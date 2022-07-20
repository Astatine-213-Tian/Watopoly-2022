#include <utility>
#include <iostream>
#include "property.h"
#include "player.h"

Property::Property(std::string name, double cost): Cell{std::move(name)}, cost{cost}, isMortgaged{false}, owner{nullptr} {}

Player *Property::getOwner() const { return owner; }

void Property::setOwner(Player *p) { owner = p; }

double Property::getCost() const { return cost; }

void Property::setMortgage() { isMortgaged = true; }

void Property::setUnMortgage() { isMortgaged = false; }

void Property::passBy(Player &p) { }

void Property::landOn(Player &p) {
    if (&p == owner) return;

    if (!owner) {
        bool buy = false;
        std::cout << "Do you want to buy the property? (y/n)" << std::endl;
        std::string ans;
        while (std::cin >> ans) {
            if (ans == "Y" || ans == "y" || ans == "Yes" || ans == "yes") {
                buy = true;
                break;
            } else if (ans == "N" || ans == "n" || ans == "No" || ans == "no") {
                buy = false;
                break;
            } else {
                std::cout << "Please answer with y/n" << std::endl;
            }
        }
        if (!buy) return;
        p.payMoney(cost);
        // p.addProperty(*this);
        owner = &p;
    }

    double rent = calculateRent();
    p.payMoney(rent);
    owner->receiveMoney(rent);
}
