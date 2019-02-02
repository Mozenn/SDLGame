#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "SLEngineTypes.h"


class Sprite
{

public:
	//Initializes variables
	Sprite(ERenderPriority priority, int x = 0, int y = 0);

	//Deallocates memory
	~Sprite();

	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer* renderer);

	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font *font);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x , int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Renders texture at Position 
	void renderAtPosition( SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);


	// SETTER 

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	void setPosition(int x, int y);

	void setPriority(ERenderPriority); 

	//GETTER 

	int getWidth();
	int getHeight();

	SDL_Point getPosition() const; 

	ERenderPriority getPriority() const; 

private:

	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image Rendering Position 
	SDL_Point mPosition;

	//Image dimensions
	int mWidth;
	int mHeight;

	ERenderPriority mPriority; 

};