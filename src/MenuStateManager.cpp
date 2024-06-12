#include "MenuStateManager.h"
#include "MenuPrincipal.h"

MenuStateManager::MenuStateManager()
{
    if (!texturePlateau.loadFromFile("resources/TemplatePlateau.png")) {
        printf("Error loading texture\n");
    }
    backgroundSprite.setTexture(texturePlateau);

    if (!textureMenuPrincipal.loadFromFile("resources/FondMenuPrincipal.png")) {
        printf("Error loading texture\n");
    }
    menuPrincipalSprite.setTexture(textureMenuPrincipal);

    if (!textureMenuCartes.loadFromFile("resources/MenuCartes.png")) {
        printf("Error loading texture\n");
    }
    menuCartesSprite.setTexture(textureMenuCartes);

    if (!textureMenuPause.loadFromFile("resources/MenuPause.png")) {
        printf("Error loading texture\n");
    }
    menuPauseSprite.setTexture(textureMenuPause);

    if (!textureMenuFin.loadFromFile("resources/MenuEndGame.png")) {
        printf("Error loading texture\n");
    }
    menuFinSprite.setTexture(textureMenuFin);

	mFont.loadFromFile("media/Sansation.ttf");
	menuCartesText.setFont(mFont);
	menuCartesText.setPosition(370.f, 493.f);
	menuCartesText.setCharacterSize(50);
	menuCartesText.setString("Cliquez sur une carte pour voir sa description");

	auto newState = std::make_unique<MenuPrincipal>(*this);
	menuState = std::move(newState);
}

void MenuStateManager::render(sf::RenderWindow& window)
{
	menuState->render(window);
}

void MenuStateManager::onUserEvent(sf::Event event, sf::RenderWindow& window)
{
	menuState->onUserEvent(event, window);
}

void MenuStateManager::changeState(std::unique_ptr<MenuState> state)
{
	menuState = std::move(state);
}
