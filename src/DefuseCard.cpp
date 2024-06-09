#include "DefuseCard.h"
#include <iostream>

using namespace std;

DefuseCard::DefuseCard(const pugi::xml_node& node, EventCardManager& eventCardManager) : Card(node, eventCardManager)
{
	if (!defuseCardTexture.loadFromFile("resources/DefuseCard-Babysous.png"))
	{
		std::cerr << "Error loading texture" << std::endl;
	}
	defuseCardSprite.setTexture(defuseCardTexture);
}

void DefuseCard::play()
{
	cout << "Defuse card played: " << getName() << endl;
}

std::string DefuseCard::getClassType() const
{
	return classType;
}

void DefuseCard::render(sf::RenderWindow& window, const sf::Vector2f& position)
{
	defuseCardSprite.setPosition(position);
	window.draw(defuseCardSprite);
}
