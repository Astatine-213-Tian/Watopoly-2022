#include "osap.h"
#include "player.h"

OSAP::OSAP() : NonProperty{"COLLECT OSAP"} {}

void OSAP::passBy(Player &p) { p.receiveMoney(value); }
void OSAP::landOn(Player &p) { p.receiveMoney(value); }
