#include "Game.hpp"

Game *game = nullptr;

int main()
{
    game = new Game();

    game->init("Gilb Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 500, false);

    while (game->running())
    {
        game->handleEvents();
        game->update();
        game->render();
        // cap at 60 fps
        SDL_Delay(16);
    }

    game->clean();

    return 0;
}