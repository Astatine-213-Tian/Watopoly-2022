#include <utility>
#include "gym.h"
#include "player.h"
#include "Dice.h"

Gym::Gym(std::string name): Property{std::move(name), 150} {}

double Gym::calculateRent() const {
    int diceSum = 0;
    Dice d;
    diceSum += d.roll();
    diceSum += d.roll();
    
    int numGym = 0;
    for (auto p: owner->getProperties()) {
        if (dynamic_cast<Gym *>(p)) ++numGym;
    }

    if (numGym == 1) {
        return 4.0 * diceSum;
    } else {
        return 10.0 * diceSum;
    }
}