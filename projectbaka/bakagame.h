
#include "bakamain.h"
class GameControl {
private:
	BakaEnvironment *ControlBaka;
public:
	virtual void Head() { return; }
	virtual void Tail() { return; }
	virtual void Gaming() { return; }
	virtual void Loading() { return; }
};