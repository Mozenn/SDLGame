#include "BaseSprite.h"

BaseSprite::BaseSprite(ERenderPriority priority, float x, float y) : mPriority(priority), mPosX(x), mPosY(y), mWidth(0), mHeight(0), mTexture(nullptr)
{
}

BaseSprite::~BaseSprite()
{
	//Deallocate
	free();
}

void BaseSprite::free()
{
	//Free texture if it exists
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

void BaseSprite::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions 
	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen 
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void BaseSprite::renderAtPosition(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { (int)mPosX, (int)mPosY, mWidth, mHeight };

	//Set clip rendering dimensions 
	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen 
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}


void BaseSprite::setAsRenderTarget()
{
	//Make self render target
	SDL_SetRenderTarget(gRenderer, mTexture);
}

void BaseSprite::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void BaseSprite::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void BaseSprite::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void BaseSprite::setPosition(float x, float y)
{
	mPosX = x;
	mPosY = y;
}

void BaseSprite::setPriority(ERenderPriority priority)
{
	mPriority = priority;
}

//############### GETTER 

int BaseSprite::getWidth()
{
	return mWidth;
}

int BaseSprite::getHeight()
{
	return mHeight;
}

float BaseSprite::getXPosition() const
{
	return mPosX; 
}

float BaseSprite::getYPosition() const
{
	return mPosY;
}


ERenderPriority BaseSprite::getPriority() const
{
	return mPriority;
}

bool operator==(BaseSprite const& a, BaseSprite const& b)
{
	return a.mPriority == b.mPriority; 
}

bool operator!=(BaseSprite const& a, BaseSprite const& b)
{
	return a.mPriority != b.mPriority;
}

bool operator<(BaseSprite const& a, BaseSprite const& b)
{
	return a.mPriority < b.mPriority;
}

bool operator>(BaseSprite const& a, BaseSprite const& b)
{
	return a.mPriority > b.mPriority;
}

