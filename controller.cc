#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "controller.h"
#include "gameboard.h"
#include "dice.h"
#include "termcodes.h"

using namespace std;

class Property;
class AcademicBuilding;

Controller::Controller(): testMode{false} {}

void Controller::setGameBoard(GameBoard *gb) {
    g = gb;
    g->init();
}

void Controller::setToTestMode() { testMode = true; }

void Controller::roll() {
    bool inTims = g->inTimsLine();
    if (testMode) {
        string s1, s2;
        cin >> s1 >> s2;
        int roll1 = -1;
        int roll2 = -1;
        istringstream ss1{s1};
        ss1 >> roll1;
        istringstream ss2{s2};
        ss2 >> roll2;
        if (roll1 < 0 || roll2 < 0) {
            cout << RED << "Please enter two non-negative number after roll." << DEFAULT << endl;
            return;
        }
        try {
            g->roll(roll1, roll2);
        } catch (exception &e) {
            cout << RED << e.what() << DEFAULT << endl;
            return;
        }
    } else {
        try {
            g->roll();
        } catch (exception &e) {
            cout << RED << e.what() << DEFAULT << endl;
            return;
        }
    }
    if (!inTims) cout << *g;
    else if (!g->inTimsLine()) {
        cout << GREEN << "Congrats! You're moved out of the Tims Line." << DEFAULT << endl;
        cout << *g;
    }
}

void Controller::improve() {
    string name;
    string option;
    cin >> name >> option;
    if (option == "buy") {
        try {
            g->buyImprove(name);
        } catch (exception &e) {
            cout << RED << e.what() << DEFAULT << endl;
            return;
        }
    } else if (option == "sell") {
        try {
            g->sellImprove(name);
        } catch (exception &e) {
            cout << RED << e.what() << DEFAULT << endl;
            return;
        }
    }
    cout << *g;
}

void Controller::trade() {
    string name;
    string give;
    string receive;
    cin >> name >> give >> receive;
    try {
        g->trade(name, give, receive);
    } catch (exception &e) {
        cout << RED << e.what() << DEFAULT << endl;
    }
}


void Controller::unmortgage() {
    string name;
    cin >> name;
    try {
        g->unmortgage(name);
    } catch (exception &e) {
        cout << RED << e.what() << DEFAULT << endl;
    }
}

void Controller::next() {
    try {
        g->next();
    } catch (exception &e) {
        cout << RED << e.what() << DEFAULT << endl;
        return;
    }
    cout << GREEN << g->getCurPlayerName() << ": it is now your round." << DEFAULT << endl;
}

void Controller::mortgage() {
    string name;
    cin >> name;
    try {
        g->mortgage(name);
    } catch (exception &e) {
        cout << RED << e.what() << DEFAULT << endl;
    }
}

void Controller::payDebt() {
    try {
        g->payDebt();
    } catch (exception &e) {
        cout << RED << e.what() << DEFAULT << endl;
    }
}

