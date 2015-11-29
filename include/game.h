#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL.h>

typedef uint8_t uint8;
typedef uint32_t uint32;

const int FRAMERATE = 60;
const int FRAMETIME = 1000/FRAMERATE;
const float TEXTURE_RATIO = 0.3;

class Game;

class GameObject
{
    public:
        SDL_Texture* texture;
        int x, y, z, w, h; // x, y are the center of the object
        float angle;
};

class Player: public GameObject
{
    public:
        float movespeed;
        Game* game;

        Player(Game* game, int x, int y);
        void shoot();
};

class Projectile: public GameObject
{
    public:
        float movespeed;
        GameObject* owner;

        Projectile(GameObject& owner);
};

class Game
{
    public:
        bool isRunning;
        uint8 score;
        Player* player;
        std::vector<GameObject*> projectiles;

        Game();
        ~Game();
        void update();
        void render();
};

#endif
