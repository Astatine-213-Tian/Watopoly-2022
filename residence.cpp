#include <utility>
#include "residence.h"
#include "player.h"

Residence::Residence(std::string name) : Property{std::move(name), 200} {}

double Residence::calculateRent() const {
    int numRes = owner->getRes();
    if (numRes == 1) return 25;
    else if (numRes == 2) return 50;
    else if (numRes == 3) return 100;
    else return 200;
}
