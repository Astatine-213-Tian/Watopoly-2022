#include <utility>
#include "gym.h"
#include "player.h"
#include "dice.h"

Gym::Gym(std::string name): Property{std::move(name), 150} {}

double Gym::calculateRent() const {
    int diceSum = 0;
    Dice d;
    diceSum += d.roll();
    diceSum += d.roll();
    
    if (owner->getGym() == 1) {
        return 4.0 * diceSum;
    } else {
        return 10.0 * diceSum;
    }
}

void Gym::afterBoughtBy(Player &p) {
    p.addGym();
}
