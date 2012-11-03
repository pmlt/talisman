#pragma once

#include <vector>
#include "Observer.h"

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

