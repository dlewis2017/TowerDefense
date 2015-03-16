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


//Screen dimension constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 800;

const int GOB_WIDTH = 60;
const int GOB_HEIGHT = 60;

// function prototypes
bool init();				//Starts up SDL and creates window
bool loadMedia();			//Loads media
void close();				//Frees media and shuts down SDL

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
			
				//Handle event on queue
				while( SDL_PollEvent(&e) != 0 ){
					
					//Aply main image stertched
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
					if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
						//If mouse click occurs, place image where mouse was clicked ***NOT WORKING***
						SDL_Point mPosition;
 						int x,y;
 						SDL_GetMouseState(&x,&y);
						//Apply the goblin image
						SDL_Rect shrinkRect;
						shrinkRect.x = mPosition.x;
						shrinkRect.y = mPosition.y;
						shrinkRect.w = GOB_WIDTH;
						shrinkRect.h = GOB_HEIGHT;
						SDL_BlitScaled(gGoblin, NULL, gScreenSurface, &shrinkRect);
					}

					SDL_Point mPosition; //SDL point mouse position
					//Apply the goblin image to path
					SDL_Rect shrinkRect;
					shrinkRect.x = 0;
					shrinkRect.y = 400;
					shrinkRect.w = GOB_WIDTH;
					shrinkRect.h = GOB_HEIGHT;
					SDL_BlitScaled(gGoblin, NULL, gScreenSurface, &shrinkRect);

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
	gMain = SDL_LoadBMP( "img/towerDefenseBackground.bmp" );
	if( gMain == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "img/towerDefenseBackground.bmp", SDL_GetError() );
		success = false;
	}
	gGoblin = SDL_LoadBMP("img/goblin.bmp");
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
