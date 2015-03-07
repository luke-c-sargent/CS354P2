#include "SoundEffects.h"

SoundEffects::SoundEffects(){}

bool SoundEffects::init() {


    //Some code borrowed from lazyfoo.net SDL tutorials

    //Initialize SDL subsystems (only audio subsystem necessary?)

    //if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    if ( SDL_Init ( SDL_INIT_AUDIO ) == -1)
    {
        return false;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }

    //If everything initialized fine
    return true;

}

bool SoundEffects::load_files() {

    enable_Sound = true;
    //Load the music
    gMusic = Mix_LoadMUS( "music.mp3" );

    //If there was a problem loading the music
    if( gMusic == NULL )
    {
        return false;
    }


    //Load the sound effects
    //Fillers
    gSwing = Mix_LoadWAV( "swing.wav" );
    /*
    gHigh = Mix_LoadWAV( "high.wav" );
    gMed = Mix_LoadWAV( "medium.wav" );
    gLow = Mix_LoadWAV( "low.wav" );

    //If there was a problem loading the sound effects
    if( ( gScratch == NULL ) || ( gHigh == NULL ) || ( gMed == NULL ) || ( gLow == NULL ) )
    {
        return false;
    }
    */

    //If everything loaded fine
    return true;
}

void SoundEffects::clean_up() {

    //Free the sound effects
    Mix_FreeChunk( gSwing );
    /*
    Mix_FreeChunk( gHigh );
    Mix_FreeChunk( gMed );
    Mix_FreeChunk( gLow );
    */
    //Free the music
    Mix_FreeMusic( gMusic );

    //Quit SDL_mixer
    Mix_CloseAudio();

    //Quit SDL
    SDL_Quit();
}

void SoundEffects::playMusic(){
    Mix_PlayMusic(gMusic, -1);
}

void SoundEffects::playEffect(int s){
    if(enable_Sound)
    {
        switch(s) {
        case 1:
            Mix_PlayChannel( -1, gSwing, 0 );
        }
    }


}

void SoundEffects::pauseMusic(){

    //If the music is paused
    if( Mix_PausedMusic() == 1 )
    {
        //Resume the music
        if(enable_Sound)
        {
            Mix_ResumeMusic();
        }

    }
    else
    {
        //Pause the music
        Mix_PauseMusic();
    }
}

void SoundEffects::enableSound()
{
    if(enable_Sound)
    {
        enable_Sound = false;
        Mix_PauseMusic();
    }
    else
    {
        enable_Sound = true;
    }
}
