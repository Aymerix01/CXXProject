#pragma once

#include "Card.h"
#include <string>

class ExplodingCard : public Card
{
private:
	std::string name;

public:
	explicit ExplodingCard(const std::string& name);
	void play() override;
};
