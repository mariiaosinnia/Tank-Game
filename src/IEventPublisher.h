#pragma once
#include "EventType.h"

class IEventPublisher {
public:
	virtual void publishEvent(const EventType& event) = 0;
	virtual ~IEventPublisher() = default;
};