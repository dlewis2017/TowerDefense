#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Enemy.h"
using namespace std;

Enemy::Enemy(SDL_Renderer** gRendererPtr, MapDirections pathInfo)
{
	ENEMY_MAX_DIMENSION = 60;
	MAX_DISTORTION = .57;		// decimal of max percentage
	gRenderer = gRendererPtr;

    mapDirections = pathInfo;
	
    //Initialize the offsets
    mPosX = ENEMY_MAX_DIMENSION/2;
    mPosY = 405;

    moveInterval = 120;         // move every 100 microseconds
    gettimeofday(&tp, NULL);
    lastMoveTime = (tp.tv_sec * 1000 + tp.tv_usec / 1000) - moveInterval;   // will trigger movement immediately
}

/* Not necessary
// testing purposes only, included in SDL tutorial from lazyfoo
void Enemy::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= ENEMY_VEL; break;
            case SDLK_DOWN: mVelY += ENEMY_VEL; break;
            case SDLK_LEFT: mVelX -= ENEMY_VEL; break;
            case SDLK_RIGHT: mVelX += ENEMY_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += ENEMY_VEL; break;
            case SDLK_DOWN: mVelY -= ENEMY_VEL; break;
            case SDLK_LEFT: mVelX += ENEMY_VEL; break;
            case SDLK_RIGHT: mVelX -= ENEMY_VEL; break;
        }
    }
}
*/

/* Move the enemy. Return false if the enemy is done moving (reached end of path)
 * Movement instructions come from MapDirections object
 * Only move every moveInterval number of milliseconds, to standardize movement across different computers
 */
bool Enemy::move()
{ 
    // check if it is time to move again or not
    gettimeofday(&tp, NULL);
    long int curTime = tp.tv_sec * 1000 + tp.tv_usec / 1000; //get current timestamp in milliseconds
    if(curTime - lastMoveTime < moveInterval) return true; // don't move unless it has been long enough

    if(mapDirections.isEnd() == false) {

        string curDirection = mapDirections.getDir();
        if (curDirection == "right") {
            mPosX += ENEMY_VEL;
            if(mPosX >= mapDirections.getStop()) mapDirections.next();  // check if ready for next direction
        } 
        else if(curDirection == "left") {
            mPosX -= ENEMY_VEL;
            if(mPosX <= mapDirections.getStop()) mapDirections.next();
        } 
        else if(curDirection == "up") {
            mPosY -= ENEMY_VEL;
            if(mPosY <= mapDirections.getStop()) mapDirections.next();
        } 
        else if(curDirection == "down") {
            mPosY += ENEMY_VEL; 
            if(mPosY >= mapDirections.getStop()) mapDirections.next();
        }
        lastMoveTime = curTime;     // track that enemy just moved so it doesn't move again before it is supposed to
        return true;
    } else {
        cout << "done moving" << endl;
        return false;
    }
}

/* Update the position of the container, and make a call to SDL_RenderCopy()
*/
void Enemy::render()
{
    // update the enemy's position;
    enemyRect.x = mPosX;
    enemyRect.y = mPosY;
    SDL_RenderCopy( *gRenderer, gEnemy, NULL, &enemyRect);  // renderings need to be pushed to screen still. happens in main
	
}

/* Return an SDL_Rect with an SDL_Surface as the background
 * Method assumes a square image is most ideal, as long as it is not too distorted
 * Returns an SDL_Rect that has no more than the maximum threshold of distortion
 * x and y are the coordinates of the position of the top of the SDL_Rect
*/
SDL_Rect Enemy::getRect(SDL_Texture* texture, int maxDimension, int x, int y) {
    SDL_Rect container;

    // get height and width of original image
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    double textureWidth = width;
    double textureHeight = height;

    if(textureHeight > textureWidth) {                  // height = maxDimesion. Distort up to MAX_DISTORTION
        double factor = textureHeight / maxDimension;   // scaling factor to reduce height by
        textureHeight = maxDimension;                   // height cannot exceed max dimension
        // check if factor will cause width to exceed MAX_DISTORTION            
        if(1 - (textureWidth / factor / maxDimension) > MAX_DISTORTION) { 
            textureWidth = textureWidth / factor * (1 + MAX_DISTORTION); // set width MAX_DISTORTION threshold
        } else {
            textureWidth = maxDimension;    // safe because width won't exceed MAX_DISTORTION threshold
        }
        
    } else {                                            // width = maxDimension. Distort height as necessary
        double factor = textureWidth / maxDimension;    // scaling factor to reduce height by
        textureWidth = maxDimension;                    // height cannot exceed max dimension
        // check if factor will cause width to exceed MAX_DISTORTION            
        if(1 - (textureHeight / factor / maxDimension) > MAX_DISTORTION) { 
            textureHeight = textureHeight / factor * (1 + MAX_DISTORTION); // set width MAX_DISTORTION threshold
        } else {
            textureHeight = maxDimension;   // safe because width won't exceed MAX_DISTORTION threshold
        }
    }
    container.x = (int)(x - (.5 * textureWidth));
    container.y = (int)(y - (.5 * textureHeight));          
    container.w = (int)textureWidth;
    container.h = (int)textureHeight;

    return container;
}

/* Return an SDL_Texture for the specified image, print errors appropriately
*/
SDL_Texture* Enemy::loadTexture( std::string path )
{
    SDL_Texture* newTexture = NULL; //The final texture

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( *gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

// return x position of enemy
double Enemy::getPosX() {
	return mPosX;
}

// return y position of enemy
double Enemy::getPosY() {
	return mPosY;
}
