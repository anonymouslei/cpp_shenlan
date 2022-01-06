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

int Human::get_attack_value() { return attack_; }

int Human::get_health_value() const { return health_; }

void Human::refill_health() {
  health_ = 100;
  std::cout << "refill " << get_name()
            << "full health, health (100/100)\n"; // TODO:
}

void Human::refill_health(int health) {
  health_ += health;
  health_ = health_ > initial_health_ ? initial_health_ : health_;
  std::cout << "refill " << get_name() << " " << health << " health, health ("
            << health_ << "/" << initial_health_ << ")\n";
}

void Explorer::add_experience(const int experience) {
  experience_ += experience;
  if (experience_ > 10) {
    experience_ -= 10;
    std::cout << "experience is greater than 10, upgrade.\n";
    refill_health();
  }
}

void Explorer::set_health(const int health) { health_ = health; }

int Explorer::get_experience() const { return experience_; }

int Explorer::get_attack_value() {
  int attack;
  int weapon_attack = 0;
  if (has_weapon_) {
    weapon_attack = weapon_->use_weapon();
    attack = attack_ + weapon_attack;
  } else
    attack = attack_;
  if (has_weapon_ && weapon_attack == 0) {
    has_weapon_ = false;
  }

  return attack;
}
std::string Explorer::get_name() const { return "explorer"; }

void Explorer::get_buffer(RoomType room_type) {
  switch (room_type) {
  case RoomType::common:
    buffers_.emplace_back(std::make_shared<CommonBuff>());
    return;
  case RoomType::trap:
    buffers_.emplace_back(std::make_shared<TrapBuff>());
    return;
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

void Explorer::get_weapon(std::unique_ptr<weapon::Weapon1> weapon) {
  has_weapon_ = true;
  weapon_ = std::move(weapon);
  std::cout << "explorer get a weapon: " << weapon_->type_ << std::endl;
}

Monster::Monster() : Human(5 * 2, 10 * 2) {
  serial_ = 1;
  std::cout << "monster" << serial_ << " (" << initial_health_ << "/"
            << initial_health_ << ") ";
}

Monster::Monster(const int serial)
    : Human(util::generate_random_num(3, 7), util::generate_random_num(6, 14)) {
  serial_ = serial;
  std::cout << "monster" << serial_ << " (" << initial_health_ << "/"
            << initial_health_ << ") ";
};

std::string Monster::get_name() const { return "monster"; }

bool Monster::is_dead() {
  if (health_ < 1) {
    dead_ = true;
    std::cout << get_name() << serial_ << " is dead\n";
    return true;
  }
  return false;
}

MonsterHeader::MonsterHeader() : Monster(15, 40) {}

std::string MonsterHeader::get_name() const { return "MonsterHeader"; }

void MonsterHeader::enhance_attack_power() { attack_ += 1; }

void MonsterHeader::refill_health() {
  refill_health();
  buff_ = false;
}
} // namespace figure
} // namespace homework