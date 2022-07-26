#include <iostream>
#include <memory>
#include <sstream>
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

using namespace std;

GameBoard::GameBoard() : curPlayerIndex{0}, dice1{make_unique<Dice>()}, dice2{make_unique<Dice>()}, hasRolled{false} {}

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
    players.emplace_back(make_unique<Player>(name, displayChar, timsCups, money, position, isInTims, timsRound));
    cells[position]->initLandOn(*players[players.size() - 1].get());
}

int GameBoard::totalCups() {
    int total = 0;
    for (auto &p: players) {
        total += p->getNumCup();
    }
    return total;
}

void GameBoard::setProperty(const string &name, const string &owner, int improvements, bool mortgaged) {
    Property *property = getProperty(name);
    Player *player = getPlayer(owner);
    property->setOwner(player);
    property->loadInfo(improvements, mortgaged);
}

void GameBoard::move(int distance) {
    if (distance == 0) return;
    Player *curPlayer = players[curPlayerIndex].get();
    curPlayer->setNumToMove(0);

    int cur = curPlayer->getLocation();
    cells[cur]->leave(curPlayer->getDisplayChar());

    int size = static_cast<int>(cells.size());
    int dest = cur;

    for (int i = 1; i <= abs(distance); ++i) {
        if (distance >= 0) {
            dest = (cur + i >= size) ? cur + i - size : cur + i;
        } else {
            dest = (cur - i < 0) ? cur - i + size : cur - i;
        }
        if (i != abs(distance)) cells[dest]->passBy(*curPlayer);
    }
    curPlayer->setLocation(dest);
    
    auto *p = dynamic_cast<Property *>(cells[dest].get());
    if (p && !p->getOwner()) {
        bool willBuy = Controller::askBuyResponse(cells[dest]->getName(), p->getCost());
        if (willBuy) {
            p->boughtBy(*curPlayer, p->getCost());
        } else {
            pair<string, double> bidInfo = controller->auction(vector<string>{cells[dest]->getName()});
            Player *bidWinner = getPlayer(bidInfo.first);
            p->boughtBy(*bidWinner, bidInfo.second);
        }
    }

    cells[dest]->landOn(*curPlayer);

    if (totalCups() > 4) curPlayer->addCups(-1);
    if (curPlayer->getGoToOSAP()) {
        curPlayer->setGoToOSAP(false);
        cells[dest]->leave(curPlayer->getDisplayChar());
        curPlayer->setLocation(osapIndex);
        cells[osapIndex]->landOn(*curPlayer);
    } else if (curPlayer->getGoToTims()) {
        cells[dest]->leave(curPlayer->getDisplayChar());
        curPlayer->sentToTimsLine(timsLineIndex);
        cells[curPlayer->getLocation()]->landOn(*curPlayer);
        controller->next();
    } else if (curPlayer->getNumToMove() != 0) {
        move(curPlayer->getNumToMove());
    }
}


bool GameBoard::inTimsLine() {
    return players[curPlayerIndex]->inTimsLine();
}

bool GameBoard::askToLeaveTims() {
    return players[curPlayerIndex]->inTimsLine() && !hasRolled;
}

bool GameBoard::mustLeaveTims() {
    return hasRolled && players[curPlayerIndex]->getTimsLineRound() >= 3;
}

void GameBoard::payTims() {
    Player *curPlayer = players[curPlayerIndex].get();
    curPlayer->removeFromTimsLine();
    if (mustLeaveTims()) {
        move(dice1->getValue() + dice2->getValue());
    }
    curPlayer->forcePay(50);
}

void GameBoard::useCups() {
    Player *curPlayer = players[curPlayerIndex].get();
    curPlayer->useCup();
    curPlayer->removeFromTimsLine();
    if (mustLeaveTims()) {
        move(dice1->getValue() + dice2->getValue());
    }
}


void GameBoard::roll(int d1, int d2) {
    if (!players[curPlayerIndex]->getRollState()) throw InvalidRoll{};
    dice1->setValue(d1);
    dice2->setValue(d2);
    processRoll();
}

pair<int, int> GameBoard::roll() {
    if (!players[curPlayerIndex]->getRollState()) throw InvalidRoll{};
    dice1->roll();
    dice2->roll();
    processRoll();
    return make_pair(dice1->getValue(), dice2->getValue());
}

void GameBoard::processRoll() {
    Player *curPlayer = players[curPlayerIndex].get();
    hasRolled = true;
    curPlayer->addRollTimes();
    int roll1 = dice1->getValue();
    int roll2 = dice2->getValue();

    if (curPlayer->inTimsLine()) {
        curPlayer->setRollState(false);
        if (roll1 == roll2) {
            curPlayer->removeFromTimsLine();
            move(roll1 + roll2);
        }
    } else {
        curPlayer->setRollState(roll1 == roll2);
        if (curPlayer->getRollTimes() == 3 && roll1 == roll2) {
            cells[curPlayer->getLocation()]->leave(curPlayer->getDisplayChar());
            curPlayer->sentToTimsLine(timsLineIndex);
            cells[timsLineIndex]->landOn(*curPlayer);
            curPlayer->setRollState(false);
            controller->next();
        } else {
            move(roll1 + roll2);
        }
    }
}

void GameBoard::moveToNextPlayer() {
    curPlayerIndex = curPlayerIndex == players.size() - 1 ? 0 : curPlayerIndex + 1;
    auto curPlayer = players[curPlayerIndex].get();
    curPlayer->initRollTimes();
    curPlayer->setRollState(true);
    hasRolled = false;
}

