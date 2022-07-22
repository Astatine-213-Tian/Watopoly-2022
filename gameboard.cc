#include <iostream>
#include <memory>
#include <sstream>
#include "gameboard.h"
#include "textdisplay.h"
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
#include "subject.h"
#include "observer.h"

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

    cells.emplace_back(make_shared<OSAP>());
    properties.emplace_back(make_shared<AcademicBuilding>(AcademicBuilding{"AL", 40, vector<double>{2, 10, 30, 90, 160, 250}, Art1}));
    cells.emplace_back(properties[properties.size() - 1]);
    //    cells.emplace_back(make_shared<SLC>())
    properties.emplace_back(make_shared<AcademicBuilding>(AcademicBuilding{"ML", 60, vector<double>{4, 20, 60, 180, 320, 450}, Art1}));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<Tuition>(Tuition{}));
    properties.emplace_back(make_shared<Residence>("MKV"));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("ECH", 100, vector<double>{6, 30, 90, 270, 400, 550}, Art2));
    cells.emplace_back(properties[properties.size() - 1]);
    //    cells.emplace_back(make_shared<NHL>())
    properties.emplace_back(make_shared<AcademicBuilding>("PAS", 100, vector<double>{6, 30, 90, 270, 400, 550}, Art2));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("HH", 120, vector<double>{8, 40, 10, 300, 450, 600}, Art2));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<TimsLine>());
    properties.emplace_back(make_shared<AcademicBuilding>("RCH", 140, vector<double>{10, 50, 150, 450, 625, 750}, Eng));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<Gym>("PAC"));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("DWE", 140, vector<double>{10, 50, 150, 450, 625, 750}, Eng));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("CPH", 160, vector<double>{12, 60, 180, 500, 700, 900}, Eng));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<Residence>("UWP"));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("LHI", 180, vector<double>{14, 70, 200, 550, 750, 950}, Health));
    cells.emplace_back(properties[properties.size() - 1]);
    //    cells.emplace_back(make_shared<SLC>())
    properties.emplace_back(make_shared<AcademicBuilding>("BMH", 180, vector<double>{14, 70, 200, 550, 750, 950}, Health));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("OPT", 200, vector<double>{16, 80, 220, 600, 800, 1000}, Health));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<Geese>());
    properties.emplace_back(make_shared<AcademicBuilding>("EV1", 220, vector<double>{18, 90, 250, 700, 875, 1050}, Env));
    cells.emplace_back(properties[properties.size() - 1]);
    //    cells.emplace_back(make_shared<NHL>())
    properties.emplace_back(make_shared<AcademicBuilding>("EV2", 220, vector<double>{18, 90, 250, 700, 875, 1050}, Env));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("EV3", 240, vector<double>{20, 100, 300, 750, 925, 1100}, Env));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<Residence>("V1"));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("PHYS", 260, vector<double>{22, 110, 330, 800, 975, 1150}, Sci1));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("B1", 260, vector<double>{22, 110, 330, 800, 975, 1150}, Sci1));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<Gym>("CIF"));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("B2", 280, vector<double>{24, 120, 360, 850, 1025, 1200}, Sci1));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<GoToTims>());
    properties.emplace_back(make_shared<AcademicBuilding>("EIT", 300, vector<double>{26, 130, 390, 900, 1100, 1275}, Sci2));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<AcademicBuilding>("ESC", 300, vector<double>{26, 130, 390, 900, 1100, 1275}, Sci2));
    cells.emplace_back(properties[properties.size() - 1]);
    //    cells.emplace_back(make_shared<SLC>())
    properties.emplace_back(make_shared<AcademicBuilding>("C2", 320, vector<double>{28, 150, 450, 1000, 1200, 1400}, Sci2));
    cells.emplace_back(properties[properties.size() - 1]);
    properties.emplace_back(make_shared<Residence>("REV"));
    cells.emplace_back(properties[properties.size() - 1]);
    //    cells.emplace_back(make_shared<NHL>())
    properties.emplace_back(make_shared<AcademicBuilding>("MC", 350, vector<double>{35, 175, 500, 1100, 1300, 1500}, Math));
    cells.emplace_back(properties[properties.size() - 1]);
    cells.emplace_back(make_shared<Coop>());
    properties.emplace_back(make_shared<AcademicBuilding>("DC", 400, vector<double>{50, 200, 600, 1400, 1700, 2000}, Math));
    cells.emplace_back(properties[properties.size() - 1]);

    for (int i = 0; i < (int) cells.size(); i++) {
        cells[i]->setIndex(i);
        cells[i]->attach(ob);
        cells[i]->notifyObservers();
    }
}

