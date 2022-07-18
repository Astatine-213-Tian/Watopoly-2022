#include <iostream>
#include <exception>
#include <memory>
#include "gameboard.h"
#include "player.h"

using namespace std;

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

void GameBoard::trade(Player &player, int value, Property &property) {
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

void GameBoard::trade(Player &player, Property &property, int value) {
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
        Academic ab = p;
        ab.addImprove();
    } catch (bad_cast &bc) {
        cout << "This is not an academic building." << endl;
    }
}

void GameBoard::sellImprove(Property &p) {
    try {
        Academic ab = p;
        ab.sellImprove();
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
        if (curPlayer->payMoney(p.getCash() * 0.6)) {
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

