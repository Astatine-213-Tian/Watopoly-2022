#ifndef _TUITION_H_
#define _TUITION_H_

#include "NonProperty.h"
class Player;

class Tuition: public NonProperty {
public:
    void passBy(Player &p) override;
    void landOn(Player &p) override;
};

#endif