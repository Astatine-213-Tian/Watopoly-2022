#include "tuition.h"
#include "player.h"

using namespace std;

Tuition::Tuition() : NonProperty{"TUITION"} {}

void Tuition::passBy(Player &p) {}

void Tuition::landOnAction(Player &p) {
    p.setPayTuition(true);
}