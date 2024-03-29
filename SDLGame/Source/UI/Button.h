#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "Sprite.h"
#include "TextSprite.h"

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

	TextSprite* getText() const; 

	//Set attribute 
	bool loadSprite(std::string path);

	bool loadText(std::string textureText, SDL_Color textColor, TTF_Font *font);

	void setTextureColor(Uint8 red, Uint8 green, Uint8 blue);

	void setTextureAlpha(Uint8 alpha);

	void setTextColor(Uint8 red, Uint8 green, Uint8 blue);

	void setText(std::string text); 

	void setTextAlpha(Uint8 alpha);

	void setSprite(Sprite* sprite); 

	void setTextSprite(TextSprite* text); 

private :

	Sprite* mTexture; 
	TextSprite* mText; 
};

