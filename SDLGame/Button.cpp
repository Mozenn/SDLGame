#include "Button.h"



Button::Button()
{
}


Button::~Button()
{
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

LTexture* Button::getLTexture() const 
{
	return mTexture ;
}

void Button::setLTexture(LTexture* texture)
{
	mTexture = texture; 
}