
#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <experimental/random>
#include <iostream>

namespace homework {
namespace util {

enum RoomType { camp, common, trap, header, weapon };
// enumeration types (both scoped and unscoped) can have overloaded operators
std::ostream &operator<<(std::ostream &os, RoomType c);



int generate_random_num(const int begin, const int end);

} // namespace util
} // namespace homework

#endif