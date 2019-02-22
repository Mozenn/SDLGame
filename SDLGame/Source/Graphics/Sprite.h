#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "BaseSprite.h"
#include "SLEngineTypes.h"


class Sprite : public BaseSprite
{

public:
	//Initializes variables
	Sprite(ERenderPriority priority, float x = 0, float y = 0);

	//Deallocates memory
	virtual ~Sprite();

	//Loads image at specified path
	virtual bool load(std::string path);

	bool createBlank(int width, int wheight, SDL_TextureAccess = SDL_TEXTUREACCESS_STREAMING); 

protected:



};