#include "Button.h"



Button::Button()
{
	mTexture = nullptr;
}

Button::Button(Sprite* texture)
{
	mTexture = texture;
}


Button::~Button()
{
	mTexture->free(); 
}

void Button::free()
{
	mTexture->free(); 
	mText->free(); 
}


//void Button::handleEvent(SDL_Event* e)
//{
//
//}

bool Button::isPushed(SDL_Event* e)
{
	bool result = false;

	if (e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x >= mTexture->getPosition().x && x <= mTexture->getPosition().x + mTexture->getWidth() && y >= mTexture->getPosition().y && y <= mTexture->getPosition().y + mTexture->getHeight())
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

	if (x >= mTexture->getPosition().x && x <= mTexture->getPosition().x + mTexture->getWidth() && y >= mTexture->getPosition().y && y <= mTexture->getPosition().y + mTexture->getHeight())
	{
		result = true;
	}

	return result;
}

Sprite* Button::getSprite() const
{
	return mTexture;
}

void Button::setSprite(Sprite* texture)
{
	mTexture = texture;
}