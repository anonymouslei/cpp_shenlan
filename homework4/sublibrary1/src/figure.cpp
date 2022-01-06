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
  if (experience_ > 10) {
    experience_ -= 10;
    std::cout << "experience is greater than 10, upgrade.\n";
    refill_health();
  }
}

int Explorer::get_experience() const { return experience_; }

std::string Explorer::get_name() const { return "explorer"; }

void Explorer::refill_health() {
  health_ = 100;
  std::cout << "refill explore full health, health (100/100)\n";
}

void Explorer::refill_health(int health) {
  health_ += health;
  health_ = health_ > 100 ? 100 : health_;
  std::cout << "refill explore " << health << " health, health (" << health_
            << "/100)\n";
}

void Explorer::get_buffer(RoomType room_type) {
  switch (room_type) {
    //  case RoomType::camp:
    //    buffers_.emplace_back(std::make_shared<CampBuff>());
    //    return;
  case RoomType::common:
    buffers_.emplace_back(std::make_shared<CommonBuff>());
    return;
  case RoomType::trap:
    buffers_.emplace_back(std::make_shared<TrapBuff>());
    return;
    //  case RoomType::header:
    //    buffers_.emplace_back(std::make_shared<HeaderBuff>());
    //    return;
  default:
    return;
  }
}

bool Explorer::apply_buffer() {
  for (auto it = buffers_.begin(); it != buffers_.end();) {
    std::shared_ptr<Buff> buffer = *it;
    refill_health(buffer->health_);
    buffer->remaining_num_--;
    if (buffer->remaining_num_ == 0)
      it = buffers_.erase(it);
    else
      ++it;
    if (is_dead())
      return false;
  }
  return true;
}

void Explorer::eraser_buffer() { buffers_.clear(); };

Monster::Monster(const int serial)
    : Human(util::generate_random_num(3, 7), util::generate_random_num(6, 14)),
      initial_health_(health_) {
  serial_ = serial;
  std::cout << "monster" << serial << " (" << initial_health_ << "/"
            << initial_health_ << ") ";
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