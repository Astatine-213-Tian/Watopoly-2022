#include <iostream>
#include <exception>
#include <memory>
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

GameBoard::GameBoard() : curPlayer{nullptr} {}

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

bool GameBoard::checkInTimsLine() { return curPlayer->inTims(); }

void GameBoard::forward(const int diceSum) {
    for (int i = 1; i < diceSum; i++) {
        int cur = curPlayer->getLocation();
        int dest = (cur + i >= cells.size()) ? cur + i - cells.size() : cur + i;
        cells[dest]->passBy(*curPlayer);
        curPlayer->move(dest);
    }
    try {
        cells[curPlayer->getLocation()]->landOn(*curPlayer);
    } catch (sendToTims &) {
        // send to tims
    }
}

void GameBoard::roll() {
    int roll1 = dice1->roll();
    int roll2 = dice2->roll();
    int diceSum = roll1 + roll2;
    curPlayer->setRollState(false);
    curPlayer->addRollTimes();
    int size = (int) cells.size();

    if (!checkInTimsLine()) {
        if (curPlayer->getRollTimes() == 3) {
            curPlayer->initRollTimes();
            //TODO Send to Tims
        } else {
            forward(diceSum);

            if (roll1 == roll2) {
                curPlayer->setRollState(true);
                cout << "Lucky! You may roll again." << endl;
            } else {
                curPlayer->initRollTimes();
            }
        }
    } else {
        if (roll1 == roll2) {
            cout << "Congrats for getting out of the line!" << endl;
            curPlayer->removeFromTimsLine();
            curPlayer->initRollTimes();
            forward(diceSum);
        }
    }
}

void GameBoard::next() {
    curPlayer->setRollState(true);
    size_t numPlayer = players.size();
    if (curPlayer == players[numPlayer - 1].get()) {
        curPlayer = players[0].get();
    } else {
        curPlayer++;
    }
}

Player *GameBoard::getCurPlayer() { return curPlayer; }

Player *GameBoard::getPlayer(const string& name) const{
    for (auto &i : players) {
        if (i->getName() == name) return i.get();
    }
    throw NotPlayer{name};
}

Property *GameBoard::getProperty(const string& name) const{
    for (auto &i : cells) {
        if (i->getName() == name) {
            auto *p = dynamic_cast<Property*>(i.get());
            if (p) return p;
            else break;
        }
    }
    throw NotProperty{name};
}

AcademicBuilding *GameBoard::getAcademicBuilding(const std::string &name) const{
    for (auto &i : cells) {
        if (i->getName() == name) {
            auto *ab = dynamic_cast<AcademicBuilding*>(i.get());
            if (ab) return ab;
            else break;
        }
    }
    throw NotAcademicBuilding{name};
}

void GameBoard::trade(Player &player, double value, Property &property) {
    // TODO encapsulate in player?
    if (property.getOwner() != &player) {
        throw NotOwner{player.getName(), property.getName()};
    }
    property.setOwner(curPlayer);

    //check bankrupt
    curPlayer->payMoney(value);
    player.receiveMoney(value);
}

void GameBoard::trade(Player &player, Property &p1, Property &p2) {
    // TODO encapsulate in player?
    if (p1.getOwner() != curPlayer) {
        throw NotOwner{curPlayer->getName(), p1.getName()};
    } else if (p2.getOwner() != &player) {
        throw NotOwner{player.getName(), p2.getName()};
    }
    p1.setOwner(&player);
    p2.setOwner(curPlayer);
}

void GameBoard::trade(Player &player, Property &property, double value) {
    // TODO encapsulate in player?
    if (property.getOwner() != curPlayer) {
        throw NotOwner{curPlayer->getName(), property.getName()};
    }
    player.payMoney(value);
    curPlayer->receiveMoney(value);
    property.setOwner(&player);
}

void GameBoard::buyImprove(AcademicBuilding &ab) {
    curPlayer->buyImprove(ab);
}

void GameBoard::sellImprove(AcademicBuilding &ab) {
    curPlayer->sellImprove(ab);
}

void GameBoard::mortgage(Property &p) {
    if (p.getOwner() == curPlayer) {
        // p.setMortgage(true);
        curPlayer->receiveMoney(p.getCost() / 2);
    } else {
        cout << "You cannot mortgage property that you do not possess." << endl;
    }
}

void GameBoard::unmortgage(Property &p) {
//    if (p.getMortgage() && p.getOwner() == curPlayer) {
//        if (curPlayer->payMoney(p.getCost() * 0.6)) {
//            p.setMortgage(false);
//        } else {
//            // bankrupt
//        }
//    } else {
//        cout << "This property is not mortgaged or you are not eligible for unmortgaging." << endl;
//    }
}

void GameBoard::assets(Player &p) {
    cout << "Player " << p.getName() << endl;
    cout << "Current Saving: $" << p.getCash() << endl;
    cout << "Properties: " << endl;
    for (auto &i : cells) {
        auto *property = dynamic_cast<Property *>(i.get());
        if (property->getOwner() == &p) {
            cout << i->getName() << endl;
        }
    }
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

void GameBoard::bankrupt() {

}