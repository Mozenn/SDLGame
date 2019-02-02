#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "Sprite.h"

class Button
{
public:

	Button(); 

	Button(Sprite* texture);

	~Button();

	void free(); 


	//Handles mouse event
	//void handleEvent(SDL_Event* e);

	bool isPushed(SDL_Event* e);
	bool isHovered();

	// Get attribute 
	Sprite* getSprite() const; 

	//Set attribute 
	void setSprite(Sprite* texture);

private :

	Sprite* mTexture; 
	Sprite* mText; 
};