void GameBoard::setController(Controller *c) {
    controller = c;
}

void GameBoard::addPlayer(const std::string &name, char displayChar, int position, int timsCups, double money, bool isInTims, int timsRound) {
    players.emplace_back(make_unique<Player>(name, displayChar, timsCups, money, position, this, isInTims, timsRound));
    cells[position]->notifyObservers();
}


void GameBoard::setProperty(const std::string &name, const std::string &owner, int improvements, bool mortgaged) {
    Property *property = getProperty(name);
    Player *player = getPlayer(owner);
    property->setOwner(player);
    property->loadInfo(improvements, mortgaged);
}

void GameBoard::start() {
    curPlayer = players[0].get();
}

void GameBoard::move(int distance) {
    cells[curPlayer->getLocation()]->leave(curPlayer->getDisplayChar());
    int size = static_cast<int>(cells.size());

    int dest;
    for (int i = 1; i < abs(distance); i++) {
        int cur = curPlayer->getLocation();
        if (distance >= 0) dest = (cur + i >= size) ? cur + i - size : cur + i;
        else dest = (cur - i < 0) ? cur - i + size : cur - i;
        cells[dest]->passBy(*curPlayer);
    }
    curPlayer->setLocation(dest);
    cells[curPlayer->getLocation()]->landOn(*curPlayer);
    if (curPlayer->getShouldMoveToTims()) {
        cells[curPlayer->getLocation()]->leave(curPlayer->getDisplayChar());
        curPlayer->sentToTimsLine(timsLineIndex);
        cells[curPlayer->getLocation()]->landOn(*curPlayer);
        curPlayer->setRollState(false);
    }
}

void GameBoard::roll() {
//    if (!curPlayer->getRollState()) throw InvalidCmd{"roll};
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
            curPlayer->sentToTimsLine(timsLineIndex);
            curPlayer->setRollState(false);
        } else {
            move(roll1 + roll2);
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
        throw InvalidCmd{"next"};
    }
    cout << curPlayer->getName() << ": your turn is ended." << endl;
    int numPlayer = static_cast<int>(players.size());
    if (curPlayer == players[numPlayer - 1].get()) {
        curPlayer = players[0].get();
    } else {
        curPlayer++;
    }
    curPlayer->initRollTimes();
    curPlayer->setRollState(true);
    cout << curPlayer->getName() << ": it is not your turn." << endl;
}

Player *GameBoard::getCurPlayer() { return curPlayer; }

Player *GameBoard::getPlayer(const string &name) const{
    if (name == "BANK") return nullptr;
    for (auto &cell : players) {
        if (cell->getName() == name) return cell.get();
    }
    throw NotPlayer{name};
}

Property *GameBoard::getProperty(const std::string &name) const {
    for (auto &property : properties) {
        if (property->getName() == name) return property.get();
    }
    throw NotProperty{name};
}

Property *GameBoard::getPlayerProperty(const string &name, Player *player) const {
    Property *property = getProperty(name);
    if (property->getOwner() != player) {
        throw NotOwner{player->getName(), property->getName()};
    }
    return property;
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
    players.erase(remove_if(players.begin(), players.end(), [this](unique_ptr<Player> p) { return p.get() == this->curPlayer; }), players.end());

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

void GameBoard::setObserver(Observer *o) { ob = o; }

ostream &operator<<(ostream &out, const GameBoard &gb) {
    out << gb.ob;
    return out;
}