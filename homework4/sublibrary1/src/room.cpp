#include "room.hpp"

namespace homework {
namespace room {

// bool Room::enter_room( // TODO:
//    std::vector<std::shared_ptr<Buff>> &buffers) {
//   enter
//  for (auto i = buffers.end() - 1; i >= buffers.begin(); i--) {
//    (*i)->apply_buffer();
//  }
//  if (explorer_.is_dead())
//    return false;
//  return true;
//}

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

void Room::settlement() {
  // explorer get experience
  // print explorer health and experience
  std::cout << "explore get " << monster_num_ << " points experience, ";
  explorer_.add_experience(monster_num_);
  std::cout << "experience (" << explorer_.get_experience() << "/10)\n";
}

bool Room::run() {
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
  if (explorer_.apply_buffer())
    return false;
  return true;
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

} // namespace room
} // namespace homework