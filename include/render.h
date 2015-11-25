#ifndef RENDER
#define RENDER

#include <iostream>
#include <SDL.h>

SDL_Window *window;
SDL_Renderer *renderer;

SDL_Texture *backgroundTex;
SDL_Texture *playerTex;

void initSDL();
void cleanupSDL();
void render();

void logSDLError(std::ostream &os, const std::string &msg);
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void tileBackground(SDL_Texture* background);

#endif
