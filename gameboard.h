#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include <vector>
#include <string>

class Cell;
class Property;
class Player;

class GameBoard {
    std::vector<Cell *> cells;
    std::vector<Property *> ownable;
    std::vector<Player *> players;
    Player *curPlayer;

public:
    void init();
	void roll();
	void next();
	Player *getCurPlayer();
	Player *getPlayer(std::string name);
	Property *getProperty(std::string name);
	void trade(Player &player, int value, Property &property);
	void trade(Player &player, Property &p1, Property &p2);
	void trade(Player &player, Property &property, int value);
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