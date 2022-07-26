#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <sstream>
#include "slc.h"
#include "player.h"
#include "dice.h"

using namespace std;

SLC::SLC(): NonProperty{"SLC"}, rng{static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count())}, dice{
    make_unique<Dice>(1, 100)} {}

vector<string> SLC::cards;

void SLC::passBy(Player &p) {}

void SLC::initCard() {
    for (int i = 0; i < 3; i++) {
        cards.emplace_back("-3");
        cards.emplace_back("1");
    }
    for (int i = 0; i < 4; i++) {
        cards.emplace_back("-2");
        cards.emplace_back("-1");
        cards.emplace_back("2");
        cards.emplace_back("3");
    }
    cards.emplace_back("OSAP");
    cards.emplace_back("Tims");
}

void SLC::landOnAction(Player &p) {
    if (dice->roll() == 23) {
        p.addCups(1);
        return;
    }

    if ((int)cards.size() == 0) {
        initCard();
        shuffle(cards.begin(), cards.end(), rng);
    }
    string firstCard = cards[0];
    cards.erase(cards.begin());
    istringstream option{firstCard};
    int moveDistance;

    if (option >> moveDistance) {
        p.setNumToMove(moveDistance);
    } else if (firstCard == "Tims") {
        p.setGoToTims();
    } else if (firstCard == "OSAP") {
        p.setGoToOSAP(true);
    }
}