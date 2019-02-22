#include "Button.h"



Button::Button()
{
	mTexture->loadFromFile("Assets / UI / ButtonDefault.png");
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

void Button::renderAtPosition(SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE)
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

bool Button::loadSpriteFromFile(std::string path)
{
	mTexture->loadFromFile(path); 
}

bool Button::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *font)
{
	mText->loadFromRenderedText
}

Sprite* Button::getSprite() const
{
	return mTexture;
}

void Button::setSprite(Sprite* texture)
{
	mTexture = texture;
}

void Button::setText(std::string text)
{
	mTexture->setColor(red, green, blue); 
}

void Button::setTextColor(Uint8 red, Uint8 green, Uint8 blue)
{
	if (mText)
	{
		mText->setColor(red, green, blue);
	}
	
}