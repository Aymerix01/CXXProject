#include "InGame.h"
#include "MenuPause.h"
#include <iostream>
#include "MenuStateManager.h"

InGame::InGame(MenuStateManager& m_manager) : MenuState(m_manager)
{
}

void InGame::render(sf::RenderWindow& window)
{
	window.draw(m_manager.backgroundSprite);
}

void InGame::onUserEvent(sf::Event event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		m_manager.paused = true;
		m_manager.inGame = false;
		m_manager.changeState(std::make_unique<MenuPause>(m_manager));
	}
}