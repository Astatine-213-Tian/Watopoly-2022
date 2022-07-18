#ifndef _NONPROPERTY_H_
#define _NONPROPERTY_H_

#include "cell.h"
class Player;

class NonProperty: public Cell {
public:
    virtual void passBy(Player &p) = 0;
    virtual void landOn(Player &p) = 0;
};

#endif