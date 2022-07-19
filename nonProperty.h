#ifndef _NONPROPERTY_H_
#define _NONPROPERTY_H_

#include "cell.h"

class NonProperty: public Cell {
 public:
  explicit NonProperty(const std::string&);
};

#endif