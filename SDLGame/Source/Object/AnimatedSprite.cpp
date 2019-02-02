#include "AnimatedSprite.h"



AnimatedSprite::AnimatedSprite(ERenderPriority priority, int x , int y, AnimData* data, int startAnimNum) : Sprite(priority,x,y)
{
	Initialize(data,startAnimNum); 
}


AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Initialize(AnimData* data, int startAnimNum)
{
	mAnimData = data;
	changeAnim(startAnimNum); 

}

void AnimatedSprite::changeAnim(int num)
{

}