#include <iostream>
#include <string>
#include <SDL.h>
#include "main.h"
#include "render.h"

int main()
{
    initSDL();
    render();
    SDL_Delay(1000);
    cleanupSDL();
    return 0;
}

void processInput()
{

}
