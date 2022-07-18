#ifndef _TIMSLINE_H_
#define _TIMSLINE_H_

#include <unordered_map>
#include "NonProperty.h"

class Player;

class TimsLine: public NonProperty {
    std::unordered_map<Player *, int> queue;
    
public:
    void passBy(Player &p);
    void landOn(Player &p);
    void addPlayerToLine(Player &p);
    int getPlayerRound(Player &p);
};

#endif