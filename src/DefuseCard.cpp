#include "DefuseCard.h"
#include <iostream>

using namespace std;

DefuseCard::DefuseCard(const pugi::xml_node& node, EventCardManager& eventCardManager) : Card(node, eventCardManager)
{
	//cout << "Defuse card created: " << node.attribute("name").as_string() << endl;
}

void DefuseCard::play()
{
	cout << "Defuse card played: " << getName() << endl;
}

std::string DefuseCard::getClassType() const
{
	return classType;
}

void DefuseCard::render(sf::RenderWindow& window, const sf::Vector2f& position) const
{
	//TODO Render
}
