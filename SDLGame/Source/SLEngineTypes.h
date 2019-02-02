#pragma once

 #include <vector> 

enum class ERenderPriority 
{
	BACK = 0,
	MIDDLE = 1,
	FRONT = 2,
	UI = 3
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