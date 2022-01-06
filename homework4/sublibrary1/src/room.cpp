#include "room.hpp"

namespace homework {
namespace room {

void Room::battle() {
  std::shared_ptr<figure::Monster> monster = *(monsters_.begin());
  monster->attacked(explorer_.get_attack_value());
  std::cout << "Explorer attack monster" << monster->get_serial() << ", cause "
            << explorer_.get_attack_value() << " points damage, Monster"
            << monster->get_serial() << " (" << monster->get_health_value()
            << "/" << monster->get_initial_health() << ")\n"; // TODO: func
  is_monsters_dead();
  if (monsters_.empty())
    return;
  for (auto it = monsters_.begin(); it != monsters_.end(); ++it) {
    int damage = (*it)->get_attack_value();
    explorer_.attacked(damage);
    std::cout << "Monster" << (*it)->get_serial() << " attack explorer, cause "
              << damage << " points damage, Explorer ("
              << explorer_.get_health_value() << "/100)\n";
  }
}

void Room::settlement() const {
  // explorer get experience
  // print explorer health and experience
  std::cout << "explore get " << monster_num_ << " points experience, ";
  explorer_.add_experience(monster_num_);
  std::cout << "experience (" << explorer_.get_experience() << "/10)\n";
}

bool Room::run() {
  std::cout << "***** debug: run" << std::endl;
  while (!monsters_.empty()) {
    // battle
    battle();
    // monster dead
    if (explorer_.is_dead()) {
      return false;
    }
    //    sleep(1);
  }
  return true;
}

void Room::is_monsters_dead() {
  for (auto it = monsters_.begin(); it != monsters_.end();) {
    if ((*it)->is_dead())
      it = monsters_.erase(it);
    else
      ++it;
  }
}

bool Camp::enter_room() {
  explorer_.refill_health();
  return explorer_.apply_buffer();
}

CommonRoom::CommonRoom(figure::Explorer &explorer)
    : Room(RoomType::common, explorer) {
  monster_num_ = util::generate_random_num(1, 3);
  std::cout << "meet " << monster_num_ << " monster, ";
  for (int i = 0; i < monster_num_; ++i) {
    monsters_.emplace_back(std::make_shared<figure::Monster>(i + 1));
  }
  std::cout << std::endl;
  //  std::sort(monsters_.begin(), monsters_.end(),
  //            [](figure::Monster a, figure::Monster b) {
  //              return a.get_attack_value() >= b.get_attack_value();
  //            }); //TODO:
};

bool CommonRoom::enter_room() {
  if (util::generate_random_num(1, 100) < 10) {
    explorer_.refill_health(10);
    explorer_.apply_buffer();
    explorer_.get_buffer(RoomType::common);
  } else {
    explorer_.apply_buffer();
  }
  if (explorer_.is_dead())
    return false;
  return true;
}

TrapRoom::TrapRoom(figure::Explorer &explorer)
    : Room(RoomType::trap, explorer) {
  monster_num_ = 1;
  std::cout << "meet " << monster_num_ << " monster, ";
  monsters_.emplace_back(std::make_shared<figure::Monster>());
}

bool TrapRoom::enter_room() {
  explorer_.refill_health(-explorer_.get_health_value() * 0.1);
  explorer_.apply_buffer();
  explorer_.get_buffer(RoomType::trap);
  if (explorer_.is_dead())
    return false;
  return true;
}

bool HeaderRoom::enter_room() {
  explorer_.refill_health(20);
  explorer_.eraser_buffer();
  return true;
}

void HeaderRoom::settlement() const {
  // explorer get experience
  // print explorer health and experience
  std::cout << "explore get " << monster_num_ * 5 << " points experience, ";
  explorer_.add_experience(monster_num_ * 5);
  std::cout << "experience (" << explorer_.get_experience() << "/10)\n";
}

void HeaderRoom::battle() {
  std::shared_ptr<figure::Monster> monster = *(monsters_.begin());

  monster->attacked(explorer_.get_attack_value());
  std::cout << "Explorer attack monster" << monster->get_serial() << ", cause "
            << explorer_.get_attack_value() << " points damage, Monster"
            << monster->get_serial() << " (" << monster->get_health_value()
            << "/" << monster->get_initial_health() << ")\n"; // TODO: func
  is_monsters_dead();
  if (monsters_.empty())
    return;

  if (monster->get_health_value() <= 9 && monster->get_buff()) {
    monster->refill_health(20);
  } else {
    monster->enhance_attack_power();
    int damage = (monster)->get_attack_value();
    explorer_.attacked(damage);
    std::cout << "MonsterHeader" << (monster)->get_serial() << " attack explorer, cause "
              << damage << " points damage, Explorer ("
              << explorer_.get_health_value() << "/100)\n";
  }
}
} // namespace room
} // namespace homework