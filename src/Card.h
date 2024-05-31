#pragma once


class Card
{
public:
	Card() = default;
	virtual void play() = 0;

	virtual ~Card() = default;
};