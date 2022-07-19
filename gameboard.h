#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include <vector>
#include <string>

class Cell;
class Property;
class AcademicBuilding;
class Player;
class Dice;

class GameBoard {
    std::vector<Cell *> cells;
    std::vector<Player *> players;
    Player *curPlayer;
    Dice *dice1;
    Dice *dice2;
	bool checkInTimsLine();
	// map, roll

public:
    void init();
	void roll(); // save dice val, check dice, check num double
    void roll(int d1, int d2);
	void next(); // check can next, 
	Player *getCurPlayer();
	Player *getPlayer(const std::string& name);
	Property *getProperty(const std::string& name);
    AcademicBuilding *getAcademicBuilding(const std::string& name);
	void trade(Player &player, double value, Property &property);
	void trade(Player &player, Property &p1, Property &p2);
	void trade(Player &player, Property &property, double value);
	void buyImprove(AcademicBuilding &ab);
	void sellImprove(AcademicBuilding &ab);
	void mortgage(Property &p);
	void unmortgage(Property &p);
	void assets(Player &p);
	void allAssets();
	void auction(int cellNum);
	bool isWin();
	void bankrupt();
};

#endif