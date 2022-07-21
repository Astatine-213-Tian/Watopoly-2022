#include <utility>
#include <iostream>
#include "property.h"
#include "player.h"
#include "error.h"

Property::Property(std::string name, double cost): Cell{std::move(name)}, cost{cost}, owner{nullptr}, isMortgaged{false}, isMortgageInterestPaid{false}, numImprove{0} {}

Player *Property::getOwner() const { return owner; }

void Property::setOwner(Player *p) { owner = p; }

double Property::getCost() const { return cost; }

void Property::setMortgage() {
    isMortgaged = true;
    isMortgageInterestPaid = false;
}

void Property::setUnMortgage() {
    isMortgaged = false;
    isMortgageInterestPaid = false;
}

void Property::setMortgageInterestPaid() { isMortgageInterestPaid = true; }

double Property::getUnMortgageCost() const {
    if (isMortgageInterestPaid) {
        return cost * 0.5;
    } else {
        return cost * 0.6;
    }
}

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

void Property::initImprove(int improveNum) const { }

void Property::addImprove() const { throw NotAcademicBuilding{name}; }

void Property::removeImprove() const { throw NotAcademicBuilding{name}; }

