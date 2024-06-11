#include "ExplodingCard.h"
#include <iostream>

using namespace std;

ExplodingCard::ExplodingCard(const pugi::xml_node& node, EventCardManager& eventCardManager) : Card(node, eventCardManager)
{
	if (!explodingCardTexture.loadFromFile("resources/ExplodingCard-BabyBoom.png"))
	{
		std::cerr << "Error loading texture" << std::endl;
	}
	explodingCardSprite.setTexture(explodingCardTexture);
}

void ExplodingCard::play()
{
	cout << "Exploding card played: " << getName() << endl;
}

std::string ExplodingCard::getClassType() const
{
	return classType;
}

void ExplodingCard::render(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size)
{
	explodingCardSprite.setScale(size);
	explodingCardSprite.setPosition(position);
	window.draw(explodingCardSprite);
}
