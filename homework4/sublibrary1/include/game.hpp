#pragma once

#include <array>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "util.hpp"
#include "figure.hpp"
#include "room.hpp"

namespace homework {
namespace game {

util::RoomType generate_room_type();

class Game {
public:
  Game();
//  ~Game();

//  void init();
  std::shared_ptr<room::Room> create_room();
  void run();
//  void summary();

private:
  figure::Explorer explorer_;
  std::array<int, 5> rooms_number_{0,0,0,0,0};
  std::vector<std::shared_ptr<util::Buff>> buffers_;
};

} // namespace game
} // namespace homework