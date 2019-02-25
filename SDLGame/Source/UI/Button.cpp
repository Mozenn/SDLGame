#include "Button.h"



Button::Button()
{
	
}

Button::~Button()
{
	free(); 
}

void Button::free()
{
	mTexture->free(); 
	mText->free(); 
}

void Button::render(int x, int y, SDL_Rect* clip , double angle , SDL_Point* center , SDL_RendererFlip flip )
{
	mTexture->render(x,y,clip,angle,center,flip); 
	if (mText != nullptr)
	{
		mText->render(x, y, clip, angle, center, flip);
	}
}

void Button::renderAtPosition(SDL_Rect* clip , double angle , SDL_Point* center , SDL_RendererFlip flip )
{
	mTexture->renderAtPosition( clip, angle, center, flip);
	if (mText != nullptr)
	{
		mText->renderAtPosition(clip, angle, center, flip);
	}
}


bool Button::isPushed(SDL_Event* e)
{
	bool result = false;

	if (e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x >= mTexture->getXPosition() && x <= mTexture->getYPosition() + mTexture->getWidth() && y >= mTexture->getYPosition() && y <= mTexture->getYPosition() + mTexture->getHeight())
		{
			result = true;
		}
	}

	return result;
}

bool Button::isHovered()
{
	bool result = false;

	//Get mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (x >= mTexture->getXPosition() && x <= mTexture->getXPosition() + mTexture->getWidth() && y >= mTexture->getYPosition() && y <= mTexture->getYPosition() + mTexture->getHeight())
	{
		result = true;
	}

	return result;
}

bool Button::loadSprite(std::string path)
{
	return mTexture->load(path); 
}

bool Button::loadText(std::string textureText, SDL_Color textColor, TTF_Font *font)
{
	return mText->load(textureText, textColor, font); 
}

Sprite* Button::getSprite() const
{
	return mTexture;
}

TextSprite* Button::getText() const
{
	return mText; 
}

void Button::setSprite(Sprite* texture)
{
	mTexture = texture;
}

void Button::setTextSprite(TextSprite* text)
{
	mText = text; 
}

void Button::setTextureColor(Uint8 red, Uint8 green, Uint8 blue)
{
	mTexture->setColor(red, green, blue);
}

void Button::setTextureAlpha(Uint8 alpha)
{
	mTexture->setAlpha(alpha); 
}

void Button::setText(std::string text)
{
	mText->setText(text); 
}

void Button::setTextColor(Uint8 red, Uint8 green, Uint8 blue)
{
	if (mText)
	{
		mText->setColor(red, green, blue);
	}
	
}

void Button::setTextAlpha(Uint8 alpha)
{
	if (mText)
	{
		mText->setAlpha(alpha);
	}
}