void Controller::bankrupt() {
    try {
        g->bankrupt();
    } catch (exception &e) {
        cout << RED << e.what() << DEFAULT << endl;
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
    for (int i = 0; i < (int)players.size(); ++i) {
        cout << i + 1 << ". " << get<1>(players[i]) << " (" << get<0>(players[i]) << ")"<< endl;
    }
    Dice d(0, 39);

    string cmd;
    while (numPlayers < 6) {
        cout << "Enter the index to add player, or end to stop: ";
        cin >> cmd;
        if (cmd == "end" || cmd == "End" || cmd == "e" || cmd == "E") {
            if (numPlayers < 2) {
                cout << RED << "Not enough players. Please add more." << DEFAULT << endl;
                continue;
            }
            break;
        }
        stringstream ss{cmd};
        int index;
        if (ss >> index && index >= 1 && index <= (int)players.size()) {
            const string &name = get<1>(players[index - 1]);
            const char &displayChar = get<0>(players[index - 1]);
            bool &used = get<2>(players[index-1]);
            if (used) {
                cout << RED << "Player " << name << " is already in the game. Please choose another one." << DEFAULT << endl;
                continue;
            }
            int randPos = 30;
            while (randPos == 30) { randPos = d.roll(); }
            g->addPlayer(name, displayChar, randPos);
            used = true;
            cout << GREEN << "Player " << name << " added to the game! Initial position is " << randPos << "." << DEFAULT << endl;
            ++numPlayers;
        } else {
            cout << RED << "Invalid command. Please enter valid index or end." << DEFAULT << endl;
        }
    }
}

void Controller::payTims() {
    try {
        g->moveOutTims(1);
    } catch (exception &e) {
        cout << RED << e.what() << DEFAULT << endl;
        return;
    }
    cout << GREEN << "Congrats! You're moved out of the Tims Line." << DEFAULT << endl;
    cout << *g;
}

void Controller::useCups() {
    try {
        g->moveOutTims(2);
    } catch (exception &e) {
        cout << RED << e.what() << DEFAULT << endl;
        return;
    }
    cout << GREEN << "Congrats! You're moved out of the Tims Line." << DEFAULT << endl;
}

void Controller::play() {
    cout << "Game started! Welcome to watopoly!" << endl;
    g->start();
    string cmd;
    cout << g->getCurPlayerName() << ": please enter a command: ";
    while (cin >> cmd) {
        if (cmd == "roll") {
            if (g->hasDebt()) cout << "You need to pay your debt first." << endl;
            else roll();
        } else if (cmd == "next") {
            if (g->hasDebt()) cout << "You need to pay your debt first." << endl;
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
            save();
        } else if (cmd == "debt" && g->hasDebt()) {
            payDebt();
        } else {
            cout << RED << "Invalid command." << DEFAULT << endl;
        }

        if (g->askToLeaveTims()) {
            leaveDC();
        }
        if (g->hasDebt()) {
            cout << YELLOW << "You currently has debt, do you want to pay the bill or continue raising money?;" << DEFAULT << endl
                 << "Input debt or other available command. " << endl;
        }
        cout << g->getCurPlayerName() << ": ";
    }
}

void Controller::leaveDC() {
    cout << YELLOW << "You are currently stuck at DC Tim Line, please use roll/cup/pay to leave (you may only choose one once): " << DEFAULT << endl;
    string cmd;
    while (cin >> cmd) {
        if (cmd == "roll") {
            roll();
            if (g->inTimsLine()) {
                if (g->inTimsRound() >= 3) {
                    cout << YELLOW << "It's your third round now, please choose pay or cup: " << DEFAULT << endl;
                    continue;
                }
                cout << YELLOW << "Oooops, you're still stuck at DC." << DEFAULT << endl;
            }
            break;
        } else if (cmd == "pay") {
            payTims();
            if (!g->inTimsLine()) break;
        } else if (cmd == "cup") {
            useCups();
            if (!g->inTimsLine()) break;
        } else cout << RED << "Invalid command." << DEFAULT << endl;
    }
}

void Controller::save() {
    string filename;
    cin >> filename;
    ofstream ofs{filename};
    auto players = g->getAllPlayersInfo();
    auto properties = g->getAllPropertiesInfo();
    if (ofs.is_open()) {
        size_t numPlayers = players->size();
        ofs << numPlayers << endl;
        for (auto &p: *players) {
            string name = get<0>(p);
            char displayChar = get<1>(p);
            int numCups = get<2>(p);
            double cash = get<3>(p);
            int position = get<4>(p);
            ofs << name << ' ' << displayChar << ' ' << numCups << ' ' << cash << ' ' << position << endl;
        }
        for (auto &p: *properties) {
            string name = get<0>(p);
            string owner = get<1>(p);
            int improvements = get<2>(p);
            bool mortgaged = get<3>(p);
            if (improvements == -1 && !mortgaged) {
                improvements = 0;
            }
            ofs << name << ' ' << owner << ' ' << improvements << ' ' << endl;
        }
        ofs.close();
        cout << GREEN << "Successfully saved to file " << filename << DEFAULT << endl;
    } else {
        cout << RED << "Unable to open the file." << DEFAULT << endl;
    }
}

void Controller::load(const string& filename) {
    string line;
    ifstream ifs{filename};
    if (ifs.is_open()) {
        getline(ifs, line);
        int numPlayers = stoi(line);
        for (int i = 0; i < numPlayers; ++i) {
            getline(ifs, line);
            istringstream ss{line};
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
    } else {
        cout << RED << "Unable to load the file." << DEFAULT << endl;
    }
}

bool Controller::yesOrNoResponse() {
    cout << "Your response (y/n): " << endl;
    string res;
    while (cin >> res) {
        if (res == "Yes" || res == "yes" || res == "y" || res == "Y") {
            return true;
        } else if (res == "No" || res == "no" || res == "N" || res == "n") {
            return false;
        } else {
            cout << RED << "Invalid input, please input y/n: " << DEFAULT << endl;
        }
    }
    return false;
}

bool Controller::askTradeResponse(const string &currName, const string &toName, const string &currGive, const string &currReceive) {
    cout << "To player " + toName + ": Do you accept this trade?" << endl <<
     "Trade detail: give player " + currName + " " + currReceive + " in exchange for " + currGive + ")" << endl;
    if (yesOrNoResponse()) {
        cout << GREEN << "Trade accepted." << DEFAULT << endl;
        return true;
    }
    else {
        cout << RED << "Trade rejected." << DEFAULT << endl;
        return false;
    }
}

bool Controller::askBuyResponse(const std::string &propertyName, double cost) {
    cout << "Do you buy the buy the Property " << propertyName << ", which will cost you $" << cost << "?" << endl;
    return yesOrNoResponse();
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
                cout << GREEN << "Congratulations " << lastBidInfo.first << "! You are the winning bidder. Your bid price is " << lastBidInfo.second << DEFAULT << endl;
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
                            cout << RED << "Invalid: your bid must be higher than " << lastBidInfo.second << DEFAULT << endl;
                        } else {
                            cout << GREEN << "Bid successfully. The newest bid is " << curBid << DEFAULT << endl;
                            lastBidInfo = make_pair(participant.first, curBid);
                            break;
                        }
                    } else {
                        cout << RED << "Invalid input." << DEFAULT << endl;
                    }
                    cout << "Please bid or enter q to quit: ";
                }
            }
        }
    }
}