#include "render.h"
#include "game.h"

Game::Game()
{
    this->score = 0;
    this->player = new Player();
}

Player::Player(int x=0, int y=0)
{
   this->x = x;
   this->y = y;
   this->texture = playerTex;
}
