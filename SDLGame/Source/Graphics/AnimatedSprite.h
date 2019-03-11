#pragma once
#include "Sprite.h"

struct AnimFrameData
{
	//index of the first frame of animation 
	int startFrame;
	//total number of frame 
	int numFrames;
	// Array of sprite clips for each frame 
	//std::vector<SDL_Rect> spriteClips;
};

struct SpriteSheetData
{
	int framePerRow;

	int frameWidth;

	int frameHeight;

	std::vector<AnimFrameData> animData;
};

 class AnimatedSprite : public Sprite
{

public:

	AnimatedSprite(ERenderPriority priority, float x = 0, float y = 0);

	virtual ~AnimatedSprite();

	//Deallocates texture
	void free() override;

	void changeAnim(int num); 

	void updateAnim(float deltaTime); 

	// TODO : load the animData member
	bool loadSpriteSheet(std::string path, int frameWidth, int frameHeight, std::vector<AnimFrameData> AnimData);

	//Renders texture at given point
	virtual void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) override;

	//Renders texture at Position 
	virtual void renderAtPosition(SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) override ;


	//GETTER
	int getFrameWidth() const; 
	int getFrameHeight() const;

protected : 

	// Use if useSpriteSheet is true 
	struct SpriteSheetData *mSpriteSheetData; 


	int currentAnim;
	int currentFrame; 
	float frameTime; 
	float animFPS = 6.f; 
};

