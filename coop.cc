#include "coop.h"
#include "player.h"

Coop::Coop() : NonProperty{"COOP FEE"} {}

void Coop::passBy(Player &p) {}

void Coop::landOnAction(Player &p) {
    p.forcePay(fee);
}
