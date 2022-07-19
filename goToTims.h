#ifndef WATOPOLY__GOTOTIMS_H_
#define WATOPOLY__GOTOTIMS_H_

#include "nonProperty.h"

class Player;
class GoToTims : public NonProperty {
 public:
  GoToTims();
  void passBy(Player &p) override;
  void landOn(Player &p) override;
};

#endif //WATOPOLY__GOTOTIMS_H_
