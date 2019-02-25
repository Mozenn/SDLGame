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
};

struct AnimData
{
	std::vector<SDL_Texture*> sprites; 

	std::vector<AnimFrameData> frameInfo;
};

struct SpriteSheetData
{

	std::vector<AnimFrameData> frameInfo;
};

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Renderer* gRenderer; 