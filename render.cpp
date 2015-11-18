#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>
#include "render.h"

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window *window;
SDL_Renderer *renderer;

SDL_Texture *background;

void initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(std::cout, "SDL_Init");
        exit(1);
    }

    window = SDL_CreateWindow("Simple Game", 100, 100, SCREEN_WIDTH,
        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        logSDLError(std::cout, "CreateRenderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    background = loadTexture("background.bmp", renderer);
    if (background == nullptr)
    {
        cleanupSDL();
        SDL_Quit();
        exit(1);
    }
}

void cleanupSDL()
{
    SDL_DestroyTexture(background);
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
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
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
    tileBackground(background);
    SDL_RenderPresent(renderer);
}

