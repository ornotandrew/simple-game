#ifndef RENDER_H
#define RENDER_H

#include <iostream>
#include <SDL.h>

const int SCREEN_WIDTH  = 1024;
const int SCREEN_HEIGHT = 768;

void initSDL();
void cleanupSDL();
void clearRenderer();
void presentRenderer();

void logSDLError(std::ostream &os, const std::string &msg);
SDL_Texture* loadTexture(const std::string &file);
void renderTexture(SDL_Texture *tex, int x, int y, int w=0, int h=0);
void tileBackground(SDL_Texture* background);

#endif
