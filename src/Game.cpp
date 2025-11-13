#include "Game.hpp"
#include "scenes/RedRectTest.hpp"

Game::Game()
{
}
Game::~Game()
{
}

/// @brief sdl gets initialized here.
void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // we initialize the window here if sdl didnt fail to init
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialised!..." << "\n";

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << "Window Initialised!..." << "\n";
        }

        // create renderer
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer Initialised!..." << "\n";
        }
        // start mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
        {
            std::cout << "Audio Initialised!..." << "\n";
        }

        isRunning = true;
        this->changeScene(std::make_unique<RedRectTest>());
    }
    else
    {
        isRunning = false;
    }
}

/// @brief handle events inputted by user
void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    // ✕ on window
    case SDL_QUIT:
        isRunning = false;
        break;
    }

    if (currentScene)
    {
        currentScene->handleEvents(event);
    }
}

void Game::update()
{
    if (currentScene)
    {
        currentScene->update();
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    if (currentScene)
    {
        currentScene->render(renderer);
    }
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    if (currentScene)
    {
        currentScene->clean();
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned up..." << "\n";
}

bool Game::running()
{
    return isRunning;
}

void Game::changeScene(std::unique_ptr<Scene> newScene)
{
    if (currentScene)
    {
        currentScene->clean();
    }

    currentScene = std::move(newScene);
    if (currentScene)
    {
        currentScene->init(renderer, this);
    }
}