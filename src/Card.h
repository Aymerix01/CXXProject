#pragma once

#include <string>
#include <pugixml.hpp>

class Card
{
protected:
	std::string name;

public:
	explicit Card(const pugi::xml_node& node);
	virtual void play() = 0;

	virtual ~Card() = default;
};