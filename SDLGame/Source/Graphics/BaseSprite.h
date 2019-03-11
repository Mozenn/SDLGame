#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "SLEngineTypes.h"

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

class BaseSprite
{

public:

	//Initializes variables
	BaseSprite(ERenderPriority priority, float x = 0, float y = 0);

	//Deallocates memory
	virtual ~BaseSprite();

	//Deallocates texture
	virtual void free();

	//Renders texture at given point
	virtual void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Renders texture at Position 
	virtual void renderAtPosition(SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void setAsRenderTarget();

	// SETTER 

	//Set color modulation
	virtual void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	virtual void setAlpha(Uint8 alpha);

	void setPosition(float x, float y);

	void setPriority(ERenderPriority);

	//GETTER 

	int getWidth();
	int getHeight();

	float getXPosition() const;
	float getYPosition() const;

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

	friend bool operator==(BaseSprite const& a, BaseSprite const& b);
	friend bool operator!=(BaseSprite const& a, BaseSprite const& b);
	friend bool operator<(BaseSprite const& a, BaseSprite const& b);
	friend bool operator>(BaseSprite const& a, BaseSprite const& b);

};

