#ifndef _OSAP_H_
#define _OSAP_H_

#include "NonProperty.h"
class Player;

class OSAP: public NonProperty {
    const int value = 200;
public:
    void passBy(Player &p);
    void landOn(Player &p);
};

#endif