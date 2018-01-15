#ifndef DECORATOR_H
#define DECORATOR_H
#include "character.h"

class Decorator: public Character {
protected:
  std::shared_ptr<Character> component; // the player it will be used on
public:
  Decorator(std::shared_ptr<Character> component);
  std::string setApply() override;
  std::string potionType() override;
  ~Decorator();
};

#endif
