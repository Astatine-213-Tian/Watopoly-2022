#include "goToTims.h"
#include "player.h"
#include "action.h"

GoToTims::GoToTims() : NonProperty{"GO TO TIMS"}, timsIndex{10} {}

void GoToTims::passBy(Player &p) {}

void GoToTims::landOn(Player &p) {
    throw sendToTims{};
}