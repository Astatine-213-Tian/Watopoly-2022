#ifndef _COOP_H_
#define _COOP_H_

#include "nonProperty.h"
class Player;

class Coop: public NonProperty {
  const int fee = 150;
public:
  Coop();
  void passBy(Player &p) override;
  void landOnAction(Player &p) override;
};

#endif
