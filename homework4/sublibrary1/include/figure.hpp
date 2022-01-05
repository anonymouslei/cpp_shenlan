#pragma once
#include "util.hpp"

namespace homework {
namespace figure {

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

private:
  int experience_;
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