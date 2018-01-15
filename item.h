#ifndef __ITEM_H__
#define __ITEM_H__
#include "decorator.h"

class Character;

class Item: public Decorator {
 public:
 	Item(std::shared_ptr<Character> c, std::string race, int type);
 	~Item();
};

#endif
