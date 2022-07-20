#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "controller.h"
#include "gameboard.h"
#include "player.h"

using namespace std;

class Property;
class AcademicBuilding;

Controller::Controller() : g{make_unique<GameBoard>()} {
    g->init();
}


bool Controller::askPlayerTradeResponse(Player *p) {
    cout << "Player " << p->getName() << ", do you accept this trade? (y/n)" << endl;
    string answer;

    while (true) {
        cin >> answer;
        if (answer == "Y" || answer == "y" || answer == "Yes" || answer == "yes") {
            return true;
        } else if (answer == "N" || answer == "n" || answer == "No" || answer == "no") {
            cout << "Player " << p->getName() << " does not accept this trade." << endl;
            return false;
        }
        cout << "Please input y/n as your response: " << endl;
    }
}

void Controller::play() {
    string cmd;

    while (cin >> cmd) {
        if (cmd == "roll") {
            if (!g->getCurPlayer()->getRollState()) {
                cout << "You cannot roll in this turn." << endl;
            } else {
                g->roll();
            }
        } else if (cmd == "next") {
            if (!g->getCurPlayer()->getRollState()) {
                g->next();
            } else {
                cout << "You may roll another time before finishing your turn." << endl;
            }
        } else if (cmd == "trade") {
            string name;
            string give;
            string receive;
            istringstream ssGive(give);
            istringstream ssReceive(receive);
            int giveMoney;
            int receiveMoney;
            Player *toWhom;

            cin >> name >> give >> receive;
            try {
                toWhom = g->getPlayer(name);
            } catch (exception &e) {
                cout << e.what() << endl;
                continue;
            }
            if (ssGive >> giveMoney) {
                if (ssReceive >> receiveMoney) {
                    cout << "You cannot trade money with money!" << endl;
                    continue;
                }
                Property *receiveProperty;
                try {
                    receiveProperty = g->getProperty(receive);
                } catch (exception &e) {
                    cout << e.what() << endl;
                    continue;
                }
                if (askPlayerTradeResponse(toWhom)) {
                    try {
                        g->trade(*toWhom, giveMoney, *receiveProperty);
                    } catch (exception &e) {
                        cout << e.what() << endl;
                    }
                }
            } else if (ssReceive >> receiveMoney) {
                Property *giveProperty;
                try {
                    giveProperty = g->getProperty(give);
                } catch (exception &e) {
                    cout << e.what() << endl;
                    continue;
                }
                if (askPlayerTradeResponse(toWhom)) {
                    try {
                        g->trade(*toWhom, *giveProperty, receiveMoney);
                    } catch (exception &e) {
                        cout << e.what() << endl;
                    }
                }
            } else {
                Property *giveProperty;
                Property *receiveProperty;
                try {
                    giveProperty = g->getProperty(give);
                    receiveProperty = g->getProperty(receive);
                } catch (exception &e) {
                    cout << e.what() << endl;
                    continue;
                }
                if (askPlayerTradeResponse(toWhom)) {
                    try {
                        g->trade(*toWhom, *giveProperty, *receiveProperty);
                    } catch (exception &e) {
                        cout << e.what() << endl;
                    }
                }
            }
        } else if (cmd == "improve") {
            string name;
            string option;
            cin >> name >> option;
            AcademicBuilding *ab;
            try {
                 ab = g->getAcademicBuilding(name);
            } catch (exception &e) {
                cout << e.what() << endl;
                continue;
            }
            if (option == "buy") {
                try {
                    g->buyImprove(*ab);
                } catch (exception &e) {
                    cout << e.what() << endl;
                }
            } else if (option == "sell") {
                try {
                    g->sellImprove(*ab);
                } catch (exception &e) {
                    cout << e.what() << endl;
                }
            }
        } else if (cmd == "mortgage") {
            string name;
            Property *p;
            try {
                p = g->getProperty(name);
            } catch (exception &e) {
                cout << e.what() << endl;
                continue;
            }
            g->mortgage(*p);
        } else if (cmd == "unmortgage") {
            string name;
            Property *p;
            try {
                p = g->getProperty(name);
            } catch (exception &e) {
                cout << e.what() << endl;
                continue;
            }
            g->unmortgage(*p);
        } else if (cmd == "bankrupt") {
            g->bankrupt();
        } else if (cmd == "asset") {
            g->assets(*(g->getCurPlayer()));
        } else if (cmd == "all") {
            g->allAssets();
        } else if (cmd == "save") {
            string filename;
            save(filename);
        } else {
            cout << "Invalid command." << endl;
        }
    }
}

void Controller::save(string filename) {

}

void Controller::load(const string& filename) {
    string line;
    ifstream iFile(filename);
    if (iFile.is_open()) {
        getline(iFile, line);
        int numPlayers = stoi(line);
        for (int i = 0; i < numPlayers; ++i) {
            getline(iFile, line);
            istringstream ss(line);
            string name;
            char displayChar;
            int timsCups;
            double money;
            int position;
            ss >> name >> displayChar >> timsCups >> money >> position;
            g->addPlayer(name, displayChar, position, timsCups, money);
        }
        while (getline(iFile, line)) {
            // TODO how to set info for property?
        }
    }
}