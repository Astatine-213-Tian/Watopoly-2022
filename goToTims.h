#ifndef _GOTOTIMS_H_
#define _GOTOTIMS_H_

#include "nonProperty.h"
class Player;

class GoToTims: public NonProperty {
 public:
  GoToTims();
  void passBy(Player &p) override;
  void landOn(Player &p) override;
};

#endif