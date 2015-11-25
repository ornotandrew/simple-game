#define SDL_STBIMAGE_IMPLEMENTATION

#include <cstdlib>
#include <iostream>
#include <SDL.h>
#include "SDL_stbimage.h"
#include "render.h"

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

void initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(std::cout, "SDL_Init");
        exit(1);
    }

    window = SDL_CreateWindow("Simple Game", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        logSDLError(std::cout, "CreateRenderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    backgroundTex = loadTexture("resources/background.bmp", renderer);
    playerTex = loadTexture("resources/player.png", renderer);
}

void cleanupSDL()
{
    SDL_DestroyTexture(backgroundTex);
    SDL_DestroyTexture(playerTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = nullptr;

    // loads the image file at the given path into a RGB(A) SDL_Surface
    // Returns NULL on error, use SDL_GetError() to get more information.
    SDL_Surface* loadedImage  = STBIMG_Load(file.c_str());

	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
			cleanupSDL();
			SDL_Quit();
			exit(1);
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
        cleanupSDL();
        SDL_Quit();
        exit(1);
	}
	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w=0, int h=0)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	// Scale the image if needed
	if(w && h)
    {
        dst.w = w;
        dst.h = h;
    }
    else
    {
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    }

	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void tileBackground(SDL_Texture* background)
{
    int width, height;
    SDL_QueryTexture(background, NULL, NULL, &width, &height);

    for(int i=0; i<SCREEN_WIDTH; i+=width)
    {
        for(int j=0; j<SCREEN_HEIGHT; j+=height)
        {
            renderTexture(background, renderer, i, j);
        }
    }
}

void render()
{
    SDL_RenderClear(renderer);
    tileBackground(backgroundTex);
    renderTexture(playerTex, renderer, (SCREEN_WIDTH-250)/2, (SCREEN_HEIGHT-250)/2, 250, 250);
    SDL_RenderPresent(renderer);
}

