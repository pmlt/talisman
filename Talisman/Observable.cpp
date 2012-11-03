#include "stdafx.h"
#include "Observable.h"


Observable::Observable(void)
{
}


Observable::~Observable(void)
{
}

void Observable::attach(Observer * o)
{
  for (auto observer : this->observers) {
    if (observer == o) return; //Already in vector
  }
  this->observers.push_back(o);
}

void Observable::detach(Observer * o)
{
  for (auto i = this->observers.begin(); i != this->observers.end(); i++) {
    if (*i == o) {
      this->observers.erase(i);
      return;
    }
  }
}

void Observable::notify()
{
  for (auto observer : this->observers) {
    observer->notify();
  }
}