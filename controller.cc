#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "controller.h"
#include "gameboard.h"

using namespace std;

Controller::Controller() {}

Controller::~Controller() { delete g; }

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
            cin >> name >> give >> receive;
            istringstream inGive(give);
            istringstream inReceive(receive);

            int giveMoney;
            int receiveMoney;
            string answer;
            
            Player *toWhom = g->getPlayer(name);

            cout << "Player " << toWhom->name << ", do you accept this trade?" << endl;
            cin >> answer;

            if (toWhom && answer == "accept") {
                if (inGive >> giveMoney && inReceive >> receiveMoney) {
                    cout << "You cannot trade money with money!" << endl;
                } else if (!(inGive >> giveMoney) && !(inReceive >> receiveMoney)) {
                    if (g->getProperty(give) && g->getProperty(receive)) {
                        g->trade(*toWhom, *(g->getProperty(give)), *(g->getProperty(receive)));
                    } else if {
                        cout << "Invalid property entered." << endl;
                    }
                } else if (inGive >> giveMoney) {
                    if (g->getProperty(receive)) {
                        g->trade(*toWhom, giveMoney, *(g->getProperty(receive)));
                    }
                } else if (inReceive >> receiveMoney) {
                    if (g->getProperty(give)) {
                        g->trade(*toWhom, *(g->getProperty(give)), receiveMoney);
                    }
                }
            } else if (!toWhom) {
                cout << "This player doesn't exist." << endl;
            } else {
                cout << "Player " << toWhom->name << " does not accept this trade." << endl;
            }
        } else if (cmd == "improve") {
            string p;
            string option;
            cin >> p >> option;
            if (g->getProperty(p)) {
                if (option == "buy") {
                    g->buyImprove(*(g->getProperty(p)));
                } else if (option == "sell") {
                    g->sellImprove(*(g->getProperty(p)));
                }
            }
        } else if (cmd == "mortgage") {
            string p;
            if (cin >> p && g->getProperty(p)) g->mortgage(*(g->getProperty(p)));
        } else if (cmd == "unmortgage") {
            string p;
            if (cin >> p && g->getProperty(p)) g->unmortgage(*(g->getProperty(p)));
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