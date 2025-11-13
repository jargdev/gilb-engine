#include "../Scene.hpp"
#include "../assets/test_beat.mp3.h"
#include "../MusicLoader.hpp"
Mix_Music *test_Music = NULL;

MusicLoader loader;

class RedRectTest : public Scene
{
public:
    void init(SDL_Renderer *renderer, Game *game) override
    {
        this->game = game;
        if (loader.loadFromMemory(test_beat_mp3, test_beat_mp3_len))
        {
            loader.play(-1);
        }
        lastFlashTime = SDL_GetTicks();
    }
    void handleEvents(SDL_Event &event) override
    {
    }
    void update() override
    {
        Uint32 currentTime = SDL_GetTicks();
        if (!flashing && currentTime - lastFlashTime >= flashInterval)
        {
            flashing = true;
            lastFlashTime = currentTime;
        }
        else if (flashing && currentTime - lastFlashTime >= flashDuration)
        {
            flashing = false;
        }
    }
    void render(SDL_Renderer *renderer) override
    {
        SDL_Rect rect = {200, 150, 400, 300};
        if (flashing)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderClear(renderer);
        }
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        if (!flashing)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
    }
    void clean() override
    {
        loader.freeMusic();
    }

private:
    Uint32 lastFlashTime = 0;
    bool flashing = false;
    const double flashInterval = 1416.66666667 / 4;
    const Uint32 flashDuration = 100;
};
