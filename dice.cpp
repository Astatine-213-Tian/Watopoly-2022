#include <algorithm>
#include <random>
#include <chrono>
#include "dice.h"

int Dice::roll() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle( v.begin(), v.end(), rng );
    lastValue = v[0];
    return lastValue;
}