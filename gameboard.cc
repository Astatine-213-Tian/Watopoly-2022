#include <iostream>
#include <exception>
#include <memory>
#include "gameboard.h"
#include "player.h"
#include "cell.h"
#include "property.h"
#include "error.h"
#include "academicBuilding.h"

using namespace std;

Player *GameBoard::getCurPlayer() { return curPlayer; }

Player *GameBoard::getPlayer(const string& name) {
	for (auto i : players) {
		if (i->getName() == name) return i;
	}
    throw NotPlayer{name};
}

Property *GameBoard::getProperty(const string& name) {
	for (auto i : cells) {
		if (i->getName() == name) {
            return dynamic_cast<Property*>(i);
        };
	}
    throw NotProperty{name};
}

AcademicBuilding *GameBoard::getAcademicBuilding(const std::string &name) {
    for (auto i : cells) {
        if (i->getName() == name) {
            return dynamic_cast<AcademicBuilding*>(i);
        };
    }
    throw NotAcademicBuilding{name};
}

void GameBoard::trade(Player &player, double value, Property &property) {
    // TODO encapsulate in player?
    if (property.getOwner() != &player) {
        throw NotOwner{player.getName(), property.getName()};
    }
    curPlayer->payMoney(value);
    curPlayer->addProperty(property);
    property.setOwner(curPlayer);
    player.removeProperty(property);
    player.receiveMoney(value);

//    if (curPlayer->payMoney(value) && property.getOwner() == &player) {
//        player.receiveMoney(value);
//        curPlayer->addProperty(property);
//        player.removeProperty(property);
//    } else if (!(player.hasProperty(property))) {
//        cout << "Invalid trade." << endl;
//    } else {
//        // bankrupt
//    }
}

void GameBoard::trade(Player &player, Property &p1, Property &p2) {
    // TODO encapsulate in player?
    if (p1.getOwner() != curPlayer) {
        throw NotOwner{curPlayer->getName(), p1.getName()};
    } else if (p2.getOwner() != &player) {
        throw NotOwner{player.getName(), p2.getName()};
    }
    curPlayer->removeProperty(p1);
    curPlayer->addProperty(p2);
    player.addProperty(p1);
    player.removeProperty(p2);
    p1.setOwner(&player);
    p2.setOwner(curPlayer);

//    if (p1.getOwner() == curPlayer && p2.getOwner() == &player) {
//        curPlayer->removeProperty(p1);
//	    curPlayer->addProperty(p2);
//	    player.addProperty(p1);
//	    player.removeProperty(p2);
//    } else {
//        cout << "Invalid trade." << endl;
//    }
}

void GameBoard::trade(Player &player, Property &property, double value) {
    // TODO encapsulate in player?
    if (property.getOwner() != curPlayer) {
        throw NotOwner{curPlayer->getName(), property.getName()};
    }
    player.payMoney(value);
    player.addProperty(property);
    curPlayer->receiveMoney(value);
    curPlayer->removeProperty(property);
    property.setOwner(&player);

//    if (property.getOwner() == curPlayer && player.payMoney(value)){
//        curPlayer->receiveMoney(value);
//        curPlayer->removeProperty(property);
//        player.addProperty(property);
//    } else if (!(curPlayer->hasProperty(property))) {
//        cout << "Invalid trade." << endl;
//    } else {
//        // bankrupt
//    }
}

void GameBoard::buyImprove(AcademicBuilding &ab) {
    // TODO curPlayer->buyImprove(ab) - checkIsMonopolized
}

void GameBoard::sellImprove(AcademicBuilding &ab) {
    // TODO curPlayer->sellImprove(ab)
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

