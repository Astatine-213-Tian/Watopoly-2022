#include <utility>
#include "gym.h"
#include "player.h"
#include "dice.h"
#include <iostream>

using namespace std;

Gym::Gym(std::string name): Property{std::move(name), 150} {}

double Gym::calculateRent() const {
    Dice d;
    int r1 = d.roll();
    int r2 = d.roll();

    cout << "Dice 1: " << r1 << ", Dice 2: " << r2 << endl;

    int diceSum = r1 + r2;
    if (owner->getGym() == 1) {
        return 4.0 * diceSum;
    } else {
        return 10.0 * diceSum;
    }
}

void Gym::afterBoughtBy(Player &p) {
    p.addGym();
}
