#pragma once

#include <string>
#include <pugixml.hpp>
#include <memory>

class Deck;
class Card
{
private:
	std::string name;

public:
	explicit Card(const pugi::xml_node& node);
	virtual void play(Deck& deck) = 0;
	virtual std::string getName() const;
	virtual std::string getClassType() const = 0;

	virtual ~Card() = default;
};