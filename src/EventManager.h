#pragma once
#include <unordered_map>
#include "IEventListener.h"
#include "EventType.h"

class EventManager
{
private:
	std::unordered_map<EventType, std::vector<IEventListener*>> event_map;
public:
	EventManager(){}
	void subscribe(const EventType& event, IEventListener* listener);
	void unsubscribe(IEventListener& entity);
	void notify(const EventType& event);
	void unsubscribeAll();
};

