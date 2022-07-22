#include <utility>
#include <iostream>
#include "property.h"
#include "player.h"
#include "error.h"
#include "info.h"

Property::Property(std::string name, double cost): Cell{std::move(name)}, cost{cost}, owner{nullptr}, isMortgaged{false}, isMortgageInterestPaid{false} {}

Player *Property::getOwner() const { return owner; }

void Property::setOwner(Player *p) { owner = p; }

double Property::getCost() const { return cost; }

void Property::setMortgage() {
    if (isMortgaged) throw PropertyStillMortgage{name};
    if (getImproveNum() > 0) throw BuildingStillWithImprove{name};
    owner->receiveMoney( cost / 2);
    isMortgaged = true;
    isMortgageInterestPaid = false;
}

void Property::setUnMortgage() {
    if (!isMortgaged) throw PropertyStillUnMortage{name};
    double payment = cost * (isMortgageInterestPaid ? 0.5 : 0.6);
    owner->pay(payment);
    isMortgaged = false;
    isMortgageInterestPaid = false;
}

void Property::setMortgageInterestPaid() { isMortgageInterestPaid = true; }

void Property::passBy(Player &p) { }

void Property::landOnAction(Player &p) {
    if (&p == owner) return;

    // TODO auction part
    if (!owner) {
        std::cout << "Do you want to buy the property? (y/n)" << std::endl;
        std::string ans;
        while (std::cin >> ans) {
            if (ans == "Y" || ans == "y" || ans == "Yes" || ans == "yes") {
                p.forcePay(cost);
                owner = &p;
                return;
            } else if (ans == "N" || ans == "n" || ans == "No" || ans == "no") {
                return;
            } else {
                std::cout << "Please answer with y/n" << std::endl;
            }
        }
    }

    if (isMortgaged) return;

    double rent = calculateRent();
    p.forcePay(rent, owner);
}


bool Property::getMortgageStatus() const {
    return isMortgaged;
}

double Property::getValueWhenUnMortgage() const {
    return cost / 2;
}

double Property::getTradableValue() const {
    if (isMortgaged) return 0;
    else return getValueWhenUnMortgage();
}

int Property::getImproveNum() const { return 0; }

double Property::getImproveCost() const { return 0; }

void Property::loadImproveNum(int improveNum) const {};

void Property::loadInfo(int improveNum, bool mortgaged) {
    isMortgaged = mortgaged;
    loadImproveNum(improveNum);
}

void Property::addImprove() const { throw NotAcademicBuilding{name}; }

void Property::removeImprove() const { throw NotAcademicBuilding{name}; }

Info &Property::getInfo() {
    Info i;
    i.owner = owner->getDisplayChar();
    i.numImprove = numImprove;
    i.cellIndex = cellIndex;
    i.cellName = name;
    i.players = playersOnCell;

    return i;
}