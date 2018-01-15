#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <string>
#include <vector>
#include <string>
#include <memory>
class Observer;
class Floor;

class Subject {
  std::vector<std::shared_ptr<Observer>> observers;
 public:
  void attach(std::shared_ptr<Observer> o);
  void dettach(std::shared_ptr<Observer> o);
  std::vector<std::shared_ptr<Observer>> &getOb();
  void clearOb();
  
  std::string notifyObservers(Floor &f, std::pair<int,int> coo, Subject &);
  
  virtual ~Subject() = 0;
};

#endif
