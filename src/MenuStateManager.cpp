#include "MenuStateManager.h"
#include "MenuPrincipal.h"

MenuStateManager::MenuStateManager(const sf::Sprite& backgroundSprite, const sf::Sprite& menuPrincipalSprite,
								   const sf::Sprite& menuCartesSprite, const sf::Sprite& menuPauseSprite, 
								   const sf::Sprite& menuFinSprite) :
	backgroundSprite(backgroundSprite), menuPrincipalSprite(menuPrincipalSprite),
	menuCartesSprite(menuCartesSprite), menuPauseSprite(menuPauseSprite), menuFinSprite(menuFinSprite)
{
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
