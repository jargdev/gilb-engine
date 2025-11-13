#ifndef Scene_hpp
#define Scene_hpp

#include "SDL2/SDL.h"
#include "Game.hpp"

class Game;

class Scene
{
public:
    Scene() = default;
    virtual ~Scene() {}

    virtual void init(SDL_Renderer *renderer, Game *game) = 0;
    virtual void handleEvents(SDL_Event &event) = 0;
    virtual void update() = 0;
    virtual void render(SDL_Renderer *renderer) = 0;
    virtual void clean() = 0;

protected:
    Game *game = nullptr;
};
#endif /* Scene_hpp */