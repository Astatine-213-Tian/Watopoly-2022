#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include "dice.h"

using namespace std;

Dice::Dice(int min, int max) : diceNums{vector<int>(max - min + 1)}, rng{static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count())}, value{0} {
    iota(diceNums.begin(), diceNums.end(), min);
}

int Dice::getValue() const { return value; }

int Dice::roll() {
    shuffle(diceNums.begin(), diceNums.end(), rng );
    value = diceNums[0];
}

void Dice::setValue(int _v) { value = _v; }
