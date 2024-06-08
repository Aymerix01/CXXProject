#include "MenuPrincipal.h"
#include "MenuCartes.h"
#include "InGame.h"
#include <iostream>
#include "MenuStateManager.h"

MenuPrincipal::MenuPrincipal(MenuStateManager& m_manager) :
	MenuState(m_manager)
{
}

void MenuPrincipal::render(sf::RenderWindow& window)
{
	window.draw(m_manager.menuPrincipalSprite);
}

void MenuPrincipal::onUserEvent(sf::Event event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.x >= 780 && event.mouseButton.x <= 1136 &&
			event.mouseButton.y >= 365 && event.mouseButton.y <= 605)
		{
			m_manager.changeState(std::make_unique<InGame>(m_manager));
		}
		else if (event.mouseButton.x >= 785 && event.mouseButton.x <= 1141 &&
			event.mouseButton.y >= 709 && event.mouseButton.y <= 948)
		{
			window.close();
		}
		else if (event.mouseButton.x >= 194 && event.mouseButton.x <= 382 &&
			event.mouseButton.y >= 475 && event.mouseButton.y <= 756)
		{
			m_manager.menuCartesText.setString("Cliquez sur une carte pour voir sa description");
			m_manager.changeState(std::make_unique<MenuCartes>(m_manager));
		}
	}
}