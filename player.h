#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>
class Property;

class Player {
    std::string name;
    std::vector<Property *> properties;
    float cash;
    int numCup;
    bool isInTimsLine;
    int rollTimes;

public:
    Player(std::string name);
    std::string getName();
    std::vector<Property *> getProperties();
    float getCash();
    int getNumCup();
    void useCup();
    bool payMoney(float value);
    void receiveMoney(float value);
    void addProperty(Property &p);
    void removeProperty(Property &p);
    bool hasProperty(Property &p);
    void setToTimsLine();
    void removeFromTimesLine();
    int getrollTimes() const;
    void addRollTimes();
    void initRollTimes();
};

#endif