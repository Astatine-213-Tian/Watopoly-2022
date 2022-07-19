#ifndef WATOPOLY__DICE_H_
#define WATOPOLY__DICE_H_
#include <vector>

class Dice {
  std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
  int lastValue;
 public:
  int roll();
};

#endif //WATOPOLY__DICE_H_
