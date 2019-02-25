#pragma once
#include "BaseSprite.h"
class TextSprite : public BaseSprite
{

public:

	TextSprite(ERenderPriority priority, float x = 0, float y = 0);

	virtual ~TextSprite();

	bool load(); 

	bool load(std::string textureText , SDL_Color textColor, TTF_Font *font ) ;

	// SETTER 

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set color modulation
	void setFont(TTF_Font *font);

	void setText(std::string text); 

protected:

	SDL_Color mColor;
	std::string mText;
	TTF_Font* mFont;

};
