#include "figure.hpp"

namespace homework {
namespace figure {

void Human::attacked(const int attack) { health_ -= attack; }

bool Human::is_dead() {
  if (health_ < 0) {
    dead_ = true;
    std::cout << get_name() << " is dead\n";
    return true;
  }
  return false;
}

int Human::get_attack_value() const { return attack_; }

int Human::get_health_value() const { return health_; }

void Explorer::add_experience(const int experience) {
  experience_ += experience;
}

int Explorer::get_experience() const { return experience_; }

std::string Explorer::get_name() const { return "explorer"; }

Monster::Monster(const int serial)
//    : Human(util::generate_random_num(3, 7), 9),
: Human(util::generate_random_num(3, 7), util::generate_random_num(6, 14)),
            initial_health_(health_) {
          serial_ = serial;
          std::cout << "monster" << serial << " (" << initial_health_ << "/" << initial_health_ << ") ";
      };

std::string Monster::get_name() const { return "monster"; }

bool Monster::is_dead() {
  if (health_ < 0) {
    dead_ = true;
    std::cout << get_name() << serial_ << " is dead\n";
    return true;
  }
  return false;
}
} // namespace figure
} // namespace homework