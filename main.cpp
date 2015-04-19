//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <vector>
#include <sys/time.h>
#include <ctime>
#include <stdlib.h>	// srand
#include "Towers/Tower.h"
#include "Towers/TowerSpace.h"
//#include "Towers/ArcherTower.h"
//#include "Towers/FreezeTower.h"
//#include "Towers/CannonTower.h"
#include "Towers/TowerSelector.h"
#include "Towers/WizardTower.h"
#include "Enemies/Enemy.h"
#include "Enemies/Goblin.h"
#include "Enemies/Troll.h"
#include "MapDirections.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 800;

const int TOWER_MAX_DIMENSION = 70;
const int ENEMY_MAX_DIMENSION = 60;
const double MAX_DISTORTION = .57;		// decimal of max percentage
const int ENEMY_TIME_DELAY = 6500;		// delay between enemies traversing the path, milliseconds

// methods
bool init();		//Starts up SDL and creates window
bool loadMedia();	//Loads media
void close();		//Frees media and shuts down SDL
SDL_Rect getRect(SDL_Texture* texture, int maxDimension, int x, int y);
void moveEnemies();	// moves all enemies in the enemies vector
void renderEnemies(); 	// render all enemies in the enemies vector
void addEnemies(MapDirections mapDirections);		// add enemies until max # reached

