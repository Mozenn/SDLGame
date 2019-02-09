#pragma once
#include "Sprite.h"
class TextSprite : public Sprite
{

public:

	TextSprite(ERenderPriority priority, int x = 0, int y = 0, AnimData* data = nullptr, int startAnimNum = 0);

	virtual ~TextSprite();

	bool load(std::string textureText, SDL_Color textColor, TTF_Font *font) override;
protected:

	SDL_Color color;
	std::string text;
	TTF_Font* font;

};
