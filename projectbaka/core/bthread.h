#pragma once
#include "bakamain.h"
//thread class ,not yet totally finished ,but it works.
class bThread :ObjectBase{
protected:
	HANDLE b_thread;
	unsigned int t_state;
public:
	virtual ~bThread() = default;
	static const unsigned int STATE_THREAD_READY = 0x00000001;
	static const unsigned int STATE_THREAD_RUNING = 0x00000002;
	static const unsigned int STATE_THREAD_ACTION_FINISH = 0x00000003; 
	void start();
	virtual void action()= 0;
	void wait();
	unsigned int thread_state();
};