// global varsF
SDL_Texture* loadTexture( std::string path );	//Loads individual image as texture
SDL_Window* gWindow = NULL;			//The window we'll be rendering to
SDL_Renderer* gRenderer = NULL;		//The window renderer
SDL_Texture* gBackground = NULL;		//Current displayed texture
SDL_Texture* gGoblin = NULL;
SDL_Texture* gTroll = NULL;
SDL_Texture* gWizard = NULL;
SDL_Texture* gWizardTower = NULL;
SDL_Texture* gArcherTower = NULL;
SDL_Texture* gCannonTower = NULL;
SDL_Texture* gFreezeTower = NULL;
SDL_Texture* gTower = NULL;
vector<Enemy> enemies;				// stores all enemies

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
		return 2;
	}
	
	bool quit = false;	// Main loop flag
	SDL_Event e;		// Event handler
	srand(time(NULL));	// seed random generator

    // add directions for the specific map (must be hard-coded for each map)
	MapDirections mapDirections;	// stores turning instructions for the map's path
    mapDirections.setNext("right", .1411*SCREEN_WIDTH);
    mapDirections.setNext("up", .2125*SCREEN_HEIGHT);
    mapDirections.setNext("right", .3444*SCREEN_WIDTH);
    mapDirections.setNext("down", .6113*SCREEN_HEIGHT);
    mapDirections.setNext("right", .6078*SCREEN_WIDTH);
    mapDirections.setNext("up", .4125*SCREEN_HEIGHT);
    mapDirections.setNext("right", SCREEN_WIDTH);

    int nEnemies = 3;
    bool allEnemiesAdded = false;

    // add first enemy immediately
    struct timeval tp;			// allows for milliseconds of current time
    gettimeofday(&tp, NULL);
    long int clockTime;			// used to track current time
	long int lastAddTime = tp.tv_sec * 1000 + tp.tv_usec / 1000; //get current timestamp in milliseconds
    addEnemies(mapDirections);

    TowerSelector towerSelector(&gRenderer, 100, 100);

	//While application is running
	while( !quit )
	{
		int x,y;	// x and y locations of mouseclick 
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			//If mouse click occurs, place image where mouse was clicked
			if(e.type == SDL_MOUSEBUTTONDOWN){
				SDL_GetMouseState(&x,&y);


				// pass x and y mouse click coordinates to TowerSelector objects
				towerSelector.handleMouseClick(x, y);


			}
		}


		// create containers for each image which specifies its size and location
		//SDL_Rect gTowerRect1 = getRect(gTower, TOWER_MAX_DIMENSION,80,360);
		//SDL_Rect gTowerRect2 = getRect(gTower, TOWER_MAX_DIMENSION,220,275);
		//SDL_Rect gTowerRect3 = getRect(gTower, TOWER_MAX_DIMENSION,400,440);
		//SDL_Rect gTowerRect4 = getRect(gTower, TOWER_MAX_DIMENSION,500,600);
		//SDL_Rect gTowerRect5 = getRect(gTower, TOWER_MAX_DIMENSION,750,435);
		
		// set timing to correctly space enemies
		if(!allEnemiesAdded) {
			gettimeofday(&tp, NULL);
			clockTime = tp.tv_sec * 1000 + tp.tv_usec / 1000; //get current timestamp in milliseconds
		}

		// check if it is time for another enemy to be added
		if(!allEnemiesAdded && enemies.size() < nEnemies && (clockTime - lastAddTime) >= ENEMY_TIME_DELAY) {
    		addEnemies(mapDirections);
    		lastAddTime = clockTime;
    		if(enemies.size() == nEnemies) allEnemiesAdded = true;
    	}
		moveEnemies();	// moves all enemies in enemies vector (updates position)

		//Clear screen
		SDL_RenderClear( gRenderer );

		//Render texture to screen
		SDL_RenderCopy( gRenderer, gBackground, NULL, NULL );	// MUST BE FIRST: render background, automatically fills the window
		
		bool T1 = true, T2 = true, T3 = true, T4 = true, T5 = true;
		SDL_Event tower_choice;

		if (T1) {
		TowerSpace tower1(80,360,gTower,gRenderer);
		SDL_Event tower_choice;
			if (tower1.dispDropDown(x,y,gWizardTower,gArcherTower,gCannonTower,gFreezeTower,gRenderer)){
				while( SDL_PollEvent( &tower_choice) != 0){
					if(tower_choice.type == SDL_KEYDOWN){
						T1 = tower1.handleKeyPress(tower_choice);
					}
					else break;
				}
			}
		}

		if(T2){
			TowerSpace tower2(220,275,gTower,gRenderer);
			if(tower2.dispDropDown(x,y,gWizardTower,gArcherTower,gCannonTower,gFreezeTower,gRenderer)){
				while( SDL_PollEvent( &tower_choice) != 0){
					if(tower_choice.type == SDL_KEYDOWN){
						T2 = tower2.handleKeyPress(tower_choice);
					}
					else break;
				}
			}
		}	
		if(T3){
			TowerSpace tower3(400,440,gTower,gRenderer);
			if(tower3.dispDropDown(x,y,gWizardTower,gArcherTower,gCannonTower,gFreezeTower,gRenderer)){
				while( SDL_PollEvent( &tower_choice) != 0){
					if(tower_choice.type == SDL_KEYDOWN){
						T3 = tower3.handleKeyPress(tower_choice);
					}
					else break;
				}
			}
		}
		if(T4){
			TowerSpace tower4(570,285,gTower,gRenderer);
			if(tower4.dispDropDown(x,y,gWizardTower,gArcherTower,gCannonTower,gFreezeTower,gRenderer)){
				while( SDL_PollEvent( &tower_choice) != 0){
					if(tower_choice.type == SDL_KEYDOWN){
						T4 = tower4.handleKeyPress(tower_choice);
					}
					else break;
				}
			}
		}
		if(T5){
			TowerSpace tower5(750,435,gTower,gRenderer);
			if(tower5.dispDropDown(x,y,gWizardTower,gArcherTower,gCannonTower,gFreezeTower,gRenderer)){
				while( SDL_PollEvent( &tower_choice) != 0){
					if(tower_choice.type == SDL_KEYDOWN){
						T5 = tower5.handleKeyPress(tower_choice);
					}
					else break;
				}
			}
		}	
		

		/*If w is pressed destroy Tower Space and replace it with a new wizard tower object*/

		/*SDL_Event tower_choice;		// Event handler
		//Handle events on queue
                while( SDL_PollEvent( &tower_choice ) != 0 )
                {
                    //User requests quit
                    if( tower_choice.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    //User presses a key
                    else if( tower_choice.type == SDL_KEYDOWN )
                    {
                        //Select surfaces based on key press
                        switch( tower_choice.key.keysym.sym )
                        {
                            case SDLK_w:
                            	WizardTower tower1
                            	break;

                            case SDLK_A:
                            	gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                            	break;

                            case SDLK_C:
                            	gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                            	break;

                            case SDLK_F:
                            	gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                            	break;

                            default:
                            	break;
                        }
                    }
                }


			}
		}*/

		//SDL_RenderCopy( gRenderer, gTower, NULL, &gTowerRect2);
		//SDL_RenderCopy( gRenderer, gTower, NULL, &gTowerRect3);
		//SDL_RenderCopy( gRenderer, gTower, NULL, &gTowerRect4);
		//SDL_RenderCopy( gRenderer, gTower, NULL, &gTowerRect5);

