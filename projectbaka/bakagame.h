
#include "bakamain.h"
#pragma once
class BAKADLL GameControl {
private:
	BakaEnvironment *ControlBaka;
public:
	virtual void Head() { return; }
	virtual void Tail() { return; }
	virtual void Gaming() { return; }
	virtual void Loading() { return; }
	void Init(BakaEnvironment *be);
};