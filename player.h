#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
#include <vector>

class Player : public Character {
protected:
  int maxHP;
public:
  Player();
  int &getMax() override;
  void regain() override;

  int attack(std::shared_ptr<Character> whom) override;
  int beAttacked(std::shared_ptr<Character> who) override;
  void printInfo() override;
  void displayInfo() override;

  virtual ~Player() = 0;
};

#endif
