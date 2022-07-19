#ifndef WATOPOLY__ERROR_H_
#define WATOPOLY__ERROR_H_

#include <stdexcept>

class Error : public std::exception {};

// throw when player is not authorized to do sth
class NotOwner : public Error {};
// throw when player try to improve an un-monopolized block
class NotMonopolized: public Error {};
// throw when a block reaches maximum improvement number
class MaxImprove: public Error {};
// throw when a block cannot be removed more improvement
class ZeroImprove: public Error {};

#endif //WATOPOLY__ERROR_H_
