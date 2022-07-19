#include <algorithm>
#include <random>
#include <chrono>
#include "dice.h"

Dice::Dice() : lastValue{0} {}

int Dice::getLastValue() { return lastValue; }

int Dice::roll() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle( v.begin(), v.end(), rng );
    lastValue = v[0];
    return lastValue;
}

void Dice::setValue(int v) { lastValue = v; }