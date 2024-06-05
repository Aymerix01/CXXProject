#pragma once
#include <vector>
#include <memory>
#include "EventCardListener.h"

class EventCardManager
{
private:
	std::vector<EventCardListener*> listeners;

public:
	EventCardManager() = default;

	void addEventCardListener(EventCardListener* listener);
	void notifyEventCardListeners() const;
};