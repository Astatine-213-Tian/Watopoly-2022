#include "property.h"
#include <utility>
#include "player.h"

Property::Property(std::string name, float cost): Cell{std::move(name)}, cost{cost}, owner{nullptr} {}

Player *Property::getOwner() const { return owner; }
void Property::setOwner(Player *p) { owner = p; }

float Property::getCost() const { return cost; }

void Property::passBy(Player &p) { return; }

void Property::landOn(Player &p) {
    float rent = calculateRent(p);

    if (&p == owner) return;
}
