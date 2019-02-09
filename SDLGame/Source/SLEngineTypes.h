#pragma once

 #include <vector> 
#include <SDL_ttf.h>

enum ERenderPriority 
{
	BACK1 = 0,
	BACK2 = 1,
	BACK3 = 2,
	FRONT1 = 3,
	FRONT2 = 4,
	FRONT3 = 5,
	UI = 6
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

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Renderer* gRenderer; 