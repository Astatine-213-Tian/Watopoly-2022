#include <iostream>
#include <exception>
#include <memory>
#include <sstream>
#include "gameboard.h"
#include "property.h"
#include "academicBuilding.h"
#include "dice.h"
#include "error.h"
#include "geese.h"
#include "osap.h"
#include "residence.h"
#include "monopolyBlock.h"
#include "tuition.h"
#include "timsLine.h"
#include "gym.h"
#include "goToTims.h"
#include "coop.h"
#include "action.h"

using namespace std;

GameBoard::GameBoard() : curPlayer{nullptr}, dice1{make_unique<Dice>()}, dice2{make_unique<Dice>()} {}

void GameBoard::init() {
    MonopolyBlock Art1 = MonopolyBlock{"Art1", 50};
    MonopolyBlock Art2 = MonopolyBlock{"Art2", 50};
    MonopolyBlock Eng = MonopolyBlock{"Eng", 100};
    MonopolyBlock Health = MonopolyBlock{"Health", 100};
    MonopolyBlock Env = MonopolyBlock{"Env", 150};
    MonopolyBlock Sci1 = MonopolyBlock{"Sci1", 150};
    MonopolyBlock Sci2 = MonopolyBlock{"Sci2", 200};
    MonopolyBlock Math = MonopolyBlock{"Math", 200};

    cells.emplace_back(make_unique<OSAP>());
    cells.emplace_back(make_unique<AcademicBuilding>(AcademicBuilding{"AL", 40, vector<double>{2, 10, 30, 90, 160, 250}, Art1}));
//    cells.emplace_back(make_unique<SLC>())
    cells.emplace_back(make_unique<AcademicBuilding>(AcademicBuilding{"ML", 60, vector<double>{4, 20, 60, 180, 320, 450}, Art1}));
    cells.emplace_back(make_unique<Tuition>(Tuition{}));
    cells.emplace_back(make_unique<Residence>("MKV"));
    cells.emplace_back(make_unique<AcademicBuilding>("ECH", 100, vector<double>{6, 30, 90, 270, 400, 550}, Art2));
//    cells.emplace_back(make_unique<NHL>())
    cells.emplace_back(make_unique<AcademicBuilding>("PAS", 100, vector<double>{6, 30, 90, 270, 400, 550}, Art2));
    cells.emplace_back(make_unique<AcademicBuilding>("HH", 120, vector<double>{8, 40, 10, 300, 450, 600}, Art2));
    cells.emplace_back(make_unique<TimsLine>());
    cells.emplace_back(make_unique<AcademicBuilding>("RCH", 140, vector<double>{10, 50, 150, 450, 625, 750}, Eng));
    cells.emplace_back(make_unique<Gym>("PAC"));
    cells.emplace_back(make_unique<AcademicBuilding>("DWE", 140, vector<double>{10, 50, 150, 450, 625, 750}, Eng));
    cells.emplace_back(make_unique<AcademicBuilding>("CPH", 160, vector<double>{12, 60, 180, 500, 700, 900}, Eng));
    cells.emplace_back(make_unique<Residence>("UWP"));
    cells.emplace_back(make_unique<AcademicBuilding>("LHI", 180, vector<double>{14, 70, 200, 550, 750, 950}, Health));
    //    cells.emplace_back(make_unique<SLC>())
    cells.emplace_back(make_unique<AcademicBuilding>("BMH", 180, vector<double>{14, 70, 200, 550, 750, 950}, Health));
    cells.emplace_back(make_unique<AcademicBuilding>("OPT", 200, vector<double>{16, 80, 220, 600, 800, 1000}, Health));
    cells.emplace_back(make_unique<Geese>());
    cells.emplace_back(make_unique<AcademicBuilding>("EV1", 220, vector<double>{18, 90, 250, 700, 875, 1050}, Env));
    //    cells.emplace_back(make_unique<NHL>())
    cells.emplace_back(make_unique<AcademicBuilding>("EV2", 220, vector<double>{18, 90, 250, 700, 875, 1050}, Env));
    cells.emplace_back(make_unique<AcademicBuilding>("EV3", 240, vector<double>{20, 100, 300, 750, 925, 1100}, Env));
    cells.emplace_back(make_unique<Residence>("V1"));
    cells.emplace_back(make_unique<AcademicBuilding>("PHYS", 260, vector<double>{22, 110, 330, 800, 975, 1150}, Sci1));
    cells.emplace_back(make_unique<AcademicBuilding>("B1", 260, vector<double>{22, 110, 330, 800, 975, 1150}, Sci1));
    cells.emplace_back(make_unique<Gym>("CIF"));
    cells.emplace_back(make_unique<AcademicBuilding>("B2", 280, vector<double>{24, 120, 360, 850, 1025, 1200}, Sci1));
    cells.emplace_back(make_unique<GoToTims>());
    cells.emplace_back(make_unique<AcademicBuilding>("EIT", 300, vector<double>{26, 130, 390, 900, 1100, 1275}, Sci2));
    cells.emplace_back(make_unique<AcademicBuilding>("ESC", 300, vector<double>{26, 130, 390, 900, 1100, 1275}, Sci2));
    //    cells.emplace_back(make_unique<SLC>())
    cells.emplace_back(make_unique<AcademicBuilding>("C2", 320, vector<double>{28, 150, 450, 1000, 1200, 1400}, Sci2));
    cells.emplace_back(make_unique<Residence>("REV"));
    //    cells.emplace_back(make_unique<NHL>())
    cells.emplace_back(make_unique<AcademicBuilding>("MC", 350, vector<double>{35, 175, 500, 1100, 1300, 1500}, Math));
    cells.emplace_back(make_unique<Coop>());
    cells.emplace_back(make_unique<AcademicBuilding>("DC", 400, vector<double>{50, 200, 600, 1400, 1700, 2000}, Math));
}

