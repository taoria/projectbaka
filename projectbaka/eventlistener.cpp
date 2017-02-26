
#include "eventlistener.h"

#include <queue>
std::queue<Event*> *event_list;
std::map<DWORD, std::vector<EventListener*>*> event_map;

EventThread::EventThread(BakaEnvironment* be): be(be) {
}

void EventThread::InitEventThread() {
	event_list = new std::queue<Event*>;

}

std::queue<Event*>* EventThread::GetEventQueue() {
	return event_list;
}
/**
* \brief
* \return
*/
Event* EventThread::GetEvent() {
	while (event_list->size() == 0);
	Event *temp = event_list->front();
	event_list->pop();
	return temp;
}

void EventThread::action() {
	Event *temp;
	while (temp = GetEvent()) {
		if (event_map[temp->event_type] != nullptr) {
			auto v = event_map[temp->event_type];
			if (!v->size()) {
				event_map.erase(temp->event_type);
				delete v;
			}
			for (EventListener *el : *v) {
				el->do_action(temp);
			}
		}
		delete temp;
	}
}

EventThread::~EventThread() {
}

void EventListener::do_action(Event* e) {
}


void EventListener::RegisterEvent(DWORD event_type) {
	if (!event_map[event_type])
		event_map[event_type] = new std::vector<EventListener*>;
	event_map[event_type]->push_back(this);

}
