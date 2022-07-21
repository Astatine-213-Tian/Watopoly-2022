#ifndef _TUITION_H_
#define _TUITION_H_

#include "nonProperty.h"
class Player;

class Tuition: public NonProperty {
 public:
  Tuition();
  void passBy(Player &p) override;
  void landOnAction(Player &p) override;
};

#endif