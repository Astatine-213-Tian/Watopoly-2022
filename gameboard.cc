#include <iostream>
#include <exception>
#include <memory>
#include "gameboard.h"
#include "player.h"
#include "property.h"
#include "academicBuilding.h"
#include "cell.h"
#include "dice.h"

using namespace std;

bool GameBoard::checkInTimsLine() { return curPlayer->inTims(); }

void GameBoard::roll() {
    int diceSum = 0;
    Dice d;
    int roll1 = d.roll();
    int roll2 = d.roll();
    diceSum = roll1 + roll2;
    curPlayer->setRollState(false);
    curPlayer->addRollTimes();

    if (!checkInTimsLine()) {
        if (curPlayer->getRollTimes() == 3) {
            curPlayer->initRollTimes();
            //send to Tims
        } else {
            for (int i = 1; i < diceSum; i++) {
                int cur = curPlayer->getLocation();
                int dest = (cur + i >= size) ? cur + i - size : cur + i;
                cells[dest]->passBy(*curPlayer);
                curPlayer->move(dest);
            }
            cells[curPlayer->getLocation()]->landOn(*curPlayer);

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
            // roll again once getting out of Tims line??
        }
    }
}

void GameBoard::next() {
    curPlayer->setRollState(true);
    if (curPlayer == *players.end()) {
        curPlayer = *players.begin();
    } else {
        curPlayer++;
    }
}

Player *GameBoard::getCurPlayer() { return curPlayer; }

Player *GameBoard::getPlayer(string name) {
	for (auto i : players) {
		if (i->getName() == name) return i;
	}
	return nullptr;
}

Property *GameBoard::getProperty(string name) {
	for (auto i : cells) {
		if (i->getName() == name) return i;
	}
	return nullptr;
}

void GameBoard::trade(Player &player, double value, Property &property) {
    if (curPlayer->payMoney(value) && property.getOwner() == &player) {
        player.receiveMoney(value);
        curPlayer->addProperty(property);
        player.removeProperty(property);
    } else if (!(player.hasProperty(property))) {
        cout << "Invalid trade." << endl;
    } else {
        // bankrupt
    }
}

void GameBoard::trade(Player &player, Property &p1, Property &p2) {
    if (p1.getOwner() == curPlayer && p2.getOwner() == &player) {
        curPlayer->removeProperty(p1);
	    curPlayer->addProperty(p2);
	    player.addProperty(p1);
	    player.removeProperty(p2);
    } else {
        cout << "Invalid trade." << endl;
    }
}

void GameBoard::trade(Player &player, Property &property, double value) {
    if (property.getOwner() == curPlayer && player.payMoney(value)){
        curPlayer->receiveMoney(value);
        curPlayer->removeProperty(property);
        player.addProperty(property);
    } else if (!(curPlayer->hasProperty(property))) {
        cout << "Invalid trade." << endl;
    } else {
        // bankrupt
    }
}

void GameBoard::buyImprove(Property &p) {
	try {
        AcademicBuilding ab = p;
        ab.addImprove(*curPlayer);
    } catch (bad_cast &bc) {
        cout << "This is not an academic building." << endl;
    }
}

void GameBoard::sellImprove(Property &p) {
    try {
        AcademicBuilding ab = p;
        ab.sellImprove(*curPlayer);
    } catch (bad_cast &bc) {
        cout << "This is not an academic building." << endl;
    }
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
    if (p.getMortgage() && p.getOwner() == curPlayer) {
        if (curPlayer->payMoney(p.getCost() * 0.6)) {
            p.setMortgage(false);
        } else {
            // bankrupt
        }
    } else {
        cout << "This property is not mortgaged or you are not eligible for unmortgaging." << endl;
    }
}

void GameBoard::assets(Player &p) {
    cout << "Player " << p.getName() << endl;
    cout << "Current Saving: $" << p.getCash() << endl;
    cout << "Properties: " << endl;
    for (auto i : p.getProperties()) {
        cout << i->getName() << endl;
    }
}

void GameBoard::allAssets() {
    for (auto i : players) {
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