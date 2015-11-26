#include <vector>
#include <iostream>
#include <math.h>
#include <SDL.h>
#include "render.h"
#include "game.h"

// Textures
SDL_Texture *backgroundTex;
SDL_Texture *playerTex;

// Mouse coordinates
int xMouse, yMouse;

Game::Game()
{
    backgroundTex = loadTexture("resources/background.bmp");
    playerTex = loadTexture("resources/player.png");

    isRunning = true;
    score = 0;
    player = new Player((SCREEN_WIDTH - PLAYER_SIZE)/2,
                        (SCREEN_HEIGHT - PLAYER_SIZE)/2);
}

void Game::update()
{

    // Update the mouse position
    // and handle close event
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            isRunning = false;
        }
        else if(e.type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&xMouse, &yMouse);
        }
    }

    // =============
    // Game controls
    // =============

    // Movement
    const uint8* keystate = SDL_GetKeyboardState(NULL);
    if(keystate[SDL_SCANCODE_A])
    {
        player->x -= player->movespeed*FRAMETIME;
        if(player->x < 0)
            player->x = 0;
    }
    else if(keystate[SDL_SCANCODE_D])
    {
        player->x += player->movespeed*FRAMETIME;
        if(player->x + player->w > SCREEN_WIDTH)
            player->x = SCREEN_WIDTH - player->w;

    }
    if(keystate[SDL_SCANCODE_W])
    {
        player->y -= player->movespeed*FRAMETIME;
        if(player->y < 0)
            player->y = 0;
    }
    else if(keystate[SDL_SCANCODE_S])
    {
        player->y += player->movespeed*FRAMETIME;
        if(player->y + player->h > SCREEN_HEIGHT)
            player->y = SCREEN_HEIGHT - player->h;
    }

    // Rotation
    float x = (player->x + player->w/2) - xMouse;
    float y = (player->y + player->h/2) - yMouse;
    player->angle = atan2(y, x) * 180.0/M_PI - 90;
}

Game::~Game()
{
    delete player;
    SDL_DestroyTexture(backgroundTex);
    SDL_DestroyTexture(playerTex);
}

// Sort the objects by z value and draw them
void Game::render()
{
    using namespace std;
    clearRenderer();
    tileBackground(backgroundTex);

    std::vector<GameObject*> list = {player};
    // TODO: sort
    
    for(GameObject* obj: list)
    {
        renderTexture(obj->texture, obj->x, obj->y, obj->w, obj->h, obj->angle);
    }

    presentRenderer();
}

Player::Player(int _x, int _y, int _w, int _h)
{
   x = _x;
   y = _y;
   z = 99;
   w = _w;
   h = _h;
   texture = playerTex;
   movespeed = 0.5;
   angle = 0;
}

