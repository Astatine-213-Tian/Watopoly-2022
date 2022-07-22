#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <string>
#include <memory>

class GameBoard;
class Player;

class Controller {
  GameBoard *g = nullptr;
//  void processUsualCmd(const std::string &cmd);
  void next();
  void roll();
  void trade();
  void improve();
  void mortgage();
  void unmortgage();
  void payDebt();
  void bankrupt();
  void save(std::string& filename);
  bool yesOrNoResponse();

 public:
  Controller();
  void setGameBoard(GameBoard *gb);
//  bool askPlayerTradeResponse(Player *p);
  void addPlayers();
  void play();
  void load(const std::string& filename);
  bool askTradeResponse(const std::string &curName, const std::string &toName, const std::string &curGive, const std::string &curReceive);
};

#endif