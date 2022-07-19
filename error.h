#ifndef WATOPOLY__ERROR_H_
#define WATOPOLY__ERROR_H_

#include <stdexcept>

class Error : public std::exception {};

class NotOwner : public Error {};
class NotMonopolized: public Error {};
class MaxImprove: public Error {};
class ZeroImprove: public Error {};

#endif //WATOPOLY__ERROR_H_
