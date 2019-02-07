#pragma once
#include "AnimatedSprite.h"
class MovableSprite : public AnimatedSprite
{
public:
	MovableSprite(ERenderPriority priority, int x = 0, int y = 0, AnimData* data = nullptr, int startAnimNum = 0);

	~MovableSprite();

	//Takes key presses and adjusts velocity
	void handleEvent(SDL_Event& e);

	void move(float deltaTime);

protected : 

	float mVelX; 
	float mVelY; 

	//Maximum axis velocity 
	static const int MAX_VEL = 640;
};

