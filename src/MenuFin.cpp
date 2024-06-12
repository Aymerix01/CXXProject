
#include "MenuFin.h"
#include "MenuStateManager.h"
#include "MenuPrincipal.h"

MenuFin::MenuFin(MenuStateManager& m_manager) : MenuState(m_manager)
{
}

void MenuFin::render(sf::RenderWindow& window)
{
	window.draw(m_manager.menuFinSprite);
}

void MenuFin::onUserEvent(sf::Event event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonPressed && 
		event.mouseButton.x >= 825 && event.mouseButton.x <= 1100 &&
		event.mouseButton.y >= 776 && event.mouseButton.y <= 958)
	{
		
		std::cout << "Retour au menu principal" << std::endl;
		m_manager.endGame = false;
		m_manager.changeState(std::make_unique<MenuPrincipal>(m_manager));
		
	}
}