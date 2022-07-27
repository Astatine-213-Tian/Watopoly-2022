#ifndef _TIMSLINE_H_
#define _TIMSLINE_H_

#include <unordered_map>
#include "nonProperty.h"

class Player;

class TimsLine: public NonProperty {
    std::unordered_map<Player *, int> queue;
    
public:
    TimsLine();
    void passBy(Player &p) override;
    void landOnAction(Player &p) override;
    void addPlayerToLine(Player &p);
    int getPlayerRound(Player &p);
};

#endif
