#include "Card.h"
#include "EventCardListener.h"

using namespace std;

Card::Card(const pugi::xml_node& node, EventCardManager& eventCardManager) :
	name(node.attribute("name").as_string()), eventCardManager(eventCardManager)
{
}

string Card::getName() const
{
	return name;
}

void Card::notifyEventCardManager(EventCard eventCard) const {
	eventCardManager.notifyEventCardListeners(eventCard);
}

