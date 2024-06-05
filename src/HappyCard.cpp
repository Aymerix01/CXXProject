#include "HappyCard.h"
#include <iostream>

using namespace std;

HappyCard::HappyCard(const pugi::xml_node& node, EventCardManager& eventCardManager) : Card(node, eventCardManager)
{
	cout << "Happy card created: " << node.attribute("name").as_string() << endl;
}

void HappyCard::play()
{
	cout << "Happy card played: " << getName() << endl;
}

std::string HappyCard::getClassType() const
{
	return classType;
}

void HappyCard::render(sf::RenderWindow& window, const sf::Vector2f& position) const
{
	//TODO Render
}

