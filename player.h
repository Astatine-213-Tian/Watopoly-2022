#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>
class Property;
class AcademicBuilding;

class Player {
    std::string name;
    char displayChar;
    //std::vector<Property *> properties;
    double cash;
    int numCup;
    int curLocation;
    bool isInTimsLine;
    bool shouldMoveToTims;
    int rollTimes;
    bool canRoll;

public:
    Player(std::string name, char displayChar, int timCups, double cash, int position);
    std::string getName() const;
    double getCash() const;
    int getNumCup() const;
    void move(int index);
    void sentToTimsLine(int timsIndex);
    void useCup();
    void payMoney(double value);
    void receiveMoney(double value);
    bool inTimsLine() const;
    void setToTimsLine();
    void setShouldMoveToTims();
    bool getShouldMoveToTims() const;
    void removeFromTimsLine();
    int getRollTimes() const;
    void addRollTimes();
    void initRollTimes();
    int getLocation() const;
    bool getRollState() const;
    void setRollState(bool state);
    void mortgage(Property *p);
    void unmortgage(Property *p);
};

#endif