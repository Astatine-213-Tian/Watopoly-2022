#ifndef _NEEDLESHALL_H_
#define _NEEDLESHALL_H_

#include "nonProperty.h"
class Player;

class NH: public NonProperty {
 public:
    NH();
    void passBy(Player &p) override;
    void landOnAction(Player &p) override;
};

#endif