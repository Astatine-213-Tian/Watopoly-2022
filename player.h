#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>
class Property;

class Player {
    std::string name;
    std::vector<Property *> properties;
    double cash;
    int numCup;
    int curLocation;
    bool isInTimsLine;
    int rollTimes;
    bool canRoll;

public:
    Player(std::string name);
    std::string getName() const;
    std::vector<Property *> getProperties() const;
    double getCash() const;
    int getNumCup() const;
    void move(int index);
    void useCup();
    bool payMoney(double value);
    void receiveMoney(double value);
    void addProperty(Property &p);
    void removeProperty(Property &p);
    bool hasProperty(Property &p) const;
    void setToTimsLine();
    void removeFromTimesLine();
    int getrollTimes() const;
    void addRollTimes();
    void initRollTimes();
    int getLocation() const;
    void advanceCurLocation();
};

#endif