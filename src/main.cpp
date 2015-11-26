#include <iostream>
#include <SDL.h>
#include "render.h"
#include "game.h"

int main()
{
    initSDL();
    Game game;
    while(game.isRunning)
    {
        game.update();
        game.render();
        SDL_Delay(FRAMETIME);
    }

    cleanupSDL();
    return 0;
}

