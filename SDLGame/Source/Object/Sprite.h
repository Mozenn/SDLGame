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
	virtual ~Sprite();

	//Loads image at specified path
	virtual bool load(std::string path);

	bool createBlank(int width, int wheight, SDL_TextureAccess = SDL_TEXTUREACCESS_STREAMING); 

	void setAsRenderTarget(); 

	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *font);

	//Deallocates texture
	virtual void free();

	//Renders texture at given point
	void render(int x , int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Renders texture at Position 
	void renderAtPosition( SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// SETTER 

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	void setPosition(int x , int y );

	void setPriority(ERenderPriority); 

	//GETTER 

	int getWidth();
	int getHeight();

	SDL_Point getPosition() const; 

	ERenderPriority getPriority() const; 

protected:

	//The actual hardware texture
	SDL_Texture* mTexture;


	//Image Rendering Position 
	float mPosX;
	float mPosY;

	//Image dimensions
	int mWidth;
	int mHeight;

	ERenderPriority mPriority; 

};