#pragma once

#include "Card.h"
#include <string>
#include <pugixml.hpp>

class ExplodingCard : public Card
{
public:
	explicit ExplodingCard(const pugi::xml_node& node);
	void play() override;
};
