#ifndef _NEEDLESHALL_H_
#define _NEEDLESHALL_H_

#include "nonProperty.h"
class Player;

class NH: public NonProperty {
    std::vector<int> cards;
    static std::vector<int> curDeck;
    std::default_random_engine rng;
 public:
    NH();
    void passBy(Player &p) override;
    void landOnAction(Player &p) override;
};

#endif