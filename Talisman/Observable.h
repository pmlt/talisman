#pragma once

#include <vector>
#include "Observer.h"

/*
  Class: Observable
  Represents an object that can be observed. Observers can
  be attached and detached to this object to received state 
  change notifications.
*/
class Observable
{
public:
	Observable(void);
	virtual ~Observable(void);

  void attach(Observer * o);
  void detach(Observer * o);
  void notify();

private:
  std::vector<Observer *> observers;
};

