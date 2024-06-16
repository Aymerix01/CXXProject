#pragma once
#include <SFML/Audio.hpp>


class AudioManager {
private:
	std::vector<std::unique_ptr<sf::Music>> osts;
	std::vector<std::unique_ptr<sf::SoundBuffer>> sfxBuffers;
	std::vector<sf::Sound> sfx;
	int songPlaying = 0; //Current song that is playing

public:
	/*
	* Constructor that builds osts, sfxBuffers and sfx
	*/
	explicit AudioManager();

	/*
	* Plays the current song defined by songPlaying
	*/
	void playMusic(); 
	
	/*
	* Plays the correspoding sfx : SFX(i+1)
	*	SFX1 is CardPlayed ok
	*	SFX2 is CardShuffle ok
	*	SFX3 is BabyLaugh (attack) ok
	*	SFX4 is Defuse ok
	*	SFX5 is Explosion ok
	*	SFX6 is Future ok
	*	SFX7 is Happy
	*/
	void playSFX(int i);
	
	/*
	* Returns wheter or not the current song has ended
	*/
	bool hasSongEnded();

	/*
	* Passes to the next song
	*/
	void incrementSongToPlay(); 
};