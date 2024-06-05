#include "DefuseCard.h"
#include <iostream>

using namespace std;

DefuseCard::DefuseCard(const pugi::xml_node& node) : Card(node)
{
	cout << "Defuse card created: " << node.attribute("name").as_string() << endl;
}

int DefuseCard::play(Deck& deck)
{
	return 0;
}

std::string DefuseCard::getClassType() const
{
	return classType;
}

void DefuseCard::render(sf::RenderWindow& window, const sf::Vector2f& position) const
{
	//TODO Render
}
