#pragma once
#include "util.hpp"
#include <memory>
#include <vector>

namespace homework {
namespace figure {
using namespace util;

struct Buff {
  Buff(int num, int health) : remaining_num_(num), health_(health){};
  int remaining_num_;
  int health_;
};

struct CommonBuff : public Buff {
  CommonBuff() : Buff(2, 5){};
};

struct TrapBuff : public Buff {
  TrapBuff() : Buff(5, -2){};
};

class Human {
public:
  Human() : attack_(0), health_(0){};
  Human(const int attack, const int health)
      : attack_(attack), health_(health){};
  //  ~Human();
  //  virtual void print_info() const ;
  virtual bool is_dead();
  virtual void attacked(const int attack);
  virtual std::string get_name() const = 0;

  virtual int get_attack_value() const;
  virtual int get_health_value() const;

protected:
  int health_;
  bool dead_ = false;

private:
  int attack_; // TODO: rename to attack
};

class Explorer : public Human {
public:
  Explorer() : Human(10, 100), experience_(0){};
  //  ~Explorer();

  //  void print_info() const override ;
  int get_experience() const;
  void add_experience(const int experience);
  std::string get_name() const override;
  void refill_health();
  void refill_health(int health);

  void get_buffer(util::RoomType room_type);
  bool apply_buffer();
  void eraser_buffer();

private:
  int experience_;
  std::vector<std::shared_ptr<Buff>> buffers_;
};

class Monster : public Human {
public:
  Monster();
  Monster(const int serial);
  //  ~Monster();
  //  void print_info() const override ;
  std::string get_name() const override;
  int get_serial() { return serial_; };
  int get_initial_health() { return initial_health_; };
  bool is_dead() override;

protected:
  int initial_health_;

private:
  int serial_;
};

class MonsterHeader : public Monster {
public:
  MonsterHeader(){}; // TODO:
  //  ~MonsterHeader();
  //  void print_info() const override;
};

} // namespace figure
} // namespace homework