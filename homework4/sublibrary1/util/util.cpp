#include "util.hpp"

namespace homework {
namespace util {

std::ostream &operator<<(std::ostream &os, RoomType c) {
  switch (c) {
  case camp:
    os << "camp";
    break;
  case common:
    os << "common";
    break;
  case trap:
    os << "trap";
    break;
  case header:
    os << "header";
    break;
  case weapon:
    os << "weapon";
    break;
  default:
    os.setstate(std::ios_base::failbit);
  }
  return os;
}

void Buff::apply_buffer() {
  std::cout << "apply buffer\n";
}

int generate_random_num(const int begin, const int end) {
  std::experimental::reseed();
  return std::experimental::randint(begin, end);
}
}
}