void GameBoard::addPlayer(const std::string &name, char displayChar, int position, int timsCups, double money) {
    players.emplace_back(make_unique<Player>(name, displayChar, timsCups, money, position));
}

void GameBoard::forward(int diceSum) {
    int size = static_cast<int>(cells.size());
    for (int i = 1; i < diceSum; i++) {
        int cur = curPlayer->getLocation();
        int dest = (cur + i >= size) ? cur + i - size : cur + i;
        cells[dest]->passBy(*curPlayer);
        curPlayer->move(dest);
    }
    cells[curPlayer->getLocation()]->landOn(*curPlayer);
    if (curPlayer->getShouldMoveToTims()) {
        curPlayer->sentToTimsLine(timsLineLocation);
        curPlayer->setRollState(false);
    }
}

void GameBoard::roll() {
//    if (!curPlayer->getRollState()) throw InvalidCmd{};
    int roll1 = dice1->roll();
    int roll2 = dice2->roll();
    curPlayer->addRollTimes();

    if (curPlayer->inTimsLine()) {
        if (roll1 == roll2) {
            curPlayer->removeFromTimsLine();
            curPlayer->setRollState(false);
        } else if (curPlayer->getRollTimes() == 2) {
            curPlayer->setRollState(false);
        }
    } else {
        if (curPlayer->getRollTimes() == 3 && roll1 == roll2) {
            curPlayer->sentToTimsLine(timsLineLocation);
            curPlayer->setRollState(false);
        } else {
            forward(roll1 + roll2);
            if (roll1 == roll2) {
                curPlayer->setRollState(true);
            } else {
                curPlayer->setRollState(false);
            }
        }
    }
}

void GameBoard::next() {
    if (curPlayer->getRollState()) {
        throw InvalidCmd{};
    }
    int numPlayer = static_cast<int>(players.size());
    if (curPlayer == players[numPlayer - 1].get()) {
        curPlayer = players[0].get();
    } else {
        curPlayer++;
    }
    curPlayer->initRollTimes();
    curPlayer->setRollState(true);
}

Player *GameBoard::getCurPlayer() { return curPlayer; }

Player *GameBoard::getPlayer(const string& name) const{
    for (auto &cell : players) {
        if (cell->getName() == name) return cell.get();
    }
    throw NotPlayer{name};
}

Property *GameBoard::getPlayerProperty(const string& name, Player *player) const {
    for (auto &cell : cells) {
        if (cell->getName() == name) {
            auto *property = dynamic_cast<Property*>(cell.get());
            if (property) {
                if (property->getOwner() == player) {
                    return property;
                } else {
                    throw NotOwner{player->getName(), property->getName()};
                }
            } else break;
        }
    }
    throw NotProperty{name};
}

