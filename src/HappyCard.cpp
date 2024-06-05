#include "HappyCard.h"
#include <iostream>

using namespace std;

HappyCard::HappyCard(const pugi::xml_node& node) : Card(node)
{
	cout << "Happy card created: " << node.attribute("name").as_string() << endl;
}

int HappyCard::play(Deck& deck)
{
	return 100;
}

std::string HappyCard::getClassType() const
{
	return classType;
}

void HappyCard::render(sf::RenderWindow& window, const sf::Vector2f& position) const
{
	//TODO Render
}
