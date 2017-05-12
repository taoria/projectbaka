#pragma once
#include "core/bThread.h"
#include <queue>

class EventListener;
class Event;
//Event Thread is a thread that Listen to event in the game ,it will be initialized in the environment.
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
//Event is some message send by Event Thread to EventListener.
class BAKADLL Event {
public:
	const static DWORD STATE_KEY_EVENT = 0x01;
	const static DWORD STATE_MOUSE_LEFT_CLICK_EVENT = 0x02;
	const static DWORD STATE_MOUSE_RIGHT_CLICK_EVENT = 0x03;
	Event(DWORD event_message, DWORD event_type, b_id event_id);
	static DWORD get_key_code(char c);
	DWORD event_message;
	DWORD event_type;
	b_id event_id;
};

//Event Listener listen to event_thread to send back event and do actions to react.
//user register event function to bind itself to listen to some kind of events
class BAKADLL EventListener {
public:
	/**
	 * \brief 
	 * \param e 
	 */
	virtual void do_action(Event* e);
	void register_event(DWORD event_type);
};
