#ifndef _GEESE_H_
#define _GEESE_H_

#include "NonProperty.h"
class Player;

class Geese: public NonProperty {
public:
    void passBy(Player &p);
    void landOn(Player &p);
};

#endif