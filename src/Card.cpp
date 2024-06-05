#include "Card.h"

using namespace std;

Card::Card(const pugi::xml_node& node, EventCardManager& eventCardManager) :
	name(node.attribute("name").as_string()), eventCardManager(eventCardManager)
{
}

string Card::getName() const
{
	return name;
}

void Card::play()
{
	eventCardManager.notifyEventCardListeners();
}

