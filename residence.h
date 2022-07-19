#ifndef WATOPOLY__RESIDENCE_H_
#define WATOPOLY__RESIDENCE_H_

#include "property.h"
class Residence : public Property {
  double calculateRent() const override;
 public:
  explicit Residence(std::string name);
};

#endif //WATOPOLY__RESIDENCE_H_
