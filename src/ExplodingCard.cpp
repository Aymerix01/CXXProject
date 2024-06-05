#include "ExplodingCard.h"
#include <iostream>

using namespace std;

ExplodingCard::ExplodingCard(const pugi::xml_node& node, EventCardManager& eventCardManager) : Card(node, eventCardManager)
{
	cout << "Exploding card created: " << node.attribute("name").as_string() << endl;
}

void ExplodingCard::play()
{
	cout << "Exploding card played: " << getName() << endl;
}

std::string ExplodingCard::getClassType() const
{
	return classType;
}

void ExplodingCard::render(sf::RenderWindow& window, const sf::Vector2f& position) const {
	//TODO: Implement render
}
