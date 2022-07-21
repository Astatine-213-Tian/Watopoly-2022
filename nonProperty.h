#ifndef _NONPROPERTY_H_
#define _NONPROPERTY_H_

#include "cell.h"

class NonProperty: public Cell {
 public:
  explicit NonProperty(const std::string&);
  virtual double getValue() const override;
};

#endif