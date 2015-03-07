#pragma once

//Using SDL, SDL_image, SDL_mixer, standard IO, and strings
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

class BaseApplication;

class SoundEffects{



public:
    //Set these all to NULL initially

    bool enable_Sound;
    //The music that will be played
    Mix_Music *gMusic;

    //The sound effects that will be used
    Mix_Chunk *gSwing;
    Mix_Chunk *gHigh;
    Mix_Chunk *gMedium;
    Mix_Chunk *gLow;

    SoundEffects();
    bool init();
    bool load_files();
    void clean_up();
    void playMusic();
    void pauseMusic();
    void playEffect(int);
    void enableSound();
};
