#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "controller.h"
#include "gameboard.h"
#include "dice.h"
#include "state.h"

using namespace std;

class Property;
class AcademicBuilding;

Controller::Controller() = default;

void Controller::setGameBoard(GameBoard *gb) {
    g = gb;
    g->init();
}

//bool Controller::askPlayerTradeResponse(Player *p) {
//    cout << "Player " << p->getName() << ", do you accept this trade? (y/n)" << endl;
//    string answer;
//
//    while (true) {
//        cin >> answer;
//        if (answer == "Y" || answer == "y" || answer == "Yes" || answer == "yes") {
//            return true;
//        } else if (answer == "N" || answer == "n" || answer == "No" || answer == "no") {
//            cout << "Player " << p->getName() << " does not accept this trade." << endl;
//            return false;
//        }
//        cout << "Please input y/n as your response: " << endl;
//    }
//}


void Controller::roll() {
    // TODO better method?

    try {
        g->roll();
        cout << g;
    } catch (exception &e) {
        cout << "You may not roll anymore in this turn." << endl;
    } catch (inTims &) {
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
            cout << g;
        } else if (option == 2) {
            g->getCurPlayer()->useCup();
        } else {
            g->getCurPlayer()->forcePay(50);
        }
    }
    // if (!g->getCurPlayer()->getRollState()) {
    //     cout << "You cannot roll anymore in this term." << endl;
    // } else if (g->getCurPlayer()->inTimsLine()) {
    //     cout << "Unfortunately, you are currently in Tims Line. Please choose 1 of the 3 options (1-3):" << endl
    //          << "1 - roll (you will get out if you roll double)" << endl
    //          << "2 - use Roll Up the Rim cup (if you have)" << endl
    //          << "3 - pay 50" << endl;
    //     int option;
    //     while (!(cin >> option) || option <= 3 || option > 3) {
    //         cout << "Invalid input. Please choose a number between 1 and 3: ";
    //     }
    //     if (option == 1) {
    //         g->roll();
    //         cout << g;
    //     } else if (option == 2) {
    //         g->getCurPlayer()->useCup();
    //     } else {
    //         g->getCurPlayer()->forcePay(50);
    //     }
    // } else {
    //     g->roll();
    //     cout << g;
    // }
}

void Controller::improve() {
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
    cout << g;
}

void Controller::trade() {
    string name;
    string give;
    string receive;
    cin >> name >> give >> receive;
    try {
        g->trade(name, give, receive);
    } catch (exception &e) {
        cout << e.what() << endl;
    }
}


void Controller::unmortgage() {
    string name;
    try {
        g->unmortgage(name);
    } catch (exception &e) {
        cout << e.what() << endl;
    }
}

void Controller::next() {
    try {
        g->next();
    } catch (exception &e) {
        cout << "Unable to go next. You need to roll another time before finishing your turn." << endl;
    }
}

void Controller::mortgage() {
    string name;
    try {
        g->mortgage(name);
    } catch (exception &e) {
        cout << e.what() << endl;
    }
}

void Controller::payDebt() {
    try {
        g->payDebt();
    } catch (exception &e) {
        cout << e.what() << endl;
    }
}

void Controller::bankrupt() {
    try {
        g->bankrupt();
    } catch (exception &e) {
        cout << "Not able to bankrupt" << endl;
    }
}

void Controller::addPlayers() {
    int numPlayers = 0;
    vector<tuple<char, string, bool>> players = {
        {'G', "Goose", false},
        {'B', "GRT Bus", false},
        {'P', "Professor", false},
        {'S', "Student", false},
        {'$', "Money", false},
        {'L', "Laptop", false},
        {'T', "Pink tie", false},
    };

    cout << "Please start adding players!" << endl;
    cout << "Available players are: " << endl;
    for (int i = 0; i < players.size(); ++i) {
        cout << i + 1 << ". " << get<1>(players[i]) << " (" << get<0>(players[i]) << ")"<< endl;
    }
    cout << "Enter the index to add player, enter end to stop." << endl;
    string cmd;
    Dice d(0, 39);

    while (numPlayers <= 6) {
        cin >> cmd;
        if (cmd == "end" || cmd == "End") {
            if (numPlayers < 2) {
                cout << "Not enough players. Please add more." << endl;
                continue;
            }
            break;
        }
        stringstream ss;
        int index;
        if (ss >> index && index >= 1 && index <= players.size()) {
            const string &name = get<1>(players[index - 1]);
            const char &displayChar = get<0>(players[index - 1]);
            bool &used = get<2>(players[index-1]);
            if (used) {
                cout << "Player " << name << " is already in the game. Please choose another one." << endl;
                continue;
            }
            int randPos = 30;
            while (randPos == 30) { randPos = d.roll(); }
            g->addPlayer(name, displayChar, randPos);
            used = true;
            cout << "Player " << name << " added to the game! Initial position is " << randPos << endl;
            ++numPlayers;
        } else {
            cout << "Invalid command. Please enter valid index or end." << endl;
        }
    }
}

