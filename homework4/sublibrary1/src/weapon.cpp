#include "weapon.hpp"

namespace homework {
namespace weapon {

std::ostream &operator<<(std::ostream &os, WeaponType c) {
  switch (c) {
  case type1:
    os << "type1";
    break;
  case type2:
    os << "type2";
    break;
  case type3:
    os << "type3";
    break;
  default:
    os.setstate(std::ios_base::failbit);
  }
  return os;
}

int Weapon1::use_weapon() {
  std::cout << "*** the weapon durable: " << durable_ << " attack: " << attack_
            << std::endl;
  durable_--;
  if (durable_ == 0) {
    std::cout << "weapon is broken\n";
    return 0;
  }
  return attack_;
}

int Weapon2::use_weapon() {
  std::cout << "*** the weapon durable: " << durable_ << " attack: " << attack_
            << std::endl;
  durable_--;
  if (durable_ == 0) {
    std::cout << "weapon is broken\n";
    return 0;
  }
  return attack_--;
}

bool Weapon3::get_buff() const {
  if (util::generate_random_num(1, 100) < 50) {
    return true;
  }
  return false;
}

} // namespace weapon
} // namespace homework