#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <string>
#include <memory>

class GameBoard;
class Player;

class Controller {
  std::unique_ptr<GameBoard> g;
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

 public:
  Controller();
//  bool askPlayerTradeResponse(Player *p);
  void addPlayers();
  void play();
  void load(const std::string& filename);
};

#endif