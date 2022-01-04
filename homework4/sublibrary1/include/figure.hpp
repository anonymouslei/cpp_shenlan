#pragma once
#include "util.hpp"

namespace homework {
namespace figure {

class Human {
public:
  Human(): attack_(0), health_(0) {};
  Human(const int attack, const int health): attack_(attack), health_(health) {};
//  ~Human();
//  virtual void print_info() const ;
  virtual bool is_dead();
  virtual void attacked(const int attack);
  virtual std::string get_name() const = 0;

  virtual int get_attack_value() const;

private:
  int attack_; //TODO: rename to attack
  int health_;
  bool dead = false;
};

class Explorer: public Human {
public:
  Explorer(): Human(100, 10), experience_(10) {};
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
//  ~Monster();
//  void print_info() const override ;
  std::string get_name() const override;
};

class MonsterHeader: public Monster {
public:
  MonsterHeader() {}; //TODO:
//  ~MonsterHeader();
//  void print_info() const override;
};

} // namespace figure
} // namespace homework