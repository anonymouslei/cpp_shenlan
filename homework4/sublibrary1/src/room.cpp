#include "room.hpp"

namespace homework {
namespace room {

bool Room::enter_room(std::vector<std::shared_ptr<util::Buff>> &buffers) {
  // enter
  for (auto i = buffers.end() - 1; i >= buffers.begin(); i--) {
    (*i)->apply_buffer();
  }
  if (explorer_.is_dead())
    return false;
}

void Room::battle() {
  std::shared_ptr<figure::Monster> monster = *(monsters_.begin());
  monster->attacked(explorer_.get_attack_value());
  for (auto it = monsters_.begin(); it != monsters_.end(); ++it) {
    explorer_.attacked((*it)->get_attack_value());
  }
}

std::shared_ptr<util::Buff> Room::create_buffer() {
  return std::make_shared<util::Buff>();
}

void Room::settlement() {
  // explorer get experience
  // print explorer health and experience
  std::cout << "explore get " << monster_num_ << "points experience";
  explorer_.add_experience(monster_num_);
}

bool Room::run() {
  while (monsters_.empty()) {
    // battle
    battle();
    // monster dead
    is_monsters_dead();
    if (explorer_.is_dead())
      using namespace std::chrono_literals;
//    std::this_thread::sleep_for(2ms);
    return false;
  }
  return true;
}

void Room::is_monsters_dead() {
  for (auto it = monsters_.begin(); it != monsters_.end(); ++it) {
    if ((*it)->is_dead())
      it = monsters_.erase(it);
  }
}

CommonRoom::CommonRoom(figure::Explorer &explorer)
    : Room(util::RoomType::common, explorer) {
  monster_num_ = util::generate_random_num(1, 3);
  for (int i = 0; i < monster_num_; ++i) {
    monsters_.emplace_back(std::make_shared<figure::Monster>());
  }
//  std::sort(monsters_.begin(), monsters_.end(),
//            [](figure::Monster a, figure::Monster b) {
//              return a.get_attack_value() >= b.get_attack_value();
//            }); //TODO:
};
} // namespace room
} // namespace homework