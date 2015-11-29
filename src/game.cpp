#include <vector>
#include <iostream>
#include <math.h>
#include <SDL.h>
#include "render.h"
#include "game.h"

// Textures
SDL_Texture *backgroundTex;
SDL_Texture *playerTex;
SDL_Texture *projectileTex;

// Mouse state
int xMouse, yMouse;
uint32 mouseState;

Game::Game()
{
    backgroundTex = loadTexture("resources/background.jpg");
    playerTex = loadTexture("resources/player.png");
    projectileTex = loadTexture("resources/projectiles.png");

    isRunning = true;
    score = 0;
    player = new Player(this, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
}

Game::~Game()
{
    delete player;
    projectiles.clear();

    SDL_DestroyTexture(backgroundTex);
    SDL_DestroyTexture(playerTex);
    SDL_DestroyTexture(projectileTex);
}

void Game::update()
{

    // ============
    // Housekeeping
    // ============

    // Close event
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            isRunning = false;
    }

    // Kill anything that is hit by a projectile

    // ==============
    // Mouse controls
    // ==============

    mouseState = SDL_GetMouseState(&xMouse, &yMouse);

    if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
        player->shoot();

    // =================
    // Keyboard controls
    // =================

    // Movement
    const uint8* keystate = SDL_GetKeyboardState(NULL);
    if(keystate[SDL_SCANCODE_A])
    {
        player->x -= player->movespeed*FRAMETIME;
        if(player->x - player->w/2 < 0)
            player->x = player->w/2;
    }
    else if(keystate[SDL_SCANCODE_D])
    {
        player->x += player->movespeed*FRAMETIME;
        if(player->x + player->w/2 > SCREEN_WIDTH)
            player->x = SCREEN_WIDTH - player->w/2;

    }
    if(keystate[SDL_SCANCODE_W])
    {
        player->y -= player->movespeed*FRAMETIME;
        if(player->y - player->h/2 < 0)
            player->y = player->h/2;
    }
    else if(keystate[SDL_SCANCODE_S])
    {
        player->y += player->movespeed*FRAMETIME;
        if(player->y + player->h/2 > SCREEN_HEIGHT)
            player->y = SCREEN_HEIGHT - player->h/2;
    }

    // Rotation
    float x = (player->x + player->w/2) - xMouse;
    float y = (player->y + player->h/2) - yMouse;
    player->angle = atan2(y, x) * 180.0/M_PI - 90;
}

void Game::render()
{
    // Sort the objects by z value and draw them
    using namespace std;
    clearRenderer();
    tileBackground(backgroundTex);

    std::vector<GameObject*> list = {player};
    list.insert(list.end(), projectiles.begin(), projectiles.end());

    // TODO: sort
    
    for(GameObject* obj: list)
    {
        renderGameObject(*obj);
    }

    presentRenderer();
}

Player::Player(Game* game, int x, int y)
{
    this->game = game;
    texture = playerTex;
    SDL_QueryTexture(playerTex, NULL, NULL, &w, &h);

    this->x = x;
    this->y = y;
    this->z = 99;
    std::cout << w << " " << h << std::endl;
    w *= TEXTURE_RATIO;
    h *= TEXTURE_RATIO;
    angle = 0;
    movespeed = 0.5;
}

void Player::shoot()
{
   game->projectiles.push_back(new Projectile(*this));
}

Projectile::Projectile(GameObject& owner)
{
    texture = projectileTex;
    x = owner.x;
    y = owner.y;
    z = 50;
    SDL_QueryTexture(projectileTex, NULL, NULL, &w, &h);
    w *= TEXTURE_RATIO;
    h *= TEXTURE_RATIO;
    angle = owner.angle;
    movespeed = 1;
    this->owner = &owner;
}

