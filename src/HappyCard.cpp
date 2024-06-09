#include "HappyCard.h"
#include <iostream>

using namespace std;

HappyCard::HappyCard(const pugi::xml_node& node, EventCardManager& eventCardManager) : 
	Card(node, eventCardManager)
{
	if (!happyCardTexture.loadFromFile("resources/HappyCard-BabyShark.png"))
	{
		std::cerr << "Error loading texture" << std::endl;
	}
	happyCardSprite.setTexture(happyCardTexture);
}

void HappyCard::play()
{
	cout << "Happy card played: " << getName() << endl;
	notifyEventCardManager(EventCard::HAPPYPOINTS);
}

std::string HappyCard::getClassType() const
{
	return classType;
}

void HappyCard::render(sf::RenderWindow& window, const sf::Vector2f& position)
{
	happyCardSprite.setPosition(position);
	window.draw(happyCardSprite);
}

