#ifndef GAME_H
#define GAME_H

#include <SDL.h>

typedef uint8_t uint8 ;

const int FRAMERATE = 60;
const int FRAMETIME = 1000/60;
const int PLAYER_SIZE = 75;

class GameObject
{
    public:
        SDL_Texture* texture = 0;
        int x, y, z, w, h;
};

class Player: public GameObject
{
    public:
        float movespeed;
        Player(int x=0, int y=0, int w=PLAYER_SIZE, int h=PLAYER_SIZE);
};

class Game
{
    public:
        bool isRunning;
        uint8 score;
        Player* player;
        Game();
        ~Game();
        void update();
        void render();
};

#endif
