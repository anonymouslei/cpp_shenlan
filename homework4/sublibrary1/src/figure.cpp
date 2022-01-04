#include "figure.hpp"

namespace homework {
namespace figure {

void Human::attacked(const int attack) {
  health_ -= attack;
}


bool Human::is_dead() {
  if (health_ < 0) {
    dead = true;
    std::cout << get_name() << " is dead\n";
    return true;
  }
  return false;
}

int Human::get_attack_value() const {
  return attack_;
}

void Explorer::add_experience(const int experience) {
  experience_ += experience;
}

int Explorer::get_experience() const {
    return experience_;
}

std::string Explorer::get_name() const {
  return "explorer";
}

Monster::Monster(): Human(util::generate_random_num(6,14), util::generate_random_num(3,7)) {
}

std::string Monster::get_name() const {
  return "monster";
}

} // figure
} // homework