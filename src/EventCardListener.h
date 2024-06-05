#pragma once

class EventCardListener 
{

public:
	virtual void onEventCard() = 0;

	virtual ~EventCardListener() = default;
};