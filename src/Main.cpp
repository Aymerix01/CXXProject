#include "Game.hpp"
#include <iostream>
#include <pugixml.hpp>
#include <string>
#include "SFML/Graphics.hpp"

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

    sf::Texture texturePlateau;
    if (!texturePlateau.loadFromFile("resources/TemplatePlateau.png")) {
        printf("Error loading texture\n");
        return -1;
    }
    sf::Sprite spritePlateau;
    spritePlateau.setTexture(texturePlateau);

    sf::Texture textureDosCarte;
    if (!textureDosCarte.loadFromFile("resources/DosCarte.png")) {
        printf("Error loading texture\n");
        return -1;
    }
    sf::Sprite spriteDosCarte;
    spriteDosCarte.setTexture(textureDosCarte);

    EventCardManager eventCardManager;

	Game game(string("Toto"), root, spritePlateau, spriteDosCarte, eventCardManager);
    game.run();
	return 0;
}
