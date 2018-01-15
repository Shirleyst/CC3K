#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "character.h"

class Enemy: public Character{
protected:
  bool isEnemy = true; // true if it is enemy to player
public:
  Enemy();
  bool isE() override;

  int attack(std::shared_ptr<Character> whom) override;
  int beAttacked(std::shared_ptr<Character> who) override;
  void dropGold(std::shared_ptr<Character> who);

  virtual ~Enemy() = 0;
};


#endif
