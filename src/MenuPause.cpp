#include "MenuPause.h"
#include "InGame.h"
#include "MenuPrincipal.h"
#include "MenuCartes.h"
#include "MenuStateManager.h"

MenuPause::MenuPause(MenuStateManager& m_manager) : MenuState(m_manager)
{
}

void MenuPause::render(sf::RenderWindow& window)
{
	window.draw(m_manager.menuPauseSprite);
}

void MenuPause::onUserEvent(sf::Event event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			m_manager.paused = false;
			m_manager.changeState(std::make_unique<InGame>(m_manager));
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.x >= 772 && event.mouseButton.x <= 1123 &&
			event.mouseButton.y >= 356 && event.mouseButton.y <= 593)
		{
			m_manager.paused = false;
			m_manager.changeState(std::make_unique<InGame>(m_manager));
		}
		else if (event.mouseButton.x >= 774 && event.mouseButton.x <= 1122 &&
			event.mouseButton.y >= 750 && event.mouseButton.y <= 987)
		{
			m_manager.paused = false;
			m_manager.changeState(std::make_unique<MenuPrincipal>(m_manager));
		}
		else if (event.mouseButton.x >= 132 && event.mouseButton.x <= 316 &&
			event.mouseButton.y >= 448 && event.mouseButton.y <= 725)
		{
			m_manager.changeState(std::make_unique<MenuCartes>(m_manager));
		}
	}
}