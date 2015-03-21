/* main.cpp
* This program serves as a driver program to run the Tower Defense program
* 
* The program currently displays a tower defense background to the window
*/


//Using SDL and standard IO
#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;


//Screen dimension constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 800;

const int ENEMY_MAX_DIMENSION = 60;
const double MAX_DISTORTION = .57;		// decimal of max percentage

// function prototypes
bool init();				//Starts up SDL and creates window
bool loadMedia();			//Loads media
void close();				//Frees media and shuts down SDL
SDL_Rect getRect(SDL_Surface* surface, int maxDimension, int x, int y);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gMain = NULL;

//THe image we ill load and show on main image
SDL_Surface* gGoblin = NULL;

//Loads individual image
SDL_Surface* loadSurface(std::string path);

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;
		
			//Event handler
			SDL_Event e;
			
			//While application is running
			while (!quit){
			
				//Handle event on queue. reads in every event that’s occurred since the previous frame and handle them
				while( SDL_PollEvent(&e) != 0 ){
					
					//Aply background image stretched
					SDL_Rect stretchRect;
					stretchRect.x = 0;
					stretchRect.y = 0;
					stretchRect.w = SCREEN_WIDTH;
					stretchRect.h = SCREEN_HEIGHT;
					SDL_BlitScaled(gMain,NULL,gScreenSurface, &stretchRect);

					//User requests quit
					if(e.type == SDL_QUIT){
						quit = true;
						return 0;
					}
					if(e.type == SDL_MOUSEBUTTONDOWN){
						//If mouse click occurs, place image where mouse was clicked ***NOT WORKING***
						//SDL_Point mPosition;
 						int x,y;
 						SDL_GetMouseState(&x,&y);
						SDL_Rect container = getRect(gGoblin, ENEMY_MAX_DIMENSION, x, y);
						//Apply the goblin 
						SDL_BlitScaled(gGoblin, NULL, gScreenSurface, &container);
					}

					SDL_Point mPosition; //SDL point mouse position
					//Apply the goblin image to path
					SDL_Rect enemyOnPathContainer = getRect(gGoblin, ENEMY_MAX_DIMENSION, ENEMY_MAX_DIMENSION/2, 435);
					SDL_BlitScaled(gGoblin, NULL, gScreenSurface, &enemyOnPathContainer);

				//Update the surface
				SDL_UpdateWindowSurface( gWindow );
		
				}
			}	
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
 
/* Return an SDL_Rect with an SDL_Surface as the background
 * Method assumes a square image is most ideal, as long as it is not too distorted
 * Returns an SDL_Rect that has no more than the maximum threshold of distortion
 * x and y are the coordinates of the position of the top of the SDL_Rect
*/
SDL_Rect getRect(SDL_Surface* surface, int maxDimension, int x, int y) {
	SDL_Rect container;
	double surfaceWidth = surface->SDL_Surface::w;		// easier to reference, keep precision
	double surfaceHeight = surface->SDL_Surface::h;

	if(surfaceHeight > surfaceWidth) {					// height = maxDimesion. Distort up to MAX_DISTORTION
		double factor = surfaceHeight / maxDimension;	// scaling factor to reduce height by
		surfaceHeight = maxDimension;					// height cannot exceed max dimension
		// check if factor will cause width to exceed MAX_DISTORTION			
		if(1 - (surfaceWidth / factor / maxDimension) > MAX_DISTORTION) { 
			surfaceWidth = surfaceWidth / factor * (1 + MAX_DISTORTION); // set width MAX_DISTORTION threshold
		} else {
			surfaceWidth = maxDimension;	// safe because width won't exceed MAX_DISTORTION threshold
		}
		
	} else {											// width = maxDimension. Distort height as necessary
		double factor = surfaceWidth / maxDimension;	// scaling factor to reduce height by
		surfaceWidth = maxDimension;					// height cannot exceed max dimension
		// check if factor will cause width to exceed MAX_DISTORTION			
		if(1 - (surfaceHeight / factor / maxDimension) > MAX_DISTORTION) { 
			surfaceHeight = surfaceHeight / factor * (1 + MAX_DISTORTION); // set width MAX_DISTORTION threshold
		} else {
			surfaceHeight = maxDimension;	// safe because width won't exceed MAX_DISTORTION threshold
		}
	}
	container.x = (int)(x - (.5 * surfaceWidth));
	container.y = (int)(y - (.5 * surfaceHeight));			
	container.w = (int)surfaceWidth;
	container.h = (int)surfaceHeight;

	return container;
}

/* Initialize SDL and the window. Returns false if the initialization is unsuccessful
*/
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Tower Defense", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );

		}
	}

	return success;
}

/* load the background */
bool loadMedia() {
	//Loading success flag
	bool success = true;

	//Load splash image
	gMain = loadSurface( "img/towerDefenseBackground.bmp" );
	if( gMain == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "img/towerDefenseBackground.bmp", SDL_GetError() );
		success = false;
	}
	gGoblin = loadSurface("img/goblin.bmp");
	if( gGoblin == NULL)
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "img/goblin.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

/* deallocate memory */
void close() {
	//Deallocate surface
	SDL_FreeSurface( gMain );
	gMain = NULL;

	//Deallocate surface
	SDL_FreeSurface(gGoblin);
	gGoblin = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

// returns an optimized surface which will load and render faster
SDL_Surface* loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;
	
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str());
	if(loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}else{
		//convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL);
		if(optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n",path.c_str(), SDL_GetError());
		}
	}

	return optimizedSurface;
}
