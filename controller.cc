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
            pair<int, int> res = g->roll();
            cout << "Dice values: " << get<0>(res) << " " << get<1>(res) << endl;
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
    string name = g->getCurPlayerName();
    try {
        g->next();
    } catch (exception &e) {
        cout << RED << e.what() << DEFAULT << endl;
        return;
    }
    cout << YELLOW << name << ", your turn ends!" << DEFAULT << endl;
    cout << GREEN << g->getCurPlayerName() << ", it is now your round." << DEFAULT << endl;
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
    string name = g->getCurPlayerName();
    try {
        g->bankrupt();
    } catch (exception &e) {
        cout << RED << e.what() << DEFAULT << endl;
        return;
    }
    cout << YELLOW << "Player " << name << " was bankrupt and removed from the game." << DEFAULT << endl;
    cout << GREEN << g->getCurPlayerName() << ", it is now your round." << DEFAULT << endl;
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

void Controller::printAssets(std::tuple<std::string, double, int, std::vector<std::string>> &info) {
    cout << "Player " << get<0>(info) << endl;
    cout << "Cash: $" << get<1>(info) << endl;
    cout << "Number of cups: " << get<2>(info) << endl;
    cout << "Properties: " << endl;
    for (auto &p: get<3>(info)) {
        cout << " -" << p << endl;
    }
}

void Controller::play() {
    cout << "Game started! Welcome to watopoly!" << endl;
    string cmd;
    while (true) {
        if (g->askToLeaveTims()) {
            leaveTims();
        }
        cout << g->getCurPlayerName() << ": ";
        cin >> cmd;
        if (cmd == "roll") {
            roll();
        } else if (cmd == "next") {
            next();
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
            auto info = g->assets();
            printAssets(info);
        } else if (cmd == "all") {
            int num = g->getTotalPlayersNum();
            for (int i = 0; i < num; ++i) {
                auto info = g->assets(i);
                printAssets(info);
            }
        } else if (cmd == "save") {
            save();
        } else if (cmd == "debt" && g->debtAmount() > 0) {
            payDebt();
        } else {
            cout << RED << "Invalid command." << DEFAULT << endl;
        }
        if (g->isWin()) {
            cout << "Congratulations! You win the game." << endl;
            break;
        }
        if (g->debtAmount() > 0) {
            cout << YELLOW << "You currently owes debt $" << g->debtAmount() << ", you're provided with the debt to pay your debt." << DEFAULT << endl;
        }
    }
}


void Controller::leaveTims() {
    cout << YELLOW << "You are currently stuck at DC Tims Line, please use roll/cup/pay to leave (you may only choose once): " << DEFAULT << endl;
    cout << "(" << g->getCurPlayerName() << "): ";
    string cmd;
    while (cin >> cmd) {
        if (cmd == "roll") {
            roll();
            if (g->mustLeaveTims()) {
                cout << YELLOW << "Oops, it's your third round at Tims Line now, you must leave by pay or use cup: " << DEFAULT << endl;
            } else {
                break;
            }
        } else if (cmd == "pay") {
            g->payTims();
            break;
        } else if (cmd == "cup") {
            try {
                g->useCups();
                break;
            } catch (exception &e) {
                cout << RED << e.what() << DEFAULT << endl;
            }
        } else {
            cout << RED << "Invalid command." << DEFAULT << endl;
        }
        cout << "(" << g->getCurPlayerName() << "): ";
    }
    if (!g->inTimsLine()) {
        cout << GREEN << "Congrats! You move out of the Tims Line." << DEFAULT << endl;
        cout << *g;
    } else {
        cout << YELLOW << "Oooops, you're still stuck at DC Tims Line. Try to leave next round!" << DEFAULT << endl;
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
            bool inTims = false;
            int timsRound = 0;
            ss >> name >> displayChar >> timsCups >> money >> position;
            if (position == 10 ) {
                ss >> inTims;
                if (inTims) {
                    ss >> timsRound;
                    ++timsRound;
                }
            }
            g->addPlayer(name, displayChar, position, timsCups, money, inTims, timsRound);
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

bool Controller::askTradeResponse(const string &toName, const string &currGive, const string &currReceive) {
    cout << "To player " + toName + ": Do you accept this trade?" << endl <<
     "Trade detail: give player " + g->getCurPlayerName() + " " + currReceive + " in exchange for " + currGive << endl;
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

bool Controller::askPayTuition() {
    cout << YELLOW << "Opps, you need to pay tuition. Payment can be completed by either paying $300 (1) or paying 10% of your assets value (2)." << DEFAULT << endl
    << "Please choose 1 / 2: ";
    string cmd;
    while (cin >> cmd) {
        if (cmd == "1") return true;
        else if (cmd == "2") return false;
        else cout << RED << "Please choose 1 / 2: " << DEFAULT;
    }
    return false;
}

bool Controller::askUnMortgage(const std::string &receiverName, const std::string &propertyName) {
    cout << YELLOW << "To Player " << receiverName << ": you're receiving a mortgaged property " << propertyName << " from "
    << g->getCurPlayerName() << ". Do you want to unmortgage it immediately (1) or pay 10% of the property cost to keep it mortgage (2)?"
    << DEFAULT << endl << "Please choose 1 / 2: ";
    string cmd;
    while (cin >> cmd) {
        if (cmd == "1") {
            return true;
        } else if (cmd == "2") {
            return false;
        } else {
            cout << RED << "Please choose 1 / 2: " << DEFAULT;
        }
    }
    return false;
}


pair<string, double> Controller::auction(const vector<string>& properties) {
    cout << "Auction for ";
    for (auto &name: properties) cout << name << " ";
    cout << "started!" << endl;
    auto playersName = g->getAllPlayersName();
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