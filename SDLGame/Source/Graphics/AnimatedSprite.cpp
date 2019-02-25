#include "AnimatedSprite.h"



AnimatedSprite::AnimatedSprite(ERenderPriority priority, float x , float y) : Sprite(priority,x,y)
{
}


AnimatedSprite::~AnimatedSprite()
{
	free(); 
}

void AnimatedSprite::free()
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

void AnimatedSprite::Initialize(AnimData* data, int startAnimNum)
{
	mAnimData = data;
	changeAnim(startAnimNum); 

}

void AnimatedSprite::changeAnim(int num)
{
	currentAnim = num; 
	currentFrame = 0; 
	frameTime = 0.f; 

	//set Starting frame 
	int spriteNum = mAnimData->frameInfo[currentAnim].startFrame; 
	mTexture = mAnimData->sprites[spriteNum]; 
}

void AnimatedSprite::updateAnim(float deltaTime)
{
	frameTime += deltaTime; 

	//change to next frame ? 
	if (frameTime > 1 / animFPS)
	{
		currentFrame += frameTime * animFPS; 

		if (currentFrame >= mAnimData->frameInfo[currentAnim].numFrames)
		{
			currentFrame = currentFrame % mAnimData->frameInfo[currentAnim].numFrames; 
		}

		//update active sprite 
		int spriteNum = mAnimData->frameInfo[currentAnim].startFrame + currentFrame; 
		mTexture = mAnimData->sprites[spriteNum]; 

		frameTime = fmod(frameTime, 1 / animFPS); 
	}
}