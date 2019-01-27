#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"

class Button
{
public:

	Button(); 

	Button(LTexture* Texture);

	~Button();

	//Handles mouse event
	//void handleEvent(SDL_Event* e);

	bool isPushed(SDL_Event* e);

	// Get attribute 
	LTexture* getLTexture() const; 

	//Set attribute 
	void setLTexture(LTexture* texture);

private :

	LTexture* mTexture; 
};

