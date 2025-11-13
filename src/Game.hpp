#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <iostream>
#include "Scene.hpp"
#include <memory>

class Game
{
public:
    Game();
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();

    void changeScene(std::unique_ptr<Scene> newScene);

private:
    std::unique_ptr<Scene> currentScene;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif /* Game_hpp */