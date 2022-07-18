#ifndef _TUITION_H
#define _TUITION_H_

#include "NonProperty.h"
class Player;

class Tuition: public NonProperty {
public:
    void passBy(Player &p);
    void landOn(Player &p);
};

#endif