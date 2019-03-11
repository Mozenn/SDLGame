#pragma once

 #include <vector> 
#include <SDL_ttf.h>


template<typename T> bool PComp(T* a, T* b)
{
	return *a < *b;
}

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Renderer* gRenderer; 