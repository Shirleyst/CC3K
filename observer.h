#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>
class Subject;
class Cell;
class Floor;

class Observer: public std::enable_shared_from_this<Observer> {
 public:
  virtual std::string notify(Floor &f, std::pair<int,int> coo, 
  	Subject &whoNotified) = 0;
  // pass the Cell that called the notify method
  virtual bool sameCell(std::pair <int, int> c) = 0;
  virtual int &getRow() = 0;
  virtual int &getCol() = 0;
  virtual ~Observer() = default;
};
#endif
