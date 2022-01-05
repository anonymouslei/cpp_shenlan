#include "game.hpp"

namespace homework {
namespace game {
util::RoomType generate_room_type() {
  int type_num = util::generate_random_num(0, 100);
  //  std::srand(std::time(nullptr));
  //  int type_num = std::rand() % 100;
  if (type_num < 10) {
    return util::RoomType::camp;
  } else if (type_num < 65) {
    return util::RoomType::common;
  } else if (type_num < 80) {
    return util::RoomType::trap;
  } else if (type_num < 90) {
    return util::RoomType::header;
  } else {
    return util::RoomType::weapon;
  }
}

Game::Game() { explorer_ = figure::Explorer(); }

std::shared_ptr<room::Room> Game::create_room() {
  util::RoomType room_type = generate_room_type();
  //  util::RoomType room_type = util::RoomType::common;
  std::cout << "enter " << room_type << " room\n";
  switch (room_type) {
  case util::RoomType::camp:
    return std::make_shared<room::Camp>(explorer_);
  case util::RoomType::common:
    return std::make_shared<room::CommonRoom>(explorer_);
  case util::RoomType::trap:
    return std::make_shared<room::TrapRoom>(explorer_);
  case util::RoomType::header:
    return std::make_shared<room::HeaderRoom>(explorer_);
  case util::RoomType::weapon:
    return std::make_shared<room::WeaponRoom>(explorer_);
  }
}

void Game::run() {
  while (1) {
    // create room
    std::shared_ptr<room::Room> new_room = create_room();
    //    std::shared_ptr<room::Buff> new_buffer = new_room->create_buffer();
    //    buffers_.emplace_back(new_buffer);

    // enter room
    if (!new_room->enter_room())
      break;

    // run room
    if (!new_room->run())
      break;
    new_room->settlement();
  }
}

} // namespace game
} // namespace homework