void Controller::play() {
    cout << "Game started! Welcome to watopoly!" << endl;
    g->start();
    string cmd;
    cout << "Please enter a command:" << endl;
    while (cin >> cmd) {
        if (cmd == "roll") {
            if (g->needDealWithDebt()) cout << "You need to pay your debt first." << endl;
            else roll();
        } else if (cmd == "next") {
            if (g->needDealWithDebt()) cout << "You need to pay your debt first." << endl;
            else next();
        } else if (cmd == "trade") {
            trade();
        } else if (cmd == "improve") {
            improve();
        } else if (cmd == "mortgage") {
            mortgage();
        } else if (cmd == "unmortgage") {
            unmortgage();
        } else if (cmd == "bankrupt") {
            bankrupt();
        } else if (cmd == "asset") {
            g->assets();
        } else if (cmd == "all") {
            g->allAssets();
        } else if (cmd == "save") {
            string filename;
            save(filename);
        } else if (cmd == "pay" && g->needDealWithDebt()) {
            payDebt();
        }else {
            cout << "Invalid command." << endl;
        }
        if (g->needDealWithDebt()) {
            cout << "You currently has debt, do you want to pay the bill or continue raising money?;" << endl
                 << "Input pay or other available command: " << endl;
        }
    }
}

void Controller::save(string& filename) {}

void Controller::load(const string& filename) {
    string line;
    ifstream ifs(filename);
    if (ifs.is_open()) {
        getline(ifs, line);
        int numPlayers = stoi(line);
        for (int i = 0; i < numPlayers; ++i) {
            getline(ifs, line);
            istringstream ss(line);
            string name;
            char displayChar;
            int timsCups;
            double money;
            int position;
            ss >> name >> displayChar >> timsCups >> money >> position;
            g->addPlayer(name, displayChar, position, timsCups, money);
        }
        while (getline(ifs, line)) {
            string property, owner;
            int improvements;
            istringstream ss(line);
            ss >> property >> owner >> improvements;
            bool mortgaged = false;
            if (improvements == -1) {
                improvements = 0;
                mortgaged = true;
            }
            g->setProperty(property, owner, improvements, mortgaged);
        }
        ifs.close();
    }
}

bool Controller::yesOrNoResponse() {
    string res;
    while (cin >> res) {
        if (res == "Yes" || res == "yes" || res == "y" || res == "Y") {
            return true;
        } else if (res == "No" || res == "no" || res == "N" || res == "n") {
            return false;
        } else {
            cout << "Invalid input, please input y/n: " << endl;
        }
    }
    return false;
}

bool Controller::askTradeResponse(const string &currName, const string &toName, const string &currGive, const string &currReceive) {
    cout << "To player " + toName + ": Do you accept this trade?" << endl <<
     "Trade detail: give player " + currName + " " + currReceive + " in exchange for " + currGive + ")" << endl
     << "Your response (y/n): " << endl;
    if (yesOrNoResponse()) return true;
    else {
        cout << "Trade rejected." << endl;
        return false;
    }
}


pair<string, double> Controller::auction(const vector<string>& properties, const vector<string>& playersName) {
    cout << "Auction for ";
    for (auto &name: properties) cout << name << " ";
    cout << "started!" << endl;

    vector<pair<string, bool>> participants;
    participants.reserve(playersName.size());
    for (auto & name : playersName) { participants.emplace_back(name, true); }
    pair<string, double> lastBidInfo(participants[participants.size() - 1].first, 0);
    size_t participantLeft = participants.size();

    while (true) {
        for (auto &participant : participants) {
            if (participantLeft <= 1) {
                cout << "Congratulations " << lastBidInfo.first << "! You are the winning bidder. Your bid price is " << lastBidInfo.second << endl;
                return lastBidInfo;
            }
            if (participant.second) {
                cout << "Player " << participant.first << ", please enter you bid (q for quit): ";
                string cmd;
                while (cin >> cmd) {
                    if (cmd == "q" || cmd == "quit" || cmd == "Q" || cmd == "Quit") {
                        --participantLeft;
                        participant.second = false;
                        break;
                    }
                    stringstream ss{cmd};
                    double curBid;
                    if (ss >> curBid) {
                        if (curBid <= lastBidInfo.second) {
                            cout << "Invalid: your bid must be higher than " << lastBidInfo.second << endl;
                        } else {
                            cout << "Bid successfully. The newest bid is " << curBid << endl;
                            lastBidInfo = make_pair(participant.first, curBid);
                            break;
                        }
                    } else {
                        cout << "Invalid input." << endl;
                    }
                    cout << "Please bid or enter q to quit: ";
                }
            }
        }
    }
}