AcademicBuilding *GameBoard::getPlayerAcademicBuilding(const std::string &name, Player *player) const {
    for (auto &cell : cells) {
        if (cell->getName() == name) {
            auto *ab = dynamic_cast<AcademicBuilding*>(cell.get());
            if (ab) {
                if (ab->getOwner() == player) {
                    return ab;
                } else {
                    throw NotOwner{player->getName(), ab->getName()};
                }
            } else break;
        }
    }
    throw NotAcademicBuilding{name};
}

// TODO where should I put this
bool askPlayerTradeResponse(Player *p) {
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


void GameBoard::noImprovementCheck(Property *property) {
    auto *ab = dynamic_cast<AcademicBuilding *>(property);
    if (ab && ab->getImproveNum() != 0) {
        throw BuildingStillWithImprove{property->getName() };
    }
}

void GameBoard::trade(const std::string &name, const std::string &give, const std::string &receive) {
    Player *toWhom = getPlayer(name);
    istringstream ssGive(give);
    istringstream ssReceive(receive);
    int giveMoney;
    int receiveMoney;

    if (ssGive >> giveMoney) {
        if (ssReceive >> receiveMoney) {
            throw TradeMoneyWithMoney{};
        }
        Property *receiveProperty = getPlayerProperty(receive, toWhom);
        noImprovementCheck(receiveProperty);
        if (askPlayerTradeResponse(toWhom)) {
            trade(*toWhom, giveMoney, *receiveProperty);
        }
    } else if (ssReceive >> receiveMoney) {
        Property *giveProperty = getPlayerProperty(give, curPlayer);
        noImprovementCheck(giveProperty);
        if (askPlayerTradeResponse(toWhom)) {
            trade(*toWhom, *giveProperty, receiveMoney);
        }
    } else {
        Property *giveProperty = getPlayerProperty(give, curPlayer);
        noImprovementCheck(giveProperty);
        Property *receiveProperty = getPlayerProperty(receive, toWhom);
        noImprovementCheck(receiveProperty);
        if (askPlayerTradeResponse(toWhom)) {
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
    AcademicBuilding *ab = getPlayerAcademicBuilding(name, curPlayer);
    if (!ab->isMonopolized()) {
        throw NotMonopolized{ab->getBlockName()};
    } else if (ab->getImproveNum() >= 5) {
        throw MaxImprove{ab->getBlockName()};
    }
    curPlayer->forcePay(ab->getImproveCost());
    ab->addImprove();
}

void GameBoard::sellImprove(const string &name) {
    AcademicBuilding *ab = getPlayerAcademicBuilding(name, curPlayer);
    if (ab->getImproveNum() <= 0) {
        throw ZeroImprove{ab->getBlockName()};
    }
    ab->removeImprove();
    curPlayer->receiveMoney(ab->getImproveCost() / 2);
}


void GameBoard::mortgage(const string &name) {
    Property *p = getPlayerProperty(name, curPlayer);
    if (p->getMortgageStatus()) {
        throw PropertyStillMortgage{p->getName()};
    }
    noImprovementCheck(p);
    p->setMortgage();
    curPlayer->receiveMoney(p->getCost() / 2);
}

void GameBoard::unmortgage(const string &name) {
    Property *p = getPlayerProperty(name, curPlayer);
    if (!p->getMortgageStatus()) {
        throw PropertyStillUnMortage{p->getName()};
    }
    curPlayer->forcePay(p->getUnMortgageCost());
    p->setUnMortgage();
}

double GameBoard::assetsValue() {
    double value = 0;
    for (auto &i: cells) {
        if (i->getOwner() == curPlayer) value+= i->getValue();
    }
    return value;
}

void GameBoard::assets(Player &p) {
    cout << "Player " << p.getName() << endl;
    cout << "Current Saving: $" << p.getCash() << endl;
    cout << "Properties: " << endl;
    for (auto &i : cells) {
        if (i->getOwner() == &p) {
            cout << i->getName() << endl;
        }
    }
    cout << "Total assets value: " << assetsValue() << endl;
}

void GameBoard::allAssets() {
    for (auto &i : players) {
        assets(*i);
    }
}

void GameBoard::auction(int cellNum) {

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
        throw InvalidCmd{};
    }
    // TODO bankrupt staff
}