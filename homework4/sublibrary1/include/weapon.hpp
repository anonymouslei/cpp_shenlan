#pragma once

#include "util.hpp"
#include <string>

namespace homework {
namespace weapon {

enum WeaponType { type1, type2, type3 };
// enumeration types (both scoped and unscoped) can have overloaded operators
std::ostream &operator<<(std::ostream &os, WeaponType c);

struct Weapon1 {
  Weapon1()
      : attack_(4), durable_(6), name_("weapon1"), type_(WeaponType::type1){};
  Weapon1(int attack, int durable) : attack_(attack), durable_(durable){};
  int attack_;
  int durable_;
  std::string name_;
  WeaponType type_;

  virtual int use_weapon();
  virtual bool get_buff() const { return false; };
};

struct Weapon2 : public Weapon1 {
  Weapon2() : Weapon1(6, 6) {
    name_ = "weapon2";
    type_ = type2;
  };

  int use_weapon() override;
};

struct Weapon3 : public Weapon1 {
  Weapon3() : Weapon1(1, 6) {
    name_ = "weapon3";
    type_ = type3;
  }

  bool get_buff() const override;
};

} // namespace weapon
} // namespace homework