#include "subject.h"
#include "observer.h"
#include <algorithm>
#include <string>

using namespace std;

// Subject::attach(o) puts o to the end of the observers
void Subject::attach(shared_ptr<Observer> o) {
  int s = observers.size();
  int r = o->getRow();
  int c = o->getCol();
  for(int i = 0; i < s; i++) {
    if(r == observers[i]->getRow() && c == observers[i]->getCol()) {
      return;
    }
  }
  observers.push_back(o);
  sort(observers.begin(), observers.end());
}

// Subject::dettach(o) dettach the given o
void Subject::dettach(shared_ptr<Observer> o){
  observers.erase(
     std::remove(observers.begin(), observers.end(), o), observers.end());
}

// Subject::getOb() returns the list of observers
vector<shared_ptr<Observer>> &Subject::getOb() {
  return observers;
}

// Subject::clearOb() clears the list of observers
void Subject::clearOb() {
  int s = observers.size();
  for(int i = 0; i < s; i++) {
    observers[i].reset();
  }
  observers.clear();
}

// Subject::notifyObservers(f, coo, ) notifies all members in observers 
//   with the given f and coo and returns the cooresponding info
string Subject::notifyObservers(Floor &f, pair<int,int> coo, Subject &) {
  string info = "";
  for(auto it = observers.begin(); it != observers.end(); ++it) {
  	string add = (*it)->notify(f, coo, *this);
  	if(add != "") {info += " " + add;}
  }
  return info;
}

// dtor
Subject::~Subject() {};
