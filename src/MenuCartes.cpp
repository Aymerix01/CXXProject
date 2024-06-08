#include "MenuCartes.h"
#include "MenuPrincipal.h"
#include "InGame.h"
#include "MenuPause.h"
#include "MenuStateManager.h"

MenuCartes::MenuCartes(MenuStateManager& m_manager) : MenuState(m_manager)
{
}

void MenuCartes::render(sf::RenderWindow& window)
{
	window.draw(m_manager.menuCartesSprite);
	window.draw(m_manager.menuCartesText);
}

void MenuCartes::onUserEvent(sf::Event event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape && m_manager.paused)
		{
			m_manager.paused = false;
			m_manager.changeState(std::make_unique<InGame>(m_manager));
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed) 
	{
		if (!m_manager.paused && event.mouseButton.x >= 836 && event.mouseButton.x <= 1118 &&
			event.mouseButton.y >= 825 && event.mouseButton.y <= 1014)
		{
			m_manager.changeState(std::make_unique<MenuPrincipal>(m_manager));
		}
		else if (m_manager.paused && event.mouseButton.x >= 836 && event.mouseButton.x <= 1118 &&
			event.mouseButton.y >= 825 && event.mouseButton.y <= 1014)
		{
			m_manager.changeState(std::make_unique<MenuPause>(m_manager));
		}
		else if (event.mouseButton.x >= 188 && event.mouseButton.x <= 375 &&
			event.mouseButton.y >= 107 && event.mouseButton.y <= 389)
		{
			m_manager.menuCartesText.setString("Cette carte vous permet d'éviter les sanglots du bébé");
		}
		else if (event.mouseButton.x >= 465 && event.mouseButton.x <= 652 &&
			event.mouseButton.y >= 107 && event.mouseButton.y <= 389)
		{
			m_manager.menuCartesText.setString("Cette carte vous permet de mélanger les cartes du Deck");
		}
		else if (event.mouseButton.x >= 734 && event.mouseButton.x <= 923 &&
			event.mouseButton.y >= 107 && event.mouseButton.y <= 389)
		{
			m_manager.menuCartesText.setString("Cette carte vous permet de faire exploser de rire le bébé");
		}
		else if (event.mouseButton.x >= 1013 && event.mouseButton.x <= 1197 &&
			event.mouseButton.y >= 107 && event.mouseButton.y <= 389)
		{
			m_manager.menuCartesText.setString("Cette carte vous permet de voir les 3 premières cartes du Deck");
		}
		else if (event.mouseButton.x >= 1277 && event.mouseButton.x <= 1463 &&
			event.mouseButton.y >= 107 && event.mouseButton.y <= 389)
		{
			m_manager.menuCartesText.setString("Cette carte vous permet de renvoyer la première carte du Deck");
		}
		else if (event.mouseButton.x >= 1573 && event.mouseButton.x <= 1788 &&
			event.mouseButton.y >= 107 && event.mouseButton.y <= 389)
		{
			m_manager.menuCartesText.setString("Cette carte fait exploser le bébé en sanglots. Evitez la !");
		}
	}
}
