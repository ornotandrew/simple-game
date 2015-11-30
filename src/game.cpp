#include <vector>
#include <iostream>
#include <algorithm>
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

    // Handle close event
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            isRunning = false;
    }

    // ===========
    // Projectiles
    // ===========

    // Move projectiles
    for(uint8 i=0; i<projectiles.size(); i++)
    {
            projectiles[i]->move();
            int maxSide = projectiles[i]->w;
            if(projectiles[i]->h > maxSide)
                maxSide = projectiles[i]->h;

            if(projectiles[i]->x < -2*maxSide ||
               projectiles[i]->x > SCREEN_WIDTH + 2*maxSide ||
               projectiles[i]->y < -2*maxSide ||
               projectiles[i]->y > SCREEN_HEIGHT + 2*2*maxSide)
            {
                delete projectiles[i];
                projectiles.erase(projectiles.begin()+i);
                i--;
            }
    }

    // Kill anything that is hit by a projectile

    // ==============
    // Mouse controls
    // ==============

    // Decrement player's shoot cooldown
    player->timeToShoot -= FRAMETIME;

    mouseState = SDL_GetMouseState(&xMouse, &yMouse);

    if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) && player->timeToShoot <= 0)
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
    player->angle = atan2(y, x) - M_PI/2;
}

bool heightSort(const GameObject* obj1, const GameObject* obj2)
{
    return obj1->z < obj2->z;
}

void Game::render()
{
    // Sort the objects by z value and draw them
    using namespace std;
    clearRenderer();
    tileBackground(backgroundTex);

    std::vector<GameObject*> list = {player};
    list.insert(list.end(), projectiles.begin(), projectiles.end());

    std::sort(list.begin(), list.end(), heightSort);
    
    for(GameObject* obj: list)
        renderGameObject(*obj);

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
    w *= TEXTURE_RATIO;
    h *= TEXTURE_RATIO;
    angle = 0;
    movespeed = 0.5;
    weaponCooldown = 200;
    timeToShoot = 0;
}

void Player::shoot()
{
   game->projectiles.push_back(new Projectile(*this));
   timeToShoot = weaponCooldown;
}

Projectile::Projectile(GameObject& owner)
{
    texture = projectileTex;
    z = 50;
    SDL_QueryTexture(projectileTex, NULL, NULL, &w, &h);
    w *= TEXTURE_RATIO;
    h *= TEXTURE_RATIO;
    angle = owner.angle;
    movespeed = 1;
    this->owner = &owner;

    // Make the bullets appear slightly away from the center
    int min = owner.w;
    if(owner.h < min)
        min = owner.h;

    min *= 0.6; // but not too far
    x = owner.x + min * cos(angle - M_PI/2);
    y = owner.y + min * sin(angle - M_PI/2);
}

void Projectile::move()
{
    x += FRAMETIME * movespeed * cos(angle - M_PI/2);
    y += FRAMETIME * movespeed * sin(angle - M_PI/2);
}

