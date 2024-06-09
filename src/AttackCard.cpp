#include "AttackCard.h"
#include <iostream>

using namespace std;

AttackCard::AttackCard(const pugi::xml_node& node, EventCardManager& eventCardManager) : Card(node, eventCardManager)
{
	if (!attackCardTexture.loadFromFile("resources/AttackCard-BabygBrother.png"))
	{
		std::cerr << "Error loading texture" << std::endl;
	}
	attackCardSprite.setTexture(attackCardTexture);
}

void AttackCard::play()
{
	cout << "Attack card played: " << getName() << endl;
	notifyEventCardManager(EventCard::ATTACK);
}

std::string AttackCard::getClassType() const
{
	return classType;
}

void AttackCard::render(sf::RenderWindow& window, const sf::Vector2f& position)
{
	attackCardSprite.setPosition(position);
	window.draw(attackCardSprite);
}
