#ifndef WATOPOLY__DICE_H_
#define WATOPOLY__DICE_H_
#include <vector>

class Dice {
  std::vector<int> diceNums;
  int value;
 public:
  Dice(int min = 1, int max = 6);
  int getValue() const;
  void setValue(int _v);
  int roll();
};

#endif //WATOPOLY__DICE_H_
