#include "EventCardManager.h"

void EventCardManager::addEventCardListener(EventCardListener* listener)
{
	listeners.push_back(listener);
}

void EventCardManager::notifyEventCardListeners() const 
{
	for (const auto& listener : listeners)
	{
		listener->onEventCard();
	}
}
