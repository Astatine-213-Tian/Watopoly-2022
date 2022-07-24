#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include <sstream>
#include "slc.h"
#include "player.h"

using namespace std;

SLC::SLC(): NonProperty{"SLC"}, cards{vector<string>(24)}, rng{static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count())} {
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

vector<string> SLC::curDeck;

void SLC::passBy(Player &p) {}

void SLC::landOnAction(Player &p) {
    if ((int)curDeck.size() == 0) {
        shuffle(cards.begin(), cards.end(), rng);
        curDeck = cards;
    }
    string firstCard = curDeck[0];
    curDeck.erase(curDeck.begin());
    istringstream option{firstCard};
    int moveDistance;

    if (option >> moveDistance) {
        p.setNumToMove(moveDistance);
    } else if (firstCard == "Tims") {
        p.setShouldMoveToTims();
    } else if (firstCard == "OSAP") {
        p.setGoToOSAP(true);
    }
}