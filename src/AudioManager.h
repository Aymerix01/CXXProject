#pragma once
#include <SFML/Audio.hpp>


class AudioManager {
private:
	std::vector<std::unique_ptr<sf::Music>> osts;
	std::vector<std::unique_ptr<sf::SoundBuffer>> sfxBuffers;
	std::vector<sf::Sound> sfx;
	int songPlaying = 0;
	
	//SFX1 is CardPlayed ok
	//SFX2 is CardShuffle ok
	//SFX3 is BabyLaugh (attack) ok
	//SFX4 is Defuse ok
	//SFX5 is Explosion ok
	//SFX6 is Future ok
	//SFX7 is Happy

public:
	explicit AudioManager();
	void playMusic();
	void playSFX(int i);
	bool hasSongEnded();
	int getSongToPlay() const { return songPlaying; };
	void incrementSongToPlay(); 
};