#ifndef _COOP_H_
#define _COOP_H_

#include "nonProperty.h"
class Player;

class Coop: public NonProperty {
    const int fee = 150;
public:
    void passBy(Player &p) override;
    void landOn(Player &p) override;
};

#endif