/*
		int trigger1; //used to determine which tower was clicked on first tower symbol
		//if tower1 symbol is clicked, then open up tower options menu (x and y based on top left corner of image (hence x-35,y-35 [35 = 1/2 of TOWER_MAX_DIMENSION])
		if( (x >= 80-35 && x <= 80-35+TOWER_MAX_DIMENSION) && (y >= 360-35 && y <= 360-35+TOWER_MAX_DIMENSION) ){
			//create containers for each image which specifies its size and location
			SDL_Rect gWizardTowerRect = getRect(gWizardTower, TOWER_MAX_DIMENSION,80,360+TOWER_MAX_DIMENSION );
			SDL_Rect gArcherTowerRect = getRect(gArcherTower, TOWER_MAX_DIMENSION,80,360+2*TOWER_MAX_DIMENSION );
			SDL_Rect gCannonTowerRect = getRect(gCannonTower, TOWER_MAX_DIMENSION,80,360+3*TOWER_MAX_DIMENSION );
			SDL_Rect gFreezeTowerRect = getRect(gFreezeTower, TOWER_MAX_DIMENSION,80,360+4*TOWER_MAX_DIMENSION );

			//open texutre on screen without rendering
			SDL_RenderCopy( gRenderer, gWizardTower, NULL, &gWizardTowerRect);
			SDL_RenderCopy( gRenderer, gArcherTower, NULL, &gArcherTowerRect);
			SDL_RenderCopy( gRenderer, gCannonTower, NULL, &gCannonTowerRect);
			SDL_RenderCopy( gRenderer, gFreezeTower, NULL, &gFreezeTowerRect);

			//wait for second event
			//Handle events on queue
			SDL_Event e2;
			while( SDL_PollEvent( &e2 ) != 0 )
			{
				//User requests quit
				if( e2.type == SDL_QUIT )
				{
					quit = true;
				}

				int x2, y2;
				//If mouse click occurs, place image where mouse was clicked
				if(e2.type == SDL_MOUSEBUTTONDOWN){
					SDL_GetMouseState(&x2,&y2);
					if( (x2>= 80-35 && x2 <= 80-35+TOWER_MAX_DIMENSION) && (y2 >= 360-35+TOWER_MAX_DIMENSION && y2 <= 360-35+2*TOWER_MAX_DIMENSION) ){
						trigger1 = 1; //if wizard tower clicked
						break;
					}
					else if( (x2>= 80-35 && x2 <= 80-35+TOWER_MAX_DIMENSION) && (y2 >= 360-35+2*TOWER_MAX_DIMENSION && y2 <= 360-35+3*TOWER_MAX_DIMENSION) ){
						trigger1 = 2; //if archer tower clicked
						break;
					}
					else if( (x2>= 80-35 && x2 <= 80-35+TOWER_MAX_DIMENSION) && (y2 >= 360-35+3*TOWER_MAX_DIMENSION && y2 <= 360-35+4*TOWER_MAX_DIMENSION) ){
						trigger1 = 3; //if cannon tower clicked
						break;
					}
					else if( (x2>= 80-35 && x2 <= 80-35+TOWER_MAX_DIMENSION) && (y2 >= 360-35+4*TOWER_MAX_DIMENSION && y2 <= 360-35+5*TOWER_MAX_DIMENSION) ){
						trigger1 = 4; //if freeze tower clicked
						break;
					}
				}
				break;//get out of second event waiting loop
			}

		}
		switch(trigger1){
			case 1:
				SDL_RenderCopy(gRenderer, gWizardTower, NULL, &gTowerRect1);
				break;
			case 2:
				SDL_RenderCopy(gRenderer, gArcherTower, NULL, &gTowerRect1);
				break;
			case 3:
				SDL_RenderCopy(gRenderer, gCannonTower, NULL, &gTowerRect1);
				break;
			case 4:
				SDL_RenderCopy(gRenderer, gFreezeTower, NULL, &gTowerRect1);
				break;
			default:
				SDL_RenderCopy( gRenderer, gTower, NULL, &gTowerRect1 );
				break;
		}
*/

		renderEnemies();	// calls SDL_RenderCopy() on all enemies in the enemies vector
		towerSelector.render();

		//Update screen
		SDL_RenderPresent( gRenderer );

	}
		
	//Free resources and close SDL
	close();

	return 0;
}

