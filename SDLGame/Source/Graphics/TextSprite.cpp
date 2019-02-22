#include "TextSprite.h"

TextSprite::TextSprite(ERenderPriority priority, float x, float y) : BaseSprite(priority, x, y)
{
}

TextSprite::~TextSprite()
{

	free(); 
	TTF_CloseFont(mFont);
	mFont = nullptr;
}

bool TextSprite::load()
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended(mFont, mText.c_str(), mColor);
	if (textSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != nullptr;
}

bool TextSprite::load(std::string textureText, SDL_Color textColor, TTF_Font *font)
{
	//Get rid of preexisting texture
	free();

	mColor = textColor; 
	mText = textureText; 
	mFont = font; 

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, textureText.c_str(), textColor);
	if (textSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != nullptr;
}

void TextSprite::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	mColor = {red, green, blue, mColor.a}; 

	load(); 
}

void TextSprite::setAlpha(Uint8 alpha)
{
	mColor = { mColor.r, mColor.g, mColor.b, alpha };

	load();
}

void TextSprite::setFont(TTF_Font *font)
{
	mFont = font; 

	load();
}