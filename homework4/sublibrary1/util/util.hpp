
#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <experimental/random>
#include <iostream>

namespace homework {
namespace util {

enum RoomType { camp, common, trap, header, weapon };
// enumeration types (both scoped and unscoped) can have overloaded operators
std::ostream &operator<<(std::ostream &os, RoomType c);

class Buff {
public:
  Buff(): room_buf(RoomType::common), remaining_num(2) {}; // TODO:
//  ~Buff();
  void apply_buffer();

private:
  RoomType room_buf;
  int remaining_num;
};
//TODO: other buffers

int generate_random_num(const int begin, const int end);

} // namespace util
} // namespace homework

#endif