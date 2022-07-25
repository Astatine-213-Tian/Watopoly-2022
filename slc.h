#ifndef _SLC_H_
#define _SLC_H_

#include <vector>
#include <string>
#include <random>
#include "nonProperty.h"

class Player;

class SLC: public NonProperty {
    std::vector<std::string> cards;
    static std::vector<std::string> curDeck;
    std::default_random_engine rng;

 public:
    SLC();
    void passBy(Player &p) override;
    void landOnAction(Player &p) override;
};

#endif