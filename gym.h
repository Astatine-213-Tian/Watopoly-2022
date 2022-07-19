#ifndef WATOPOLY__GYM_H_
#define WATOPOLY__GYM_H_

#include "property.h"
class Gym : public Property {
  double calculateRent() const override;
 public:
  explicit Gym(std::string name);
};

#endif //WATOPOLY__GYM_H_
