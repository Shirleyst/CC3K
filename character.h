#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include <utility>
#include <iostream>
#include <string>
#include <memory>

class Character : public std::enable_shared_from_this<Character> {
  std::string race;
  int hp;
  int atk;
  int def;
  int gold;
  bool permission; // true if the player can pick/use this
  bool state; // true if the character used to attack merchant
public:
  Character();
  std::string &getRace();
  int &getHp();
  int &getAtk();
  int &getDef();
  int &getGold();
  virtual int &getMax();
  virtual bool &getPermiss();
  bool &getState();
  int getScore();

  virtual bool isE();
  bool isDead();
  virtual std::string potionType();

  virtual void printInfo();
  virtual void regain();
  virtual void displayInfo();
  void display(int x, int y);

  virtual std::string setApply();
  virtual int attack(std::shared_ptr<Character> whom);
  virtual int beAttacked(std::shared_ptr<Character> who);

  virtual ~Character() = 0;

  friend std::ostream &operator<<(std::ostream &out, Character &c);
};

#endif
