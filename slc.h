#ifndef _SLC_H_
#define _SLC_H_

#include "nonProperty.h"
class Player;

class SLC: public NonProperty {
 public:
    SLC();
    void passBy(Player &p) override;
    void landOnAction(Player &p) override;
};

#endif