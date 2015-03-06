#pragma once

//Using SDL, SDL_image, SDL_mixer, standard IO, and strings
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>


/*	http://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php	*/
class BaseApplication;

class SoundEffects{



public:
	//Set these all to NULL initially
	
	//The music that will be played
	Mix_Music *gMusic;

	//The sound effects that will be used
	Mix_Chunk *gScratch;
	Mix_Chunk *gHigh;
	Mix_Chunk *gMedium;
	Mix_Chunk *gLow;

	SoundEffects();
	bool init();
	bool load_files();
	void clean_up();
	bool playMusic();
};
