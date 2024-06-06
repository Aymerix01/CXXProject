#include "EventCardManager.h"
#include <iostream>

void EventCardManager::addEventCardListener(EventCardListener* listener)
{
	listeners.push_back(listener);
}

void EventCardManager::notifyEventCardListeners(EventCard eventCard) const
{
	for (const auto& listener : listeners)
	{
		listener->onEventCard(eventCard);
	}
}
