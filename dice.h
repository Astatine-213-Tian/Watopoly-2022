#ifndef WATOPOLY__DICE_H_
#define WATOPOLY__DICE_H_
#include <vector>

class Dice {
  std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
  int value;
 public:
  Dice();
  void init();
  int getValue();
  void setValue(int value);
  int roll();
};

#endif //WATOPOLY__DICE_H_
