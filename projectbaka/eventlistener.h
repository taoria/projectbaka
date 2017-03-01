#pragma once
#include "core/bThread.h"
#include <queue>

class EventListener;
class Event;
class BAKADLL EventThread :public bThread {
private:
		BakaEnvironment* be;
public:
	explicit EventThread(BakaEnvironment* be);

	static void InitEventThread();
	std::queue<Event*>* GetEventQueue();
	static Event* GetEvent();
	void action() override;
	~EventThread() override;
};
class BAKADLL Event {
public:
	const static DWORD STATE_KEY_EVENT = 0x01;
	const static DWORD STATE_MOUSE_LEFT_CLICK_EVENT = 0x02;
	const static DWORD STATE_MOUSE_RIGHT_CLICK_EVENT = 0x03;
	Event(DWORD event_message, DWORD event_type, b_id event_id);
	static DWORD GetCharKeyCode(char c);
		
	DWORD event_message;
	DWORD event_type;
	b_id event_id;

};


class BAKADLL EventListener {
public:
	/**
	 * \brief 
	 * \param e 
	 */
	virtual void do_action(Event* e);
	void RegisterEvent(DWORD event_type);
};
