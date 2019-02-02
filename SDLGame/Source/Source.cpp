#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "Sprite.h"
#include "Button.h"
#include "Timer.h" 
#include "SLEngineTypes.h"



//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;


//######### GLOBAL VARIABLES #########

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

//Globally used font
TTF_Font *gFont = NULL;

//Controller 
SDL_Joystick* gGameController = NULL;
SDL_Haptic* gControllerHaptic = NULL;
const int JOYSTICK_DEAD_ZONE = 8000;

//Textures
Sprite*gBackTexture = new Sprite(BACK);
Sprite*gTextTexture = new Sprite(UI);
Sprite*gStartButtonTexture = new Sprite(UI);
Sprite*gButtonTexture = new Sprite(UI);

//UI 
Button*gStartButton = new Button(gStartButtonTexture); 
Button*gButton = new Button(gButtonTexture);

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
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
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


		//Load BG texture
	if (!gBackTexture->loadFromFile("Assets/UI/MainMenuBackground.png", gRenderer))
	{
		printf("Failed to load texture image!\n");
		success = false;
	}
	else
	{
		//Set standard alpha blending
		gBackTexture->setBlendMode(SDL_BLENDMODE_BLEND);
	}

	//Load Start Button texture
	if (!gStartButtonTexture->loadFromFile("Assets/UI/StartButton.png", gRenderer))
	{
		printf("Failed to load texture image!\n");
		success = false;
	}
	else
	{
		//Set standard alpha blending
		gStartButtonTexture->setBlendMode(SDL_BLENDMODE_BLEND);
	}

	//Load Button texture
	if (!gButtonTexture->loadFromFile("Assets/UI/ButtonDefault.png", gRenderer))
	{
		printf("Failed to load texture image!\n");
		success = false;
	}
	else
	{
		//Set standard alpha blending
		gButtonTexture->setBlendMode(SDL_BLENDMODE_BLEND);
	}

	//Open the font
	gFont = TTF_OpenFont("Assets/UI/Fonts/Enchanted Land.otf", 84);
	if (gFont == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 255, 255, 255 };
		if (!gTextTexture->loadFromRenderedText("Shattered Lands", textColor, gRenderer, gFont))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	//Set Texture Position 
	gStartButton->getSprite()->setPosition((SCREEN_WIDTH - gStartButton->getSprite()->getWidth()) / 2, (SCREEN_HEIGHT - gStartButton->getSprite()->getHeight()) / 1.5);
	gButton->getSprite()->setPosition((SCREEN_WIDTH - gStartButton->getSprite()->getWidth()) / 1.5, (SCREEN_HEIGHT - gStartButton->getSprite()->getHeight()) / 1.5);

	//Set Button Texture Color 
	gButton->getSprite()->setColor(45, 45, 45); 

	return success;

}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

//TODO : Create a class, controller as parametter 
void loadController()
{
	gGameController = SDL_JoystickOpen(0);
	if (gGameController == NULL)
	{
		printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Get controller haptic device
		gControllerHaptic = SDL_HapticOpenFromJoystick(gGameController);
		if (gControllerHaptic == NULL)
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
	if (gGameController != NULL)
	{
		//Close game controller with haptics
		SDL_HapticClose(gControllerHaptic);
		SDL_JoystickClose(gGameController);
		gGameController = NULL;
		gControllerHaptic = NULL;

		printf("Controller Closed\n");
	}
}

void close()
{
	//Free surface/Image
	gBackTexture->free(); 
	gTextTexture->free();

	gStartButton->free(); 
	gButton->free(); 

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy Window 
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

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
					if (gStartButton->isPushed(&e))
					{
						if (SDL_HapticRumblePlay(gControllerHaptic, 0.75, 500) != 0)
						{
							printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
						}
					}
				}

				//Calculate and correct fps
				float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
				if (avgFPS > 2000000)
				{
					avgFPS = 0;
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);


				//Render texture to screen
				gBackTexture->render(0, 0, gRenderer);
				gTextTexture->render((SCREEN_WIDTH - gTextTexture->getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture->getHeight()) / 3 , gRenderer);
				gStartButton->getSprite()->renderAtPosition(gRenderer);
				gButton->getSprite()->renderAtPosition(gRenderer);


				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}
		//Free resources and close SDL
		close();

	return 0; 
}