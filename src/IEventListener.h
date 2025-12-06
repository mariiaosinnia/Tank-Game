#pragma once
#include "EventType.h"

class IEventListener {
public:
	virtual void onEvent(const EventType& event) = 0;
	virtual ~IEventListener() = default;
};