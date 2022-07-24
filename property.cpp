#include <utility>
#include "property.h"
#include "player.h"
#include "error.h"

Property::Property(std::string name, double cost): Cell{std::move(name)}, cost{cost}, owner{nullptr}, isMortgaged{false} {}

Player *Property::getOwner() const { return owner; }

void Property::setOwner(Player *p) {
    owner = p;
    notifyObservers();
}

double Property::getCost() const { return cost; }

void Property::setMortgage() {
    if (isMortgaged) throw PropertyStillMortgage{getName()};
    if (getImproveNum() > 0) throw BuildingStillWithImprove{getName()};
    owner->receiveMoney( cost / 2);
    isMortgaged = true;
}

void Property::setUnMortgage() {
    if (!isMortgaged) throw PropertyStillUnMortage{getName()};
    owner->pay(cost * 0.6);
    isMortgaged = false;
}

void Property::passBy(Player &p) { }

void Property::landOnAction(Player &p) {
    if (!owner || &p == owner || isMortgaged) return;
    double rent = calculateRent();
    p.forcePay(rent, owner);
}


bool Property::getMortgageStatus() const { return isMortgaged;}

double Property::getImproveValue() const { return 0; }

double Property::getTradableValue() const {
    if (isMortgaged) return 0;
    else return cost / 2 + getImproveValue();
}

int Property::getImproveNum() const { return -1; }

//double Property::getImproveCost() const { return 0; }

void Property::loadImproveNum(int improveNum) const {}

void Property::loadInfo(int improveNum, bool mortgaged) {
    isMortgaged = mortgaged;
    loadImproveNum(improveNum);
    notifyObservers();
}

void Property::addImprove() { throw NotAcademicBuilding{getName()}; }

void Property::removeImprove() { throw NotAcademicBuilding{getName()}; }
