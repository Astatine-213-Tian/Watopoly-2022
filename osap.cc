#include "osap.h"
#include "player.h"

OSAP::OSAP() : NonProperty{"COLLECT OSAP"} {}

void OSAP::passBy(Player &p) { p.receiveMoney(value); }
void OSAP::landOnAction(Player &p) { p.receiveMoney(value); }
