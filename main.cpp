//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <vector>
#include "Enemies/Enemy.h"
#include "MapDirections.h"
//#include "Towers.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 800;

const int TOWER_MAX_DIMENSION = 70;
const int ENEMY_MAX_DIMENSION = 60;
const double MAX_DISTORTION = .57;		// decimal of max percentage

// methods
bool init();		//Starts up SDL and creates window
bool loadMedia();	//Loads media
void close();		//Frees media and shuts down SDL
SDL_Rect getRect(SDL_Texture* texture, int maxDimension, int x, int y);
void moveEnemies();	// moves all enemies in the enemies vector
void renderEnemies(); 	// render all enemies in the enemies vector

// global vars
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

	MapDirections mapDirections;	// stores turning instructions for the map's path
    // add directions for the specific map (must be hard-coded for each map)
    mapDirections.setNext("right", 127);
    mapDirections.setNext("up", 170);
    mapDirections.setNext("right", 310);
    mapDirections.setNext("down", 489);
    mapDirections.setNext("right", 547);
    mapDirections.setNext("up", 330);
    mapDirections.setNext("right", SCREEN_WIDTH);

	Enemy enemy(&gRenderer, mapDirections);
	//Enemy enemy2(&gRenderer);
	
	enemies.push_back(enemy);
	//enemies.push_back(enemy2);


	//While application is running
	while( !quit )
	{
		int x,y;
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
				//if(e.tpye 
				SDL_GetMouseState(&x,&y);

			}
		}


		// create containers for each image which specifies its size and location
		//SDL_Rect goblinRect = getRect(gGoblin, ENEMY_MAX_DIMENSION, x, y);
		//SDL_Rect staticTrollRect = getRect(gTroll, ENEMY_MAX_DIMENSION, 151, 350);
		//SDL_Rect gWizardTowerRect = getRect(gWizardTower, TOWER_MAX_DIMENSION, 210, 390);
		//SDL_Rect gArcherTowerRect = getRect(gArcherTower, TOWER_MAX_DIMENSION, 210, 300);
		SDL_Rect gTowerRect1 = getRect(gTower, TOWER_MAX_DIMENSION,80,360);
		SDL_Rect gTowerRect2 = getRect(gTower, TOWER_MAX_DIMENSION,220,275);
		SDL_Rect gTowerRect3 = getRect(gTower, TOWER_MAX_DIMENSION,400,440);
		SDL_Rect gTowerRect4 = getRect(gTower, TOWER_MAX_DIMENSION,500,600);
		SDL_Rect gTowerRect5 = getRect(gTower, TOWER_MAX_DIMENSION,750,435);
		

		moveEnemies();	// moves all enemies in enemies vector (updates position)

		//Clear screen
		SDL_RenderClear( gRenderer );

		//Render texture to screen
		SDL_RenderCopy( gRenderer, gBackground, NULL, NULL );	// MUST BE FIRST: render background, automatically fills the window
		//SDL_RenderCopy( gRenderer, gGoblin, NULL, &goblinRect);	// render goblin to the center of the mouse-click
		//SDL_RenderCopy( gRenderer, gTroll, NULL, &staticTrollRect);
		//SDL_RenderCopy( gRenderer, gWizardTower, NULL, &gWizardTowerRect);
		//SDL_RenderCopy( gRenderer, gArcherTower, NULL, &gArcherTowerRect);
		//SDL_RenderCopy( gRenderer, gTower, NULL, &gTowerRect1);
		SDL_RenderCopy( gRenderer, gTower, NULL, &gTowerRect2);
		SDL_RenderCopy( gRenderer, gTower, NULL, &gTowerRect3);
		SDL_RenderCopy( gRenderer, gTower, NULL, &gTowerRect4);
		SDL_RenderCopy( gRenderer, gTower, NULL, &gTowerRect5);

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

			//wait for event?

		} else { //display regular tower symbol
			SDL_RenderCopy( gRenderer, gTower, NULL, &gTowerRect1);
		}
		//if tower2 symbol is clicked, then open up tower options menu (x and y based on top left corner of image (hence x-35,y-35 [35 = 1/2 of TOWER_MAX_DIMENSION])
		if( (x >= 220-35 && x <= 220-35+TOWER_MAX_DIMENSION) && (y >= 275-35 && y <= 275-35+TOWER_MAX_DIMENSION) ){
			//create containers for each image which specifies its size and location
			SDL_Rect gWizardTowerRect = getRect(gWizardTower, TOWER_MAX_DIMENSION,220,275+TOWER_MAX_DIMENSION );
			SDL_Rect gArcherTowerRect = getRect(gArcherTower, TOWER_MAX_DIMENSION,220,275+2*TOWER_MAX_DIMENSION );
			SDL_Rect gCannonTowerRect = getRect(gCannonTower, TOWER_MAX_DIMENSION,220,275+3*TOWER_MAX_DIMENSION );
			SDL_Rect gFreezeTowerRect = getRect(gFreezeTower, TOWER_MAX_DIMENSION,220,275+4*TOWER_MAX_DIMENSION );

			//open texutre on screen without rendering
			SDL_RenderCopy( gRenderer, gWizardTower, NULL, &gWizardTowerRect);
			SDL_RenderCopy( gRenderer, gArcherTower, NULL, &gArcherTowerRect);
			SDL_RenderCopy( gRenderer, gCannonTower, NULL, &gCannonTowerRect);
			SDL_RenderCopy( gRenderer, gFreezeTower, NULL, &gFreezeTowerRect);

			//wait for event?

		} else { //display regular tower symbol
			SDL_RenderCopy( gRenderer, gTower, NULL, &gTowerRect1);
		}
		//if tower1 symbol is clicked, then open up tower options menu (x and y based on top left corner of image (hence x-35,y-35 [35 = 1/2 of TOWER_MAX_DIMENSION])
		if( (x >= 400-35 && x <= 400-35+TOWER_MAX_DIMENSION) && (y >= 440-35 && y <= 440-35+TOWER_MAX_DIMENSION) ){
			//create containers for each image which specifies its size and location
			SDL_Rect gWizardTowerRect = getRect(gWizardTower, TOWER_MAX_DIMENSION,400,440+TOWER_MAX_DIMENSION );
			SDL_Rect gArcherTowerRect = getRect(gArcherTower, TOWER_MAX_DIMENSION,400,440+2*TOWER_MAX_DIMENSION );
			SDL_Rect gCannonTowerRect = getRect(gCannonTower, TOWER_MAX_DIMENSION,400,440+3*TOWER_MAX_DIMENSION );
			SDL_Rect gFreezeTowerRect = getRect(gFreezeTower, TOWER_MAX_DIMENSION,400,440+4*TOWER_MAX_DIMENSION );

			//open texutre on screen without rendering
			SDL_RenderCopy( gRenderer, gWizardTower, NULL, &gWizardTowerRect);
			SDL_RenderCopy( gRenderer, gArcherTower, NULL, &gArcherTowerRect);
			SDL_RenderCopy( gRenderer, gCannonTower, NULL, &gCannonTowerRect);
			SDL_RenderCopy( gRenderer, gFreezeTower, NULL, &gFreezeTowerRect);

			//wait for event?

		} else { //display regular tower symbol
			SDL_RenderCopy( gRenderer, gTower, NULL, &gTowerRect1);
		}
		//if tower1 symbol is clicked, then open up tower options menu (x and y based on top left corner of image (hence x-35,y-35 [35 = 1/2 of TOWER_MAX_DIMENSION])
		if( (x >= 500-35 && x <= 500-35+TOWER_MAX_DIMENSION) && (y >= 600-35 && y <= 600-35+TOWER_MAX_DIMENSION) ){
			//create containers for each image which specifies its size and location
			SDL_Rect gWizardTowerRect = getRect(gWizardTower, TOWER_MAX_DIMENSION,500,600-TOWER_MAX_DIMENSION );
			SDL_Rect gArcherTowerRect = getRect(gArcherTower, TOWER_MAX_DIMENSION,500,600-2*TOWER_MAX_DIMENSION );
			SDL_Rect gCannonTowerRect = getRect(gCannonTower, TOWER_MAX_DIMENSION,500,600-3*TOWER_MAX_DIMENSION );
			SDL_Rect gFreezeTowerRect = getRect(gFreezeTower, TOWER_MAX_DIMENSION,500,600-4*TOWER_MAX_DIMENSION );

			//open texutre on screen without rendering
			SDL_RenderCopy( gRenderer, gWizardTower, NULL, &gWizardTowerRect);
			SDL_RenderCopy( gRenderer, gArcherTower, NULL, &gArcherTowerRect);
			SDL_RenderCopy( gRenderer, gCannonTower, NULL, &gCannonTowerRect);
			SDL_RenderCopy( gRenderer, gFreezeTower, NULL, &gFreezeTowerRect);

			//wait for event?

		} else { //display regular tower symbol
			SDL_RenderCopy( gRenderer, gTower, NULL, &gTowerRect1);
		}
		//if tower1 symbol is clicked, then open up tower options menu (x and y based on top left corner of image (hence x-35,y-35 [35 = 1/2 of TOWER_MAX_DIMENSION])
		if( (x >= 750-35 && x <= 750-35+TOWER_MAX_DIMENSION) && (y >= 435-35 && y <= 435-35+TOWER_MAX_DIMENSION) ){
			//create containers for each image which specifies its size and location
			SDL_Rect gWizardTowerRect = getRect(gWizardTower, TOWER_MAX_DIMENSION,750,435+TOWER_MAX_DIMENSION );
			SDL_Rect gArcherTowerRect = getRect(gArcherTower, TOWER_MAX_DIMENSION,750,435+2*TOWER_MAX_DIMENSION );
			SDL_Rect gCannonTowerRect = getRect(gCannonTower, TOWER_MAX_DIMENSION,750,435+3*TOWER_MAX_DIMENSION );
			SDL_Rect gFreezeTowerRect = getRect(gFreezeTower, TOWER_MAX_DIMENSION,750,435+4*TOWER_MAX_DIMENSION );

			//open texutre on screen without rendering
			SDL_RenderCopy( gRenderer, gWizardTower, NULL, &gWizardTowerRect);
			SDL_RenderCopy( gRenderer, gArcherTower, NULL, &gArcherTowerRect);
			SDL_RenderCopy( gRenderer, gCannonTower, NULL, &gCannonTowerRect);
			SDL_RenderCopy( gRenderer, gFreezeTower, NULL, &gFreezeTowerRect);

			//wait for event?

		} else { //display regular tower symbol
			SDL_RenderCopy( gRenderer, gTower, NULL, &gTowerRect1);
		}


		renderEnemies();	// calls SDL_RenderCopy() on all enemies in the enemies vector

		//Update screen
		SDL_RenderPresent( gRenderer );

	}
		
	//Free resources and close SDL
	close();

	return 0;
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
