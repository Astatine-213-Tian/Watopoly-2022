#ifndef _NEEDLESHALL_H_
#define _NEEDLESHALL_H_

#include <vector>
#include <string>
#include <random>
#include "nonProperty.h"

class Player;
class Dice;

class NH: public NonProperty {
  static std::vector<int> cards;
  std::default_random_engine rng;
  std::unique_ptr<Dice> dice;
  static void initCard();

 public:
  NH();
  void passBy(Player &p) override;
  void landOnAction(Player &p) override;
};

#endif