#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>
#include "needleshall.h"
#include "player.h"
#include "dice.h"

using namespace std;

NH::NH(): NonProperty{"NH"}, rng{static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count())}, dice{
    make_unique<Dice>(1, 100)} {}

vector<int> NH::cards;

void NH::passBy(Player &p) {}

void NH::initCard() {
    for (int i = 0; i < 2; i++) {
        cards.emplace_back(-100);
        cards.emplace_back(100);
    }
    for (int i = 0; i < 3; i++) {
        cards.emplace_back(-50);
        cards.emplace_back(50);
    }
    for (int i = 0; i < 6; i++) cards.emplace_back(25);

    cards.emplace_back(-200);
    cards.emplace_back(200);
}

void NH::landOnAction(Player &p) {
    if (dice->roll() == 23) {
        p.addCups(1);
        return;
    }
    if ((int)cards.size() == 0) {
        initCard();
        shuffle(cards.begin(), cards.end(), rng);
    }
    int firstCard = cards[0];
    cards.erase(cards.begin());
    if (firstCard > 0) {
        p.receiveMoney(firstCard);
    } else {
        p.forcePay(abs(firstCard));
    }
}
