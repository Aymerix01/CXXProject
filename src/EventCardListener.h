#pragma once

enum class EventCard
{
	ATTACK,
	SHUFFLE,
	FUTURE,
	HAPPYPOINTS,
	ATTACKPOINTS,
	RESET,
};

class EventCardListener 
{

public:
	/**
	* \Brief Called when a card is played and send an event
	* \param eventCard : EventCard
	*/
	virtual void onEventCard(EventCard eventCard) = 0;

	/**
	* \Brief Destructor  
	*/
	virtual ~EventCardListener() = default;
};