#pragma once
#include "Sprite.h"

class Actor
{
public:

	Actor(Sprite* sprite = nullptr); 

	~Actor(); 

	//Takes key presses and adjusts velocity
	void handleEvent(SDL_Event& e);

	void move(float deltaTime);

protected:

	//Position 
	float mPosX;
	float mPosY;

	//Velocity
	float mVelX;
	float mVelY;

	//Maximum axis velocity 
	static const int MAX_VEL = 640;

	Sprite* mSprite; 
};
