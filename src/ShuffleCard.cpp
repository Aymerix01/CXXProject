#include "ShuffleCard.h"
#include <iostream>

using namespace std;

ShuffleCard::ShuffleCard(const pugi::xml_node& node, EventCardManager& eventCardManager) : 
	Card(node, eventCardManager)
{
	if (!shuffleCardTexture.loadFromFile("resources/ShuffleCard-Babycyclette.png"))
	{
		std::cerr << "Error loading texture" << std::endl;
	}
	shuffleCardSprite.setTexture(shuffleCardTexture);
}

void ShuffleCard::play()
{
	cout << "Shuffle card played: " << getName() << endl;
	notifyEventCardManager(EventCard::SHUFFLE);
}

std::string ShuffleCard::getClassType() const
{
	return classType;
}

void ShuffleCard::render(sf::RenderWindow& window, const sf::Vector2f& position)
{
	shuffleCardSprite.setPosition(position);
	window.draw(shuffleCardSprite);
}

