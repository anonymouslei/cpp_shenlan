#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "figure.hpp"
#include "util.hpp"

namespace homework {
namespace room {



class Room {
public:
  Room(util::RoomType room_type, figure::Explorer &explorer)
      : room_type_(room_type), explorer_(explorer){};
//  ~Room();

  virtual bool enter_room(std::vector<std::shared_ptr<util::Buff>> &buffers);
  virtual void battle();
  virtual std::shared_ptr<util::Buff> create_buffer();
  virtual void settlement();
  virtual bool run();
  virtual void is_monsters_dead();

protected:
  std::vector<std::shared_ptr<figure::Monster>> monsters_;
  int monster_num_;

private:
  util::RoomType room_type_;
  figure::Explorer &explorer_;
};

class Camp : public Room {
public:
  Camp(figure::Explorer &explorer) : Room(util::RoomType::camp, explorer){};
//  ~Camp();
};

class CommonRoom : public Room {
public:
  CommonRoom(figure::Explorer &explorer);
};

class TrapRoom : public Room {
public:
  TrapRoom(figure::Explorer &explorer) : Room(util::RoomType::trap, explorer){};
};

class HeaderRoom : public Room {
public:
  HeaderRoom(figure::Explorer &explorer) : Room(util::RoomType::header, explorer){};
};

class WeaponRoom : public Room {
public:
  WeaponRoom(figure::Explorer &explorer) : Room(util::RoomType::weapon, explorer){};
};

} // namespace room
} // namespace homework