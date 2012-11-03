#pragma once

/*
  Class: Observer
  Represents an object that is interested in an Observable's 
  changes of states. It will receive notifications if attached
  to an Observable.
*/
class Observer
{
public:
	Observer(void);
	virtual ~Observer(void);

  virtual void notify() = 0;
};

