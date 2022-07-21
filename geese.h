#ifndef _GEESE_H_
#define _GEESE_H_

#include "nonProperty.h"
class Player;

class Geese: public NonProperty {
 public:
  Geese();
  void passBy(Player &p) override;
  void landOnAction(Player &p) override;
};

#endif