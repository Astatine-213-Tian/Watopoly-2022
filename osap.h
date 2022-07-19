#ifndef _OSAP_H_
#define _OSAP_H_

#include "nonProperty.h"
class Player;

class OSAP: public NonProperty {
  const int value = 200;
 public:
  OSAP();
  void passBy(Player &p) override;
  void landOn(Player &p) override;
};

#endif