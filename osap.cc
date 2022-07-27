#include "osap.h"
#include "player.h"
#include <iostream>

using namespace std;

OSAP::OSAP() : NonProperty{"COLLECT OSAP"} {}

void OSAP::passBy(Player &p) {
    cout << "Lucky! You receive $200 support from OSAP!" << endl;
    p.receiveMoney(value);
}
void OSAP::landOnAction(Player &p) {
    cout << "Lucky! You receive $200 support from OSAP!" << endl;
    p.receiveMoney(value);
}
