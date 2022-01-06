#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unistd.h>
#include <vector>

#include "figure.hpp"
#include "util.hpp"

namespace homework {
namespace room {

using namespace util;

class Room {
public:
  Room(RoomType room_type, figure::Explorer &explorer)
      : room_type_(room_type), explorer_(explorer){};
  //  ~Room();

  virtual bool enter_room() = 0;
  virtual void battle();
  virtual void settlement() const;
  virtual bool run();
  virtual void is_monsters_dead();

protected:
  std::vector<std::shared_ptr<figure::Monster>> monsters_;
  int monster_num_=0;
  figure::Explorer &explorer_;

private:
  util::RoomType room_type_;
};

class Camp : public Room {
public:
  Camp(figure::Explorer &explorer) : Room(RoomType::camp, explorer){};
  //  ~Camp();
  bool enter_room() override;
};

class CommonRoom : public Room {
public:
  CommonRoom(figure::Explorer &explorer);
  bool enter_room() override;
};

class TrapRoom : public Room {
public:
  TrapRoom(figure::Explorer &explorer);
  bool enter_room() override;
};

class HeaderRoom : public Room {
public:
  HeaderRoom(figure::Explorer &explorer) : Room(RoomType::header, explorer){};
  bool enter_room() override;
  void settlement() const override;
  void battle() override;
};

class WeaponRoom : public Room {
public:
  WeaponRoom(figure::Explorer &explorer) : Room(RoomType::weapon, explorer){};
  bool enter_room() override { return true; };
};

} // namespace room
} // namespace homework