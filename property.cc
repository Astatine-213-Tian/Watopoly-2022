#include <utility>
#include "property.h"
#include "player.h"
#include "error.h"

Property::Property(std::string name, double cost): Cell{std::move(name)}, cost{cost}, owner{nullptr}, mortgage{false} {}

Player *Property::getOwner() const { return owner; }

void Property::setOwner(Player *p) {
    owner = p;
    notifyObservers();
}

double Property::getCost() const { return cost; }

void Property::setMortgage() {
    if (mortgage) throw PropertyStillMortgage{getName()};
    if (getImproveNum() > 0) throw BuildingStillWithImprove{getName()};
    owner->receiveMoney( cost / 2);
    mortgage = true;
}

void Property::setUnMortgage() {
    if (!mortgage) throw PropertyStillUnMortage{getName()};
    mortgage = false;
}

void Property::passBy(Player &p) { }

void Property::landOnAction(Player &p) {
    if (!owner || &p == owner || mortgage) return;
    double rent = calculateRent();
    p.forcePay(rent, owner);
}

bool Property::isMortgage() const { return mortgage;}

double Property::getImproveValue() const { return 0; }

double Property::getTradableValue() const {
    if (mortgage) return 0;
    else return cost / 2 + getImproveValue();
}

int Property::getImproveNum() const { return -1; }

void Property::initImproveNum(int improveNum) const {}

void Property::loadInfo(int improveNum, bool mortgaged) {
    mortgage = mortgaged;
    initImproveNum(improveNum);
    notifyObservers();
}

double Property::getImproveCost() const { return 0; }

void Property::addImprove() { throw NotAcademicBuilding{getName()}; }

void Property::removeImprove() { throw NotAcademicBuilding{getName()}; }

void Property::afterBoughtBy(Player &p) { }

void Property::boughtBy(Player &p, double price) {
    owner = &p;
    afterBoughtBy(p);
    p.forcePay(price);
}
