#include "AttackCard.h"
#include <iostream>

using namespace std;

AttackCard::AttackCard(const pugi::xml_node& node, EventCardManager& eventCardManager) : Card(node, eventCardManager)
{
	cout << "Attack card created: " << node.attribute("name").as_string() << endl;
}

void AttackCard::play()
{
	cout << "Attack card played: " << getName() << endl;
}

std::string AttackCard::getClassType() const
{
	return classType;
}

void AttackCard::render(sf::RenderWindow& window, const sf::Vector2f& position) const
{
	//TODO Render
}
