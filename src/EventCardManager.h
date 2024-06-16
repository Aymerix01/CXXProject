#pragma once
#include <vector>
#include <memory>
#include "EventCardListener.h"

class EventCardManager
{
private:
	std::vector<EventCardListener*> listeners;

public:
	/**
	* Default EventCardManager constructor
	*/
	EventCardManager() = default;

	/**
	* \Brief Adds a listener to the list of listeners
	* \Param listener : EventCardListener*
	*/
	void addEventCardListener(EventCardListener* listener);

	/**
	* \Brief notify all listeners of an event card
	* \Param eventCard : EventCard
	*/
	void notifyEventCardListeners(EventCard eventCard) const;
};