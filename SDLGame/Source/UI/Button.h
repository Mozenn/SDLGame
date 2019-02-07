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

	~Button();

	void free(); 

	void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE); 

	void renderAtPosition(SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Handles mouse event
	//void handleEvent(SDL_Event* e);

	bool isPushed(SDL_Event* e);
	bool isHovered();

	// Get attribute 

	Sprite* getSprite() const; 

	//Set attribute 
	bool loadSpriteFromFile(std::string path);

	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *font);

	void setTextureColor(Uint8 red, Uint8 green, Uint8 blue);

	void setTextColor(Uint8 red, Uint8 green, Uint8 blue);

	void setText(std::string text); 

	void setSprite(Sprite* sprite); 

private :

	Sprite* mTexture; 
	Sprite* mText; 
};

