#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "controller.h"
#include "gameboard.h"
#include "player.h"

using namespace std;

class Property;
class AcademicBuilding;

Controller::Controller() {}

Controller::~Controller() { delete g; }

bool Controller::askPlayer(Player *p) {
    cout << "Player " << p->getName() << ", do you accept this trade? (y/n)" << endl;
    string answer;

    while (true) {
        cin >> answer;
        if (answer == "Y" || answer == "y" || answer == "Yes" || answer == "yes") {
            return true;
        } else if (answer == "N" || answer == "n" || answer == "No" || answer == "no") {
            return false;
        }
        cout << "Please input y/n as your response: " << endl;
    }
}

void Controller::play() {
    string cmd;

    while (cin >> cmd) {
        if (cmd == "roll") {
            g->roll();
        } else if (cmd == "next") {
            g->next();
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
                if (askPlayer(toWhom)) {
                    g->trade(*toWhom, giveMoney, *receiveProperty);
                } else {
                    cout << "Player " << toWhom->getName() << " does not accept this trade." << endl;
                }
            } else if (ssReceive >> receiveMoney) {
                Property *giveProperty;
                try {
                    giveProperty = g->getProperty(give);
                } catch (exception &e) {
                    cout << e.what() << endl;
                    continue;
                }
                if (askPlayer(toWhom)) {
                    g->trade(*toWhom, *giveProperty, receiveMoney);
                } else {
                    cout << "Player " << toWhom->getName() << " does not accept this trade." << endl;
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
                if (askPlayer(toWhom)) {
                    g->trade(*toWhom, *giveProperty, *receiveProperty);
                } else {
                    cout << "Player " << toWhom->getName() << " does not accept this trade." << endl;
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
                g->buyImprove(*ab);
            } else if (option == "sell") {
                g->sellImprove(*ab);
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

void Controller::save(string filename) {}

void Controller::load() {}