// adds enemies every ____seconds
void addEnemies(MapDirections mapDirections) {
	// create a new enemy randomly
	int random = rand() % 2;
	switch(random) {
		case 0:
		{
			Goblin goblin(&gRenderer, mapDirections);
			enemies.push_back(goblin);
			break;
		}
		case 1:
		{
			Troll troll(&gRenderer, mapDirections);
			enemies.push_back(troll);
			break;
		}
	}	
}

/* Move all enemies in the enemies vector
 * Check return status of enemy.move(). If false, then the enemy has
 * reached the end of the path, and should be removed from the enemies vector
 */
void moveEnemies() {
	for(int i = 0; i < enemies.size(); i++) {
		if(enemies[i].move() == false) {
			enemies.erase(enemies.begin() + i);
		}
	}
}


/* Render all enemies in the enemies vector
*/
void renderEnemies() {
	for(int i = 0; i < enemies.size(); i++) {
		enemies[i].render();
	}
}

/* Return an SDL_Rect with an SDL_Surface as the background
 * Method assumes a square image is most ideal, as long as it is not too distorted
 * Returns an SDL_Rect that has no more than the maximum threshold of distortion
 * x and y are the coordinates of the position of the top of the SDL_Rect
*/
SDL_Rect getRect(SDL_Texture* texture, int maxDimension, int x, int y) {
	SDL_Rect container;

	// get height and width of original image
	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	double textureWidth = width;
	double textureHeight = height;

	if(textureHeight > textureWidth) {					// height = maxDimesion. Distort up to MAX_DISTORTION
		double factor = textureHeight / maxDimension;	// scaling factor to reduce height by
		textureHeight = maxDimension;					// height cannot exceed max dimension
		// check if factor will cause width to exceed MAX_DISTORTION			
		if(1 - (textureWidth / factor / maxDimension) > MAX_DISTORTION) { 
			textureWidth = textureWidth / factor * (1 + MAX_DISTORTION); // set width MAX_DISTORTION threshold
		} else {
			textureWidth = maxDimension;	// safe because width won't exceed MAX_DISTORTION threshold
		}
		
	} else {											// width = maxDimension. Distort height as necessary
		double factor = textureWidth / maxDimension;	// scaling factor to reduce height by
		textureWidth = maxDimension;					// height cannot exceed max dimension
		// check if factor will cause width to exceed MAX_DISTORTION			
		if(1 - (textureHeight / factor / maxDimension) > MAX_DISTORTION) { 
			textureHeight = textureHeight / factor * (1 + MAX_DISTORTION); // set width MAX_DISTORTION threshold
		} else {
			textureHeight = maxDimension;	// safe because width won't exceed MAX_DISTORTION threshold
		}
	}
	container.x = (int)(x - (.5 * textureWidth));
	container.y = (int)(y - (.5 * textureHeight));			
	container.w = (int)textureWidth;
	container.h = (int)textureHeight;

	return container;
}

/* Load call loadTexture for each image
*/
bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gGoblin = loadTexture("img/goblin.png");
	gTroll = loadTexture("img/troll.png");
	gWizard = loadTexture("img/wizard.png");
	gBackground = loadTexture("img/towerDefenseBackground.bmp");
	gWizardTower = loadTexture("img/wizardTower.png");
	gArcherTower = loadTexture("img/archerTower.png");
	gCannonTower = loadTexture("img/cannonTower.png");
	gFreezeTower = loadTexture("img/freezeTower.png");
	gTower = loadTexture("img/TowerSymbol.png");

	if(gBackground==NULL || gWizardTower==NULL || gArcherTower==NULL 
		|| gGoblin==NULL || gTroll == NULL || gTower == NULL)
	{
		printf( "Failed to a load texture image!\n" );
		success = false;
	}

	return success;
}

/* Return an SDL_Texture for the specified image, print errors appropriately
*/
SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

/* Deallocate memory
*/
void close()
{
	//Free loaded image
	SDL_DestroyTexture( gBackground );
	gBackground = NULL;
	SDL_DestroyTexture( gGoblin );
	gGoblin = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

/* Initialize SDL and SDL_image
*/
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}
