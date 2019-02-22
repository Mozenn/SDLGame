#pragma once
#include "Sprite.h"
 class AnimatedSprite : public Sprite
{

public:

	AnimatedSprite(ERenderPriority priority, float x = 0, float y = 0, AnimData* data = nullptr, int startAnimNum = 0);

	virtual ~AnimatedSprite();

	//Deallocates texture
	void free() override;

	void Initialize(AnimData* data, int startAnimNum); 

	void changeAnim(int num); 

	void updateAnim(float deltaTime); 

	//Loads images sprite sheet at specified path
	bool loadArrayFromFile(std::string path, SDL_Renderer* renderer);

protected : 

	struct AnimData* mAnimData; 

	int currentSprite;
	int currentFrame; 
	float frameTime; 
	float animFPS = 24.f; 
};

