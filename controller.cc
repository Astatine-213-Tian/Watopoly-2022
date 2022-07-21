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
                cout << "You cannot roll anymore in this term." << endl;
            } else if (g->getCurPlayer()->inTimsLine()) {
                cout << "Unfortunately, you are currently in Tims Line. Please choose 1 of the 3 options (1-3):" << endl
                     << "1 - roll (you will get out if you roll double)" << endl
                     << "2 - use Roll Up the Rim cup (if you have)" << endl
                     << "3 - pay 50" << endl;
                int option;
                while (!(cin >> option) || option <= 3 || option > 3) {
                    cout << "Invalid input. Please choose a number between 1 and 3: ";
                }
                if (option == 1) {
                    g->roll();
                } else if (option == 2) {
                    g->getCurPlayer()->useCup();
                } else {
                    g->getCurPlayer()->payMoney(50);
                }
            } else {
                g->roll();
            }
        } else if (cmd == "next") {
            if (!g->getCurPlayer()->getRollState()) {
                g->next();
            } else {
                cout << "You need to roll another time before finishing your turn." << endl;
            }
        } else if (cmd == "trade") {
            string name;
            string give;
            string receive;
//            istringstream ssGive(give);
//            istringstream ssReceive(receive);
//            int giveMoney;
//            int receiveMoney;
//            Player *toWhom;

            cin >> name >> give >> receive;
            g->trade(name, give, receive);
//            try {
//                toWhom = g->getPlayer(name);
//            } catch (exception &e) {
//                cout << e.what() << endl;
//                continue;
//            }
//            if (ssGive >> giveMoney) {
//                if (ssReceive >> receiveMoney) {
//                    cout << "You cannot trade money with money!" << endl;
//                    continue;
//                }
//                Property *receiveProperty;
//                try {
//                    receiveProperty = g->getPlayerProperty(receive);
//                } catch (exception &e) {
//                    cout << e.what() << endl;
//                    continue;
//                }
//                if (askPlayerTradeResponse(toWhom)) {
//                    try {
//                        g->trade(*toWhom, giveMoney, *receiveProperty);
//                    } catch (exception &e) {
//                        cout << e.what() << endl;
//                    }
//                }
//            } else if (ssReceive >> receiveMoney) {
//                Property *giveProperty;
//                try {
//                    giveProperty = g->getPlayerProperty(give);
//                } catch (exception &e) {
//                    cout << e.what() << endl;
//                    continue;
//                }
//                if (askPlayerTradeResponse(toWhom)) {
//                    try {
//                        g->trade(*toWhom, *giveProperty, receiveMoney);
//                    } catch (exception &e) {
//                        cout << e.what() << endl;
//                    }
//                }
//            } else {
//                Property *giveProperty;
//                Property *receiveProperty;
//                try {
//                    giveProperty = g->getPlayerProperty(give);
//                    receiveProperty = g->getPlayerProperty(receive);
//                } catch (exception &e) {
//                    cout << e.what() << endl;
//                    continue;
//                }
//                if (askPlayerTradeResponse(toWhom)) {
//                    try {
//                        g->trade(*toWhom, *giveProperty, *receiveProperty);
//                    } catch (exception &e) {
//                        cout << e.what() << endl;
//                    }
//                }
//            }
        } else if (cmd == "improve") {
            string name;
            string option;
            cin >> name >> option;
            if (option == "buy") {
                try {
                    g->buyImprove(name);
                } catch (exception &e) {
                    cout << e.what() << endl;
                }
            } else if (option == "sell") {
                try {
                    g->sellImprove(name);
                } catch (exception &e) {
                    cout << e.what() << endl;
                }
            }
        } else if (cmd == "mortgage") {
            string name;
            try {
                g->mortgage(name);
            } catch (exception &e) {
                cout << e.what() << endl;
            }
        } else if (cmd == "unmortgage") {
            string name;
            try {
                g->unmortgage(name);
            } catch (exception &e) {
                cout << e.what() << endl;
            }
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