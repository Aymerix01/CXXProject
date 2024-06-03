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

    sf::Texture texture;
    if (!texture.loadFromFile("resources/TemplatePlateau.png")) {
        printf("Error loading texture\n");
        return -1;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);

	Game game(string("Toto"), root, sprite);
    game.run();
	return 0;
}
