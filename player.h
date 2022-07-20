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
    bool moveToTims;
    int rollTimes;
    bool canRoll;

public:
    Player(std::string name, char displayChar, int timCups, double cash, int position);
    std::string getName() const;
    //std::vector<Property *> getProperties() const;
    double getCash() const;
    int getNumCup() const;
    void move(int index);
    void useCup();
    bool payMoney(double value);
    void receiveMoney(double value);
    bool inTims() const;
    void setToTimsLine();
    void setMoveToTims();
    bool shouldMoveToTims() const;
    void completeMoveToTims();
    void removeFromTimsLine();
    int getRollTimes() const;
    void addRollTimes();
    void initRollTimes();
    int getLocation() const;
    bool getRollState() const;
    void setRollState(bool state);
    void buyImprove(AcademicBuilding &ab);
    void sellImprove(AcademicBuilding &ab);
};

#endif