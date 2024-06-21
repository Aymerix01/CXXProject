#include "Card.h"
#include "EventCardListener.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Card::Card(const pugi::xml_node& node, EventCardManager& eventCardManager) : classType(node.name()),
	name(node.attribute("name").as_string()), eventCardManager(eventCardManager)
{
	std::ostringstream ostringstreamSpritePath;
	ostringstreamSpritePath << "resources/"<< classType << "-" << string(node.attribute("name").as_string()) << ".png";
	if (std::string spritePath = ostringstreamSpritePath.str();
		!cardTexture.loadFromFile(spritePath))
	{
		std::cerr << "Error loading texture" << std::endl;
	}
	cardSprite.setTexture(cardTexture);
}

string Card::getName() const
{
	return name;
}

string Card::getClassType() const
{
	return classType;
}

void Card::notifyEventCardManager(EventCard eventCard) const {
	eventCardManager.notifyEventCardListeners(eventCard);
}

void Card::play() 
{
	using enum EventCard;
	if (classType == "ShuffleCard") {
		cout << "Shuffle card played: " << getName() << endl;
		notifyEventCardManager(SHUFFLE);
	}
	else if (classType == "FutureCard") {
		cout << "Future card played: " << getName() << endl;
		notifyEventCardManager(FUTURE);
	}
	else if (classType == "AttackCard") {
		cout << "Attack card played: " << getName() << endl;
		notifyEventCardManager(ATTACK);
	}
	else if (classType == "HappyCard") {
		cout << "Happy card played: " << getName() << endl;
		notifyEventCardManager(HAPPYPOINTS);
	}
}

void Card::render(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size)
{
	cardSprite.setScale(size);
	cardSprite.setPosition(position);
	window.draw(cardSprite);
}
