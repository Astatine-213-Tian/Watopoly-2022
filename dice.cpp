#include <algorithm>
#include <random>
#include <chrono>
#include "dice.h"

Dice::Dice() : value{0} {}

int Dice::getValue() { return value; }

int Dice::roll() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle( v.begin(), v.end(), rng );
    value = v[0];
    return value;
}

void Dice::setValue(int v) { value = v; }

void Dice::init() { value = 0; }
