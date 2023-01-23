//
// Created by timot on 1/22/2023.
//
//Using SDL and standard IO
#include <SDL.h>
#include <string>
#include <cstdio>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gXout = NULL;


bool init()
{

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    //Create window
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    //Get window surface
    gScreenSurface = SDL_GetWindowSurface( gWindow );

    return true;
}


bool loadMedia()
{
    //Load splash image
    gXout = SDL_LoadBMP( "../03/x.bmp" );
    if( gXout == NULL ){
        printf( "Unable to load image %s! SDL Error: %s\n", "03/x.bmp", SDL_GetError() );
        return false;
    }

    return true;
}


void close()
{
    //Deallocate surface
    SDL_FreeSurface( gXout );
    gXout = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{

    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
        return 1;
    }

    //Load media
    if( !loadMedia() )
    {
        printf( "Failed to load media!\n" );
        return 1;
    }

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            printf("Event: %x\n", e.type);
        }

        //Apply the image
        SDL_BlitSurface( gXout, NULL, gScreenSurface, NULL );

        //Update the surface
        SDL_UpdateWindowSurface( gWindow );
    }

    //Free resources and close SDL
    close();

    return 0;
}
