#include "osap.h"
#include "player.h"

void OSAP::passBy(Player &p) { p.receiveMoney(value); }

void OSAP::landOn(Player &p) { p.receiveMoney(value); }