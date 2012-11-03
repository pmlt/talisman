#pragma once
class Observer
{
public:
	Observer(void);
	virtual ~Observer(void);

  virtual void notify() = 0;
};

