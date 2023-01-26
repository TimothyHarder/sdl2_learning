//
// Created by timot on 1/23/2023.
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

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed image
SDL_Surface* gStretchedSurface = NULL;

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

SDL_Surface* loadSurface( std::string path )
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

bool loadMedia()
{
    //Load splash image
    gStretchedSurface = loadSurface( "../05/stretch.bmp" );
    if( gStretchedSurface == NULL ){
        printf( "Unable to load image %s! SDL Error: %s\n", "05/stretch.bmp", SDL_GetError() );
        return false;
    }

    return true;
}

void close()
{
    //Free loaded image
    SDL_FreeSurface( gStretchedSurface );
    gStretchedSurface = NULL;

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

        }

        //Apply the image stretched
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        SDL_BlitScaled( gStretchedSurface, NULL, gScreenSurface, &stretchRect );

        //Update the surface
        SDL_UpdateWindowSurface( gWindow );
    }

    //Free resources and close SDL
    close();

    return 0;
}
