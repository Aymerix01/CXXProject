#pragma once

enum class EventCard
{
	ATTACK,
	SHUFFLE,
	FUTURE,
	HAPPYPOINTS,
	ATTACKPOINTS,
};

class EventCardListener 
{

public:
	virtual void onEventCard(EventCard eventCard) = 0;

	virtual ~EventCardListener() = default;
};