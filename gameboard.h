#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include <vector>
#include <string>

class Cell;
class Property;
class Player;

class GameBoard {
    std::vector<Cell *> cells;
    std::vector<Player *> players;
	const int numPlayers;
    Player *curPlayer;
	int curPlayerIndex;
	bool checkInTimsLine();
	// map, roll

public:
    void init();
	void roll(); // save dice val, check dice, check num double
	void next(); // check can next, 
	Player *getCurPlayer();
	Player *getPlayer(std::string name);
	Property *getProperty(std::string name);
	void trade(Player &player, double value, Property &property);
	void trade(Player &player, Property &p1, Property &p2);
	void trade(Player &player, Property &property, double value);
	void buyImprove(Property &p);
	void sellImprove(Property &p);
	void mortgage(Property &p);
	void unmortgage(Property &p);
	void assets(Player &p);
	void allAssets();
	void auction(int cellNum);
	bool isWin();
	void bankrupt();
};

#endif