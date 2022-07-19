#include "goToTims.h"
#include "player.h"
#include "action.h"

void GoToTims::passBy(Player &p) {}

void GoToTims::landOn(Player &p) {
    throw sendToTims{};
}