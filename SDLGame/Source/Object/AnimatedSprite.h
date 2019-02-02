#pragma once
#include "Sprite.h"
 class AnimatedSprite : public Sprite
{

public:

	AnimatedSprite(ERenderPriority priority, int x = 0, int y = 0, AnimData* data,int startAnimNum);

	~AnimatedSprite();

	void Initialize(AnimData* data, int startAnimNum); 

	void changeAnim(int num); 

	void updateAnim(float deltaTime); 

	//Loads images sprite sheet at specified path
	bool loadArrayFromFile(std::string path, SDL_Renderer* renderer);

private : 

	struct AnimData* mAnimData; 

	int currentSprite;
	int currentFrame; 
	float frameTime; 
	float animFPS = 24.f; 
};

