#ifndef _OSAP_H_
#define _OSAP_H_

#include "NonProperty.h"
class Player;

class OSAP: public NonProperty {
    const int value = 200;
public:
    void passBy(Player &p) override;
    void landOn(Player &p) override;
};

#endif