void GameBoard::next() {
    Player *curPlayer = players[curPlayerIndex].get();
    if (curPlayer->getRollState()) throw StillCanRoll{};
    else if (curPlayer->getDebtAmount() != 0) throw HasDebt{};

    if (curPlayer->inTimsLine()) {
        curPlayer->addTimsLineRound();
    }

    moveToNextPlayer();
}

string GameBoard::getCurPlayerName() { return players[curPlayerIndex]->getName(); }

std::vector<std::string> GameBoard::getAllPlayersName() {
    vector<string> allPlayersName;
    allPlayersName.reserve(players.size());
    for (auto &i: players) {
        allPlayersName.emplace_back(i->getName());
    }
    return allPlayersName;
}

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
        res->emplace_back(p->getName(), ownerName, p->getImproveNum(), p->isMortgage());
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
    Player *curPlayer = players[curPlayerIndex].get();
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
        if (controller->askTradeResponse(toWhom->getName(), "$" + to_string(giveMoney), receiveProperty->getName())) {
            trade(*toWhom, giveMoney, *receiveProperty);
        }
    } else if (ssReceive >> receiveMoney) {
        Property *giveProperty = getPlayerProperty(give, curPlayer);
        noImprovementCheck(giveProperty);
        if (controller->askTradeResponse(toWhom->getName(), giveProperty->getName(), "$" + to_string(receiveMoney))) {
            trade(*toWhom, *giveProperty, receiveMoney);
        }
    } else {
        Property *giveProperty = getPlayerProperty(give, curPlayer);
        noImprovementCheck(giveProperty);
        Property *receiveProperty = getPlayerProperty(receive, toWhom);
        noImprovementCheck(receiveProperty);
        if (controller->askTradeResponse(toWhom->getName(), giveProperty->getName(), receiveProperty->getName())) {
            trade(*toWhom, *giveProperty, *receiveProperty);
        }
    }
}


void GameBoard::trade(Player &toWhom, double value, Property &property) {
    Player *curPlayer = players[curPlayerIndex].get();
    curPlayer->pay(value, &toWhom);
    property.setOwner(curPlayer);
}

void GameBoard::trade(Player &toWhom, Property &p1, Property &p2) {
    p1.setOwner(&toWhom);
    p2.setOwner( players[curPlayerIndex].get());
}

void GameBoard::trade(Player &toWhom, Property &property, double value) {
    toWhom.pay(value, players[curPlayerIndex].get());
    property.setOwner(&toWhom);
}

void GameBoard::buyImprove(const string &name) {
    Property *p = getPlayerProperty(name, players[curPlayerIndex].get());
    p->addImprove();
}

void GameBoard::sellImprove(const string &name) {
    Property *p = getPlayerProperty(name, players[curPlayerIndex].get());
    p->removeImprove();
}


void GameBoard::mortgage(const string &name) {
    Property *p = getPlayerProperty(name, players[curPlayerIndex].get());
    p->setMortgage();
}

void GameBoard::unmortgage(const string &name) {
    Property *p = getPlayerProperty(name, players[curPlayerIndex].get());
    p->setUnMortgage();
}

double GameBoard::assetsValue() {
    double value = 0;
    Player *curPlayer = players[curPlayerIndex].get();
    for (auto &i: properties) {
        if (i->getOwner() == curPlayer) value+= i->getTradableValue();
    }
    return value;
}

void GameBoard::assets() { assets(curPlayerIndex); }

void GameBoard::assets(int index) {
    Player *p = players[index].get();
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
    for (int i = 0; i < players.size(); ++i) {
        assets(i);
    }
}

bool GameBoard::isWin() {
    return (players.size() == 1);
}

void GameBoard::payDebt() {
    players[curPlayerIndex]->payDebt();
}

double GameBoard::debtAmount() {
    return players[curPlayerIndex]->getDebtAmount();
}

void GameBoard::bankrupt() {
    Player *curPlayer = players[curPlayerIndex].get();
    if (assetsValue() >= curPlayer->getDebtAmount()) {
        throw InvalidBankrupt{};
    }

    Player *creditor = curPlayer->getCreditor();
    vector<Property *> auctionProperties;
    if (creditor) {
        creditor->receiveMoney(curPlayer->getCash());
        creditor->addCups(curPlayer->getNumCup());
        for (auto &property: properties) {
            if (property->getOwner() == curPlayer) {
                property->setOwner(creditor);
                if (property->isMortgage()) {
                    bool unmortgage = controller->askUnMortgage(creditor->getName(), property->getName());
                    if (unmortgage) {
                        property->setUnMortgage();
                        creditor->forcePay(property->getCost() * 0.6);
                    } else {
                        creditor->forcePay(property->getCost() * 0.1);
                    }
                }
            }
        }
    } else {
        for (auto &property: properties) {
            if (property->getOwner() == curPlayer) {
                auctionProperties.emplace_back(property.get());
            }
        }
    }

    players.erase(players.begin() + curPlayerIndex);
    moveToNextPlayer();

    if (!auctionProperties.empty()) {
        vector<string> propertiesName;
        propertiesName.reserve(auctionProperties.size());
        for(auto &auctionProperty: auctionProperties) {
            propertiesName.emplace_back(auctionProperty->getName());
        }

        pair<string, double> bidInfo = controller->auction(propertiesName);
        Player *bidWinner = getPlayer(bidInfo.first);
        for (auto &p: auctionProperties) {
            p->setOwner(bidWinner);
        }
        bidWinner->forcePay(bidInfo.second);
    }
}

void GameBoard::setTextDisplay(TextDisplay *_td) { td = _td; }

ostream &operator<<(ostream &out, const GameBoard &gb) {
    out << *(gb.td);
    return out;
}