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

    //Load the music
    gMusic = Mix_LoadMUS( "mario.mp3" );
    
    //If there was a problem loading the music
    if( gMusic == NULL )
    {
        return false;    
    }

    /*
    //Load the sound effects
    //Fillers
    gScratch = Mix_LoadWAV( "scratch.wav" );
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
    /*    
    //Free the sound effects
    Mix_FreeChunk( gScratch );
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

bool SoundEffects::playMusic(){
    Mix_PlayMusic(gMusic, -1);
    
    return true;
}
