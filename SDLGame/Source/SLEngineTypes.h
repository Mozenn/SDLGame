#pragma once

 #include <vector> 
#include <SDL_ttf.h>

enum ERenderPriority 
{
	BACK3 = 0,
	BACK2 = 1,
	BACK1 = 2,
	FRONT3 = 3,
	FRONT2 = 4,
	FRONT1 = 5,
	UI2 = 6,
	UI1 = 7
};

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

template<typename T> bool PComp(T* a, T* b)
{
	return *a < *b;
}

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Renderer* gRenderer; 