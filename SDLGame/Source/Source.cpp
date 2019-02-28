#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <list>
#include <sstream>
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Button.h"
#include "Timer.h" 
#include "Window.h"
#include "SLEngineTypes.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;


//######### GLOBAL Ressource #########
//TODO : faire asset manager pour texture,sound, sprite, font, ...

//The window we'll be rendering to
Window gWindow; 

//The window renderer
SDL_Renderer* gRenderer = nullptr;

//Globally used font
TTF_Font *gFont = nullptr;

//Controller 
SDL_Joystick* gGameController = nullptr;
SDL_Haptic* gControllerHaptic = nullptr;
const int JOYSTICK_DEAD_ZONE = 8000;

//Textures
std::list<BaseSprite*> Sprites; 
Sprite*gBackTexture = new Sprite(BACK2);
TextSprite*gTextTexture = new TextSprite(BACK1);
Sprite* gPH1 = new Sprite(FRONT1); 
AnimatedSprite* gPHAnim = new AnimatedSprite(FRONT1); 





//UI 
//Button*gStartButton = new Button(); 

bool init()
{
	//Initialization flag 
	bool success = true;

	//Initialize SDL 
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		if (!gWindow.init())
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = gWindow.createRenderer();
			if (gRenderer == nullptr)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading succes flag 
	bool success = true;


	//	//Load BG texture
	//if (!gBackTexture->load("Assets/UI/MainMenuBackground.png"))
	//{
	//	printf("Failed to load texture image!\n");
	//	success = false;
	//}
	//else
	//{
	//	//Set standard alpha blending
	//	gBackTexture->setBlendMode(SDL_BLENDMODE_BLEND);
	//	Sprites.push_back(gBackTexture);
	//}

	////Load PH1 texture
	//if (!gPH1->load("Assets/Art/PH1.png"))
	//{
	//	printf("Failed to load texture image!\n");
	//	success = false;
	//}
	//else
	//{
	//	//Set standard alpha blending
	//	gPH1->setBlendMode(SDL_BLENDMODE_BLEND);
	//	gPH1->setPosition((SCREEN_WIDTH - gPH1->getWidth()) / 2, (SCREEN_HEIGHT - gPH1->getHeight()) / 1.5);
	//	Sprites.push_back(gPH1);
	//}

	// Setup PHAnim Data 
	std::vector<AnimFrameData> gPHData;
	AnimFrameData Anim1; 
	Anim1.startFrame = 0; 
	Anim1.numFrames = 2; 
	gPHData.push_back(Anim1); 

	//Load PHAnim texture
	if (!gPHAnim->loadSpriteSheet("Assets/Art/PHSheet.png",128,102,gPHData))
	{
		printf("Failed to load texture image!\n");
		success = false;
	}
	else
	{
		//Set standard alpha blending
		gPHAnim->setBlendMode(SDL_BLENDMODE_BLEND);
		gPHAnim->setPosition((SCREEN_WIDTH - gPHAnim->getFrameWidth()) / 2, (SCREEN_HEIGHT - gPHAnim->getFrameHeight()) / 1.5);
		Sprites.push_back(gPHAnim);
	}

	//Open the font
	gFont = TTF_OpenFont("Assets/UI/Fonts/Enchanted Land.otf", 84);
	if (gFont == nullptr)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Load TextSprite 
		SDL_Color textColor = { 255, 255, 255 };
		if (!gTextTexture->load("Shattered Lands", textColor, gFont))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
		else
		{
			gTextTexture->setPosition((SCREEN_WIDTH - gTextTexture->getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture->getHeight()) / 3);
			Sprites.push_back(gTextTexture);
		}
	}

	// Sort Sprites on Render Priority 
	Sprites.sort(PComp<BaseSprite>);

	return success;

}

//TODO : Create a class, controller as parametter 
void loadController()
{
	gGameController = SDL_JoystickOpen(0);
	if (gGameController == nullptr)
	{
		printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Get controller haptic device
		gControllerHaptic = SDL_HapticOpenFromJoystick(gGameController);
		if (gControllerHaptic == nullptr)
		{
			printf("Warning: Controller does not support haptics! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get initialize rumble
			if (SDL_HapticRumbleInit(gControllerHaptic) < 0)
			{
				printf("Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError());
			}
		}

		printf("Controller Loaded \n");
	}
}
//TODO : Create a class, controller as parametter 
void closeController()
{
	if (gGameController != nullptr)
	{
		//Close game controller with haptics
		SDL_HapticClose(gControllerHaptic);
		SDL_JoystickClose(gGameController);
		gGameController = nullptr;
		gControllerHaptic = nullptr;

		printf("Controller Closed\n");
	}
}

void close()
{
	//Free surface/Image
	for (BaseSprite* it : Sprites)
	{
		it->free(); 
	}
	//gBackTexture->free(); 
	//gTextTexture->free();
	//gPH1->free(); 

	//gStartButton->free(); 

	//Free global font
	TTF_CloseFont(gFont);
	gFont = nullptr;

	//Destroy Window 
	SDL_DestroyRenderer(gRenderer);
	gWindow.free(); 
	gRenderer = nullptr;

	//Quit SDL subsystems 
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		printf("HEY");
		//Load Media 
		if (!loadMedia())
		{
			printf("Failed  to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Frame per second Timer 
			Timer fpsTimer; 
			int countedFrames = 0; 
			fpsTimer.start(); 

			// Keeps track of time between steps 
			Timer stepTimer; 

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					switch (e.type)
					{
					case SDL_QUIT : quit = true;
						break; 
					case SDL_JOYDEVICEADDED: loadController();
						break; 
					case SDL_JOYDEVICEREMOVED: closeController();
						break; 
					}
				}

				// Calculate Time step 
				float timeStep = stepTimer.getTicks() / 1000.f; 

				//Calculate and correct fps
				float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
				if (avgFPS > 2000000)
				{
					avgFPS = 0;
				}

				//
				AnimatedSprite* temp; 
				for (BaseSprite* it : Sprites)
				{
					temp = dynamic_cast<AnimatedSprite*>(it); 
					if (temp)
					{
						temp->updateAnim(timeStep); 
					}
					
				}

				//Restart step timer 
				stepTimer.start(); 

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);


				//Render texture to screen
				for (BaseSprite* it : Sprites)
				{
					printf(" %d ", it->getPriority()); 
					it->renderAtPosition();
				}


				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}
		//Free resources and close SDL
		close();

	return 0; 
}