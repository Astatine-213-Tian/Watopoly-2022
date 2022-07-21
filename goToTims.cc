#include "goToTims.h"
#include "player.h"

GoToTims::GoToTims() : NonProperty{"GO TO TIMS"} {}

void GoToTims::passBy(Player &p) {}

void GoToTims::landOn(Player &p) {
    p.setShouldMoveToTims();
}