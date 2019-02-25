#include "Actor.h"

Actor::Actor(Sprite* sprite) : mVelX(0), mVelY(0), mSprite(sprite)
{
}

Actor::~Actor()
{

}


void Actor::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_z: mVelY -= MAX_VEL; break;
		case SDLK_s: mVelY += MAX_VEL; break;
		case SDLK_q: mVelX -= MAX_VEL; break;
		case SDLK_d: mVelX += MAX_VEL; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_z: mVelY += MAX_VEL; break;
		case SDLK_s: mVelY -= MAX_VEL; break;
		case SDLK_q: mVelX += MAX_VEL; break;
		case SDLK_d: mVelX -= MAX_VEL; break;
		}
	}
}

void Actor::move(float deltaTime)
{
	//Move the dot left or right
	mPosX += mVelX * deltaTime;

	//If the dot went too far to the left or right
	if (mPosX < 0)
	{
		//Move back
		mPosX = 0;
	}
	else if (mPosX + mWidth > SCREEN_WIDTH)
	{
		mPosX = SCREEN_WIDTH - mWidth;
	}

	//Move the dot up or down
	mPosY += mVelY * deltaTime;

	//If the dot went too far up or down
	if (mPosY < 0)
	{
		//Move back
		mPosY -= mVelY;
	}
	else if (mPosY + mHeight > SCREEN_HEIGHT)
	{
		mPosY = SCREEN_HEIGHT - mHeight;
	}
}