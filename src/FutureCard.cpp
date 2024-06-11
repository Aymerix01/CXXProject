#include "FutureCard.h"
#include <iostream>

using namespace std;

FutureCard::FutureCard(const pugi::xml_node& node, EventCardManager& eventCardManager) : Card(node, eventCardManager)
{
	if (!futureCardTexture.loadFromFile("resources/FutureCard-Babytcoin.png"))
	{
		std::cerr << "Error loading texture" << std::endl;
	}
	futureCardSprite.setTexture(futureCardTexture);
}

void FutureCard::play()
{
	cout << "Future card played: " << getName() << endl;
	notifyEventCardManager(EventCard::FUTURE);
}

std::string FutureCard::getClassType() const
{
	return classType;
}

void FutureCard::render(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size)
{
	futureCardSprite.setScale(size);
	futureCardSprite.setPosition(position);
	window.draw(futureCardSprite);
}

