#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include "needleshall.h"
#include "player.h"

using namespace std;

NH::NH(): NonProperty{"NEEDLES HALL"}, cards{vector<int>(18)}, rng{static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count())} {
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

vector<int> NH::curDeck;

void NH::passBy(Player &p) {}

void NH::landOnAction(Player &p) {
    if ((int)curDeck.size() == 0) {
        shuffle(cards.begin(), cards.end(), rng);
        curDeck = cards;
    }
    int firstCard = curDeck[0];
    curDeck.erase(curDeck.begin());

    if (firstCard > 0) {
        p.receiveMoney(firstCard);
    } else {
        p.forcePay(abs(firstCard));
    }
}