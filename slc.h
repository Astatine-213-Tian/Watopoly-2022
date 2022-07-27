#ifndef _SLC_H_
#define _SLC_H_

#include <vector>
#include <string>
#include <random>
#include "nonProperty.h"

class Player;
class Dice;

class SLC: public NonProperty {
    static std::vector<std::string> cards;
    std::default_random_engine rng;
    std::unique_ptr<Dice> dice;
    static void initCard();

 public:
    SLC();
    void passBy(Player &p) override;
    void landOnAction(Player &p) override;
};

#endif
