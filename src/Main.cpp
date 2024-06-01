#include "Game.hpp"
#include <iostream>
#include <pugixml.hpp>
#include <string>

using namespace std;

int myMain()
{
    pugi::xml_document doc;
    if (auto result = doc.load_file("resources/Data.xml"); !result)
    {
        cerr << "Could not open file Data.xml because " << result.description() << endl;
        return 1;
    }

    pugi::xml_node root = doc.child("root");

	Game game(string("Toto"), root);
    game.run();
	return 0;
}
