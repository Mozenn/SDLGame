#pragma once
#include "Sprite.h"
 class AnimatedSprite : public Sprite
{

public:

	AnimatedSprite(ERenderPriority priority, float x = 0, float y = 0);

	virtual ~AnimatedSprite();

	//Deallocates texture
	void free() override;

	void Initialize(AnimData* data, int startAnimNum); 

	void changeAnim(int num); 

	void updateAnim(float deltaTime); 

	// TODO 
	//Loads images sprite sheet at specified path
	bool loadSprites(std::vector<std::string> path);

	// TODO : load the animData member
	bool loadSpriteSheet(std::string path, int width, int height); 

protected : 
	// Used if useSpriteSheet is false  
	struct AnimData* mAnimData; 

	// Use if useSpriteSheet is true 
	struct SpriteSheetData *mSpriteSheetData; 

	int currentAnim;
	int currentFrame; 
	float frameTime; 
	float animFPS = 24.f; 

	bool useSpriteSheet; 
};

