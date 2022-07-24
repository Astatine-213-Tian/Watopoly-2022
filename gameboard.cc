#include <iostream>
#include <memory>
#include <sstream>
#include <algorithm>
#include "gameboard.h"
#include "property.h"
#include "academicBuilding.h"
#include "dice.h"
#include "error.h"
#include "geese.h"
#include "osap.h"
#include "slc.h"
#include "needleshall.h"
#include "residence.h"
#include "monopolyBlock.h"
#include "tuition.h"
#include "timsLine.h"
#include "gym.h"
#include "goToTims.h"
#include "coop.h"
#include "textdisplay.h"
//#include "state.h"

using namespace std;

GameBoard::GameBoard() : curPlayer{nullptr}, curPlayerIndex{0}, dice1{make_unique<Dice>()}, dice2{make_unique<Dice>()} {}

void GameBoard::init() {
    blocks.emplace_back(make_unique<MonopolyBlock>("Art1", 50));
    blocks.emplace_back(make_unique<MonopolyBlock>("Art2", 50));
    blocks.emplace_back(make_unique<MonopolyBlock>("Eng", 100));
    blocks.emplace_back(make_unique<MonopolyBlock>("Health", 100));
    blocks.emplace_back(make_unique<MonopolyBlock>("Env", 150));
    blocks.emplace_back(make_unique<MonopolyBlock>("Sci1", 150));
    blocks.emplace_back(make_unique<MonopolyBlock>("Sci2", 200));
    blocks.emplace_back(make_unique<MonopolyBlock>("Math", 200));

    cells.emplace_back(make_shared<OSAP>());
    properties.emplace_back(make_shared<AcademicBuilding>(AcademicBuilding{"AL", 40, vector<double>{2, 10, 30, 90, 160, 250}, blocks[0].get()}));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<SLC>());
    properties.emplace_back(make_shared<AcademicBuilding>(AcademicBuilding{"ML", 60, vector<double>{4, 20, 60, 180, 320, 450}, blocks[0].get()}));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<Tuition>(Tuition{}));
    properties.emplace_back(make_shared<Residence>("MKV"));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("ECH", 100, vector<double>{6, 30, 90, 270, 400, 550}, blocks[1].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<NH>());
    properties.emplace_back(make_shared<AcademicBuilding>("PAS", 100, vector<double>{6, 30, 90, 270, 400, 550}, blocks[1].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("HH", 120, vector<double>{8, 40, 10, 300, 450, 600}, blocks[1].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<TimsLine>());
    properties.emplace_back(make_shared<AcademicBuilding>("RCH", 140, vector<double>{10, 50, 150, 450, 625, 750}, blocks[2].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<Gym>("PAC"));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("DWE", 140, vector<double>{10, 50, 150, 450, 625, 750}, blocks[2].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("CPH", 160, vector<double>{12, 60, 180, 500, 700, 900}, blocks[2].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<Residence>("UWP"));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("LHI", 180, vector<double>{14, 70, 200, 550, 750, 950}, blocks[3].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<SLC>());
    properties.emplace_back(make_shared<AcademicBuilding>("BMH", 180, vector<double>{14, 70, 200, 550, 750, 950}, blocks[3].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("OPT", 200, vector<double>{16, 80, 220, 600, 800, 1000}, blocks[3].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<Geese>());
    properties.emplace_back(make_shared<AcademicBuilding>("EV1", 220, vector<double>{18, 90, 250, 700, 875, 1050}, blocks[4].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<NH>());
    properties.emplace_back(make_shared<AcademicBuilding>("EV2", 220, vector<double>{18, 90, 250, 700, 875, 1050}, blocks[4].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("EV3", 240, vector<double>{20, 100, 300, 750, 925, 1100}, blocks[4].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<Residence>("V1"));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("PHYS", 260, vector<double>{22, 110, 330, 800, 975, 1150}, blocks[5].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("B1", 260, vector<double>{22, 110, 330, 800, 975, 1150}, blocks[5].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<Gym>("CIF"));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("B2", 280, vector<double>{24, 120, 360, 850, 1025, 1200}, blocks[5].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<GoToTims>());
    properties.emplace_back(make_shared<AcademicBuilding>("EIT", 300, vector<double>{26, 130, 390, 900, 1100, 1275}, blocks[6].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("ESC", 300, vector<double>{26, 130, 390, 900, 1100, 1275}, blocks[6].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<SLC>());
    properties.emplace_back(make_shared<AcademicBuilding>("C2", 320, vector<double>{28, 150, 450, 1000, 1200, 1400}, blocks[6].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<Residence>("REV"));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<NH>());
    properties.emplace_back(make_shared<AcademicBuilding>("MC", 350, vector<double>{35, 175, 500, 1100, 1300, 1500}, blocks[7].get()));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<Coop>());
    properties.emplace_back(make_shared<AcademicBuilding>("DC", 400, vector<double>{50, 200, 600, 1400, 1700, 2000}, blocks[7].get()));
    cells.emplace_back(properties[properties.size() - 1]);

    for (int i = 0; i < (int) cells.size(); i++) {
        cells[i]->setIndex(i);
        cells[i]->attach(td);
        cells[i]->notifyObservers();
    }
}

void GameBoard::setController(Controller *c) {
    controller = c;
}

void GameBoard::addPlayer(const string &name, char displayChar, int position, int timsCups, double money, bool isInTims, int timsRound) {
    players.emplace_back(make_unique<Player>(name, displayChar, timsCups, money, position, this, isInTims, timsRound));
    cells[position]->initLandOn(*players[players.size() - 1].get());
}


void GameBoard::setProperty(const string &name, const string &owner, int improvements, bool mortgaged) {
    Property *property = getProperty(name);
    Player *player = getPlayer(owner);
    property->setOwner(player);
    property->loadInfo(improvements, mortgaged);
}

void GameBoard::start() {
    curPlayer = players[0].get();
}

void GameBoard::move(int distance) {
    int cur = curPlayer->getLocation();
    cells[cur]->leave(curPlayer->getDisplayChar());

    int size = static_cast<int>(cells.size());
    int dest;
    for (int i = 1; i <= abs(distance); ++i) {
        if (distance >= 0) {
            dest = (cur + i >= size) ? cur + i - size : cur + i;
        } else {
            dest = (cur - i < 0) ? cur - i + size : cur - i;
        }
        cells[dest]->passBy(*curPlayer);
    }
    curPlayer->setLocation(dest);
    
    int final = curPlayer->getLocation();
    cells[final]->landOn(*curPlayer);
    if (cells[final]->getCost() != 0 && !cells[final]->getOwner()) {
        bool willBuy = Controller::askBuyResponse(cells[final]->getName(), cells[final]->getCost());
        if (willBuy) {
            curPlayer->forcePay(cells[final]->getCost());
        } else {
            vector<string> allPlayersName;
            for (auto &i: players) {
                allPlayersName.emplace_back(i->getName());
            }
            pair<string, double> bidInfo = Controller::auction(vector<string>{cells[final]->getName()}, allPlayersName);
            Player *bidWinner = getPlayer(bidInfo.first);
            // TODO what if bankrupt here?
            bidWinner->forcePay(bidInfo.second);
        }
    }

    if (curPlayer->getShouldMoveToTims()) {
        cells[final]->leave(curPlayer->getDisplayChar());
        curPlayer->sentToTimsLine(timsLineIndex);
        cells[curPlayer->getLocation()]->landOn(*curPlayer);
        curPlayer->setRollState(false);
    }
}

// g->isTimsLine: return curPlayer->isTimsLine
// moveoutTims(int opt) 1-roll() 2-usecup 3-pay (1/2 pay, 3 - forcePay)

bool GameBoard::inTimsLine() { return curPlayer->inTimsLine(); }

void GameBoard::roll(bool testMode, int d1, int d2) {
    if (!curPlayer->getRollState()) throw InvalidCmd{"roll"};
    int roll1;
    int roll2;
    if (testMode) {
        roll1 = d1;
        roll2 = d2;
    } else {
        roll1 = dice1->roll();
        roll2 = dice2->roll();
    }
    
    curPlayer->addRollTimes();

    // TODO TimsLine check
    if (curPlayer->inTimsLine()) {
        if (roll1 == roll2) {
            curPlayer->removeFromTimsLine();
            curPlayer->setRollState(false);
        } else if (curPlayer->getRollTimes() == 2) {
            curPlayer->setRollState(false);
        }
    } else {
        if (curPlayer->getRollTimes() == 3 && roll1 == roll2) {
            curPlayer->sentToTimsLine(timsLineIndex);
            curPlayer->setRollState(false);
        } else {
            move(roll1 + roll2);
            curPlayer->setRollState(roll1 == roll2);
        }
    }
}

void GameBoard::next() {
    if (curPlayer->getRollState()) {
        throw InvalidCmd{"next"};
    }

    curPlayerIndex = curPlayerIndex == players.size() - 1 ? 0 : curPlayerIndex + 1;
    curPlayer = players[curPlayerIndex].get();
    curPlayer->initRollTimes();
    curPlayer->setRollState(true);
}

string GameBoard::getCurPlayerName() { return curPlayer->getName(); }

unique_ptr<vector<tuple<string, char, int, double, int>>> GameBoard::getAllPlayersInfo() {
    auto res = make_unique<vector<tuple<string, char, int, double, int>>>();
    for (auto &p: players) {
        res->emplace_back(p->getName(), p->getDisplayChar(), p->getNumCup(), p->getCash(), p->getLocation());
    }
    return res;
}

unique_ptr<vector<tuple<string, string, int, bool>>> GameBoard::getAllPropertiesInfo() {
    auto res = make_unique<vector<tuple<string, string, int, bool>>>();
    res->reserve(properties.size());
    for (auto &p: properties) {
        string ownerName = p->getOwner() ? p->getOwner()->getName() : "BANK";
        res->emplace_back(p->getName(), ownerName, p->getImproveNum(), p->getMortgageStatus());
    }
    return res;
}

Player *GameBoard::getPlayer(const string &name) const{
    if (name == "BANK") return nullptr;
    for (auto &cell : players) {
        if (cell->getName() == name) return cell.get();
    }
    throw NotPlayer{name};
}

Property *GameBoard::getProperty(const string &name) const {
    for (auto &property : properties) {
        if (property->getName() == name) return property.get();
    }
    throw NotProperty{name};
}

Property *GameBoard::getPlayerProperty(const string &name, Player *player) const {
    Property *property = getProperty(name);
    if (property && property->getOwner() != player) {
        throw NotOwner{player->getName(), property->getName()};
    }
    return property;
}


void GameBoard::noImprovementCheck(Property *property) {
    if (property->getImproveNum() >= 0) {
        throw BuildingStillWithImprove{property->getName() };
    }
}

void GameBoard::trade(const string &name, const string &give, const string &receive) {
    Player *toWhom = getPlayer(name);
    istringstream ssGive(give);
    istringstream ssReceive(receive);
    double giveMoney;
    double receiveMoney;

    if (ssGive >> giveMoney) {
        if (ssReceive >> receiveMoney) {
            throw TradeMoneyWithMoney{};
        }
        Property *receiveProperty = getPlayerProperty(receive, toWhom);
        noImprovementCheck(receiveProperty);
        if (Controller::askTradeResponse(curPlayer->getName(), toWhom->getName(), "$" + to_string(giveMoney), receiveProperty->getName())) {
            trade(*toWhom, giveMoney, *receiveProperty);
        }
    } else if (ssReceive >> receiveMoney) {
        Property *giveProperty = getPlayerProperty(give, curPlayer);
        noImprovementCheck(giveProperty);
        if (Controller::askTradeResponse(curPlayer->getName(), toWhom->getName(), giveProperty->getName(), "$" + to_string(receiveMoney))) {
            trade(*toWhom, *giveProperty, receiveMoney);
        }
    } else {
        Property *giveProperty = getPlayerProperty(give, curPlayer);
        noImprovementCheck(giveProperty);
        Property *receiveProperty = getPlayerProperty(receive, toWhom);
        noImprovementCheck(receiveProperty);
        if (Controller::askTradeResponse(curPlayer->getName(), toWhom->getName(), giveProperty->getName(), receiveProperty->getName())) {
            trade(*toWhom, *giveProperty, *receiveProperty);
        }
    }
}


void GameBoard::trade(Player &toWhom, double value, Property &property) {
    curPlayer->pay(value, &toWhom);
    property.setOwner(curPlayer);
}

void GameBoard::trade(Player &toWhom, Property &p1, Property &p2) {
    p1.setOwner(&toWhom);
    p2.setOwner(curPlayer);
}

void GameBoard::trade(Player &toWhom, Property &property, double value) {
    toWhom.pay(value, curPlayer);
    property.setOwner(&toWhom);
}

void GameBoard::buyImprove(const string &name) {
    Property *p = getPlayerProperty(name, curPlayer);
    p->addImprove();
}

void GameBoard::sellImprove(const string &name) {
    Property *p = getPlayerProperty(name, curPlayer);
    p->removeImprove();
}


void GameBoard::mortgage(const string &name) {
    Property *p = getPlayerProperty(name, curPlayer);
    p->setMortgage();
}

void GameBoard::unmortgage(const string &name) {
    Property *p = getPlayerProperty(name, curPlayer);
    p->setUnMortgage();
}

double GameBoard::assetsValue() {
    double value = 0;
    for (auto &i: properties) {
        if (i->getOwner() == curPlayer) value+= i->getTradableValue();
    }
    return value;
}

void GameBoard::assets() { assets(curPlayer); }

void GameBoard::assets(Player *p) {
    cout << "Player " << p->getName() << endl;
    cout << "Current Saving: $" << p->getCash() << endl;
    cout << "Current cups: " << p->getNumCup() << endl;
    cout << "Properties: " << endl;
    for (auto &i : properties) {
        if (i->getOwner() == p) {
            cout << i->getName() << endl;
        }
    }
    cout << "Total value (mortgage + sell) " << assetsValue() << endl;
}

void GameBoard::allAssets() {
    for (auto &i : players) {
        assets(i.get());
    }
}

bool GameBoard::isWin() {
    return (players.size() == 1);
}

void GameBoard::payDebt() {
    curPlayer->payDebt();
}

bool GameBoard::needDealWithDebt() {
    return curPlayer->getDebtAmount() != 0;
}

void GameBoard::bankrupt() {
    if (assetsValue() >= curPlayer->getDebtAmount()) {
        throw InvalidCmd{"bankrupt"};
    }

    Player *creditor = curPlayer->getCreditor();
    vector<Property *> auctionProperties;
    if (creditor) {
        creditor->receiveMoney(curPlayer->getCash());
        for (auto &property: properties) {
            if (property->getOwner() == curPlayer) {
                // TODO ask immediately unmortgage or pay 10%
                // if unmortgage pay, else forcepay property->getCost() * 0.1
            }
        }
    } else {
        for (auto &property: properties) {
            if (property->getOwner() == curPlayer) {
                auctionProperties.emplace_back(property.get());
            }
        }
    }
    players.erase(remove_if(players.begin(), players.end(), [this](unique_ptr<Player> &p) { return p.get() == this->curPlayer; }), players.end());

    if (!auctionProperties.empty()) {
        vector<string> otherPlayersName;
        for (auto &i: players) {
            if (i.get() != curPlayer) otherPlayersName.emplace_back(i->getName());
        }

        vector<string> propertiesName;
        propertiesName.reserve(auctionProperties.size());
        for(auto &auctionProperty: auctionProperties) {
            propertiesName.emplace_back(auctionProperty->getName());
        }

        pair<string, double> bidInfo = Controller::auction(propertiesName, otherPlayersName);
        Player *bidWinner = getPlayer(bidInfo.first);
        // TODO what if bankrupt here?
        bidWinner->forcePay(bidInfo.second);
    }
}

void GameBoard::setTextDisplay(TextDisplay *_td) { td = _td; }

ostream &operator<<(ostream &out, const GameBoard &gb) {
    out << *(gb.td);
    return out;
}