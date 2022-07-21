#include <utility>
#include <iostream>
#include "property.h"
#include "player.h"

Property::Property(std::string name, double cost): Cell{std::move(name)}, cost{cost}, isMortgaged{false}, isMortgageChargePaid{false}, owner{nullptr} {}

Player *Property::getOwner() const { return owner; }

void Property::setOwner(Player *p) { owner = p; }

double Property::getCost() const { return cost; }

void Property::setMortgage() { isMortgaged = true;}

void Property::setUnMortgage() {
    isMortgaged = false;
    isMortgageChargePaid = false;
}

void Property::setAdditionChargePaid() { isMortgageChargePaid = true; }

double Property::getUnMortgageCost() const {
    if (isMortgageChargePaid) {
        return cost * 0.5;
    } else {
        return cost * 0.6;
    }
}

void Property::passBy(Player &p) { }

void Property::landOn(Player &p) {
    if (&p == owner) return;

    // TODO auction part
    if (!owner) {
        std::cout << "Do you want to buy the property? (y/n)" << std::endl;
        std::string ans;
        while (std::cin >> ans) {
            if (ans == "Y" || ans == "y" || ans == "Yes" || ans == "yes") {
                p.payMoney(cost);
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
    p.payMoney(rent);
    owner->receiveMoney(rent);
}


bool Property::getMortgageStatus() const {
    return isMortgaged;
}
