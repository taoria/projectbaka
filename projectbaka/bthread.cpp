#include"core/bThread.h"
DWORD WINAPI ThreadFunction(void *args) {
	bThread  *temp = static_cast<bThread*>(args);
	temp->action();
	return TRUE;
}
/**
 * \brief 
 */
void bThread::start() {
	this->t_state = STATE_THREAD_RUNING;
	b_thread = CreateThread(NULL, 0, ThreadFunction, this, 0, NULL);
	if(b_thread) {
		LPDWORD lpdword_state = nullptr;
		CloseHandle(b_thread);
	}else {
		DebugBox("Warning:Thread Create Fail");
	}
}

unsigned int  bThread::thread_state() {

	return this->t_state;
}

