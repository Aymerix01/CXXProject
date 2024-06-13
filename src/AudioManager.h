#pragma once
#include <SFML/Audio.hpp>


class AudioManager {
private:
	std::vector<std::unique_ptr<sf::Music>> osts;
	std::vector<std::unique_ptr<sf::SoundBuffer>> sfxBuffers;
	std::vector<sf::Sound> sfx;
	
	//SFX1 is CardPlayed
	//SFX2 is CardShuffle
	//SFX3 is BabyLaugh

public:
	explicit AudioManager();
	void playMusic(int i);
	void playSFX(int i);
};