#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include "SFML/Graphics.hpp"
#include "RoundTarget.hpp"

class Game : private sf::NonCopyable
{
	public:
								Game();
		void					run();
		

	private:
		void					processEvents();
		void					update(sf::Time elapsedTime);
		void					render();

		void					updateStatistics(sf::Time elapsedTime);	


		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow{sf::VideoMode{640, 480}, "SFML Application", sf::Style::Close};
		sf::Texture				mTexture;
        RoundTarget 			mTarget{50.f, sf::Color::Cyan, 100.f, 100.f};
		sf::Font				mFont;
		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;

		std::size_t				mStatisticsNumFrames{0};
};

#endif // BOOK_GAME_HPP
