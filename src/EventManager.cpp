#include "EventManager.h"

void EventManager::subscribe(const EventType& event, IEventListener* listener)
{
	std::vector<IEventListener*>& listeners = event_map[event];
	if (std::find(listeners.begin(), listeners.end(), listener) == listeners.end()) {
		listeners.push_back(listener);
	}
}

void EventManager::unsubscribe(IEventListener& entity)
{
	for (auto& [eventType, listeners] : event_map) {
		listeners.erase(
			std::remove(listeners.begin(), listeners.end(), &entity),
			listeners.end()
		);
	}
}

void EventManager::notify(const EventType& event)
{
	auto it = event_map.find(event);
	if (it != event_map.end()) {
		for (auto& listener : it->second) {
			listener->onEvent(event);
		}
	}
}

void EventManager::unsubscribeAll()
{
	for (auto& [eventType, listeners] : event_map) {
		listeners.clear();
	}
	event_map.clear();
}
