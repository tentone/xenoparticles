#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

//Function declaration
void initialize(SDL_Renderer **ren, SDL_Window **win);
void update();
void render();
void dispose(SDL_Renderer **ren, SDL_Window **win, SDL_GameController **controller);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w = -1, int h = -1);
SDL_Texture *renderText(const string &msg, const string &fontPath, SDL_Color color, int fontSize, SDL_Renderer *ren);

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int CENTER_WIDTH = 5;

const float MAX_ANGLE = 3.142 / 5.0; // 72 degrees

const float BALL_MAXSPEED = 8.0f;
const float BALL_ACCELERATE = 1.05f;
const float BALL_INIT_SPEED = 4.0f;
const int BALL_WIDTH = 10;
const int BALL_HEIGHT = 10;

//Main method
int main(int argc, char* argv[])
{
	SDL_Log("Starting SDL Application...");

	SDL_Event e;

	//Renderer and window
	SDL_Renderer *ren = nullptr;
	SDL_Window *win = nullptr;

	//Gamecontroller and haptic
	SDL_GameController *controller = nullptr;
	SDL_Haptic *haptic = nullptr;

	initialize(&ren,&win);

	int board_width;
	int board_height;

	SDL_Texture *squareTex = IMG_LoadTexture(ren, "../img/pong_board.png");
	SDL_QueryTexture(squareTex, NULL, NULL, &board_width, &board_height);

	SDL_Color white = {255, 255, 255};

	SDL_Surface *fpsCounter;

	SDL_Rect b_rect;
	b_rect.w = BALL_HEIGHT;
	b_rect.h = BALL_HEIGHT;

	uint previous = SDL_GetTicks();
	bool quit = false;
	int frames = 0;
	float fps;
	char buffer[512];

	const Uint8 *keystates = SDL_GetKeyboardState(NULL);

	while(!quit)
	{
		// FPS Calculation
		++frames;
		uint time = SDL_GetTicks();
		float delta = (time - previous);

		if(delta > 100)
		{
			fps = round(frames / (delta / 1000.0));
			frames = 0;
			previous = time;
		}

		//Events input
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
			if(e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE:
						quit = true;
						break;
				}
			}
		}

		//Render stuff into screen
		SDL_RenderClear(ren);

		//SDL_RenderCopy(ren, squareTex, NULL, &p1.pos);
		//SDL_RenderCopy(ren, squareTex, NULL, &p2.pos);

		// Draw the center line
		renderTexture(squareTex, ren, SCREEN_WIDTH/2 - CENTER_WIDTH/2, 0, CENTER_WIDTH, SCREEN_HEIGHT);

		// Draw the Ball
		renderTexture(squareTex, ren, 2, 2, BALL_WIDTH, BALL_HEIGHT);

		//Render text
		sprintf(buffer, "%d", 1);
		SDL_Texture *p1score = renderText(buffer, "../fonts/sample.ttf", white, 40, ren);
		sprintf(buffer, "%d", 2);
		SDL_Texture *p2score = renderText(buffer, "../fonts/sample.ttf", white, 40, ren);

		int width;
		SDL_QueryTexture(p1score, NULL, NULL, &width, NULL);

		renderTexture(p1score, ren, SCREEN_WIDTH/2 - width - 10, 10);
		renderTexture(p2score, ren, SCREEN_WIDTH/2 + 10, 10);

		SDL_DestroyTexture(p1score);
		SDL_DestroyTexture(p2score);

		// Extremely ineffecient way of displaying text
		sprintf(buffer, "%.0f", fps);
		SDL_Texture *fpsCounter = renderText(buffer, "../fonts/sample.ttf", white, 20, ren);
		renderTexture(fpsCounter, ren, SCREEN_WIDTH - 20, 0);
		SDL_DestroyTexture(fpsCounter);

		SDL_RenderPresent(ren);
	}

	if(haptic)
	{
		SDL_HapticClose(haptic);
	}

	SDL_DestroyTexture(squareTex);
	dispose(&ren, &win, &controller);

	exit(0);
}

void initialize(SDL_Renderer **ren, SDL_Window **win)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		SDL_Log("Failed to initialize SDL");
		exit(-1);
	}

	*win = SDL_CreateWindow("Constellations", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if(*win == nullptr)
	{
		SDL_Log("Failed to create SDL Window");
		exit(-1);
	}

	*ren = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(*ren == nullptr)
	{
		SDL_Log("Failed to create SDL Renderer");
		exit(-1);
	}

	const int flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if(IMG_Init(flags) !=flags)
	{
		SDL_Log("Failed to load the Image loading extensions");
		exit(-1);
	}

	if(TTF_Init() != 0)
	{
		SDL_Log("Failed to load TTF extension");
		exit(-1);
	}
}

void update()
{

}

void render()
{

}

void dispose(SDL_Renderer **ren, SDL_Window **win, SDL_GameController **controller)
{
	SDL_DestroyRenderer(*ren);
	SDL_DestroyWindow(*win);
	SDL_GameControllerClose(*controller);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture *renderText(const string &msg, const string &fontPath, SDL_Color color, int fontSize, SDL_Renderer *ren)
{
	TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if(font == nullptr)
	{
		SDL_Log("Unable to open font");
		exit(-1);

		return nullptr;
	}

	SDL_Surface *surface = TTF_RenderText_Blended(font, msg.c_str(), color);
	if(surface == nullptr)
	{
		TTF_CloseFont(font);

		SDL_Log("Unable to render text to a surface");
		exit(-1);

		return nullptr;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surface);
	if(tex == nullptr)
	{
		SDL_Log("Unable to render surface to texture");
		exit(-1);
	}

	SDL_FreeSurface(surface);
	TTF_CloseFont(font);

	return tex;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	// If no width and height are specified, use the texture's actual width and height
	if(w == -1 || h == -1)
	{
		SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
	}

	SDL_RenderCopy(ren, tex, NULL, &dest);
}
