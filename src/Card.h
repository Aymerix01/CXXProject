#pragma once

#include <string>
#include <pugixml.hpp>
#include <memory>

class Player;
class Card
{
protected:
	std::string name;

public:
	explicit Card(const pugi::xml_node& node);
	virtual void play() = 0;
	virtual std::string getName() const;

	virtual ~Card() = default;
};