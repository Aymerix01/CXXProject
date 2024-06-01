#include "Card.h"

using namespace std;

Card::Card(const pugi::xml_node& node) :
	name(node.attribute("name").as_string())
{
}

