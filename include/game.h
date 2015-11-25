#ifndef GAME
#define GAME value

#include "render.h"
#include "game.h"

class Game
{
    public:
        unsigned int score;
        Player* player;

        Game();
};


class GameObject
{
    public:
        SDL_Texture* texture = 0;
        unsigned int x;
        unsigned int y;
};

class Player: public GameObject
{
    public:
        Player(int x, int y);
};

#endif
