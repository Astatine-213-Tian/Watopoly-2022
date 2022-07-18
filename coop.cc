#include "coop.h"
#include "player.h"

void Coop::passBy(Player &p) {}

void Coop::landOn(Player &p) {
    p.payMoney(fee);
}