#pragma once
#include "AnimatedSprite.h"
class MovableSprite : public AnimatedSprite
{
public:
	MovableSprite(ERenderPriority priority, int x = 0, int y = 0);
	~MovableSprite();
};

