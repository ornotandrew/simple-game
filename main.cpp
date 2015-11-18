#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "main.h"
#include "render.h"

int main()
{

    initSDL();
    render();
    SDL_Delay(5000);
    cleanupSDL();
    return 0;
}


