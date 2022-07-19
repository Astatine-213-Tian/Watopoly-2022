#ifndef _NONPROPERTY_H_
#define _NONPROPERTY_H_

#include "cell.h"

class Player;
class NonProperty: public Cell {
 public:
  explicit NonProperty(const std::string&);
  ~NonProperty() override = 0;
};

#endif