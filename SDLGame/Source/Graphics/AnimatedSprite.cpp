#include "AnimatedSprite.h"
#include <math.h>  



AnimatedSprite::AnimatedSprite(ERenderPriority priority, float x , float y) : Sprite(priority,x,y), currentAnim(0), currentFrame(0), frameTime(0)
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
	if (mSpriteSheetData)
	{
		delete mSpriteSheetData; 
	}
}

bool AnimatedSprite::loadSpriteSheet(std::string path, int frameWidth, int frameHeight, std::vector<AnimFrameData> AnimData)
{
	load(path); 
	mSpriteSheetData = new SpriteSheetData(); 
	mSpriteSheetData->animData = AnimData; 
	mSpriteSheetData->frameWidth = frameWidth;
	mSpriteSheetData->frameHeight = frameHeight;
	mSpriteSheetData->framePerRow = floor(mWidth / mSpriteSheetData->frameWidth);

	//int nbTotalFrame = mSpriteSheetData->framePerRow * (mHeight / mSpriteSheetData->FrameHeigth); 

	//SDL_Rect temp; 
	//temp.h = frameHeight; 
	//temp.w = frameWidth; 

	//for (int r = 0; r < (mHeight / mSpriteSheetData->FrameHeigth); r++)
	//{
	//	for (int c = 0; c < mSpriteSheetData->framePerRow; c++)
	//	{
	//		temp.x = frameWidth * c; 
	//		temp.y = frameHeight * r; 
	//		mSpriteSheetData->AnimData.spriteClips
	//	}
	//	
	//}

	return true; 
}

void AnimatedSprite::changeAnim(int num)
{
	currentAnim = num; 
	currentFrame = 0; 
	frameTime = 0.f; 

}

//TODO 
void AnimatedSprite::updateAnim(float deltaTime)
{
	frameTime += deltaTime; 

	//change to next frame ? 
	if (frameTime > 1 / animFPS)
	{
		currentFrame += frameTime * animFPS; 

		if (currentFrame >= mSpriteSheetData->animData[currentAnim].numFrames)
		{
			currentFrame = currentFrame % mSpriteSheetData->animData[currentAnim].numFrames;
		}

		frameTime = fmod(frameTime, 1 / animFPS); 
	}
}

//TODO 
void AnimatedSprite::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{

}

void AnimatedSprite::renderAtPosition(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { (int)mPosX, (int)mPosY, mWidth, mHeight };

	SDL_Rect renderedClip; 

	//Set clip rendering dimensions 
	if (clip != nullptr)
	{
		renderedClip = *clip; 
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	else
	{
		renderQuad.h = mSpriteSheetData->frameHeight;
		renderQuad.w = mSpriteSheetData->frameWidth;
		renderedClip.h = mSpriteSheetData->frameHeight;
		renderedClip.w = mSpriteSheetData->frameWidth;
		renderedClip.x = ((currentFrame + mSpriteSheetData->animData[currentAnim].startFrame) % mSpriteSheetData->framePerRow) * mSpriteSheetData->frameWidth;
		renderedClip.y = (currentFrame + mSpriteSheetData->animData[currentAnim].startFrame) / mSpriteSheetData->framePerRow;
	}

	//Render to screen 
	SDL_RenderCopyEx(gRenderer, mTexture, &renderedClip, &renderQuad, angle, center, flip);
}

//GETTER

int AnimatedSprite::getFrameWidth() const
{
	return mSpriteSheetData->frameWidth; 
}

int AnimatedSprite::getFrameHeight() const
{
	return mSpriteSheetData->frameHeight;
}