#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL.h"
#include <zlib.h>
#include <vector>
#include <iostream>

class MusicLoader
{
public:
    MusicLoader() : music(nullptr) {}
    ~MusicLoader() { freeMusic(); }

    void freeMusic()
    {
        if (music)
        {
            Mix_HaltMusic();
            Mix_FreeMusic(music);
            music = nullptr;
        }
    }

    bool loadFromMemory(const unsigned char *data, size_t length)
    {
        freeMusic();
        SDL_RWops *rw = SDL_RWFromMem((void *)data, static_cast<int>(length));
        if (!rw)
            return false;
        music = Mix_LoadMUS_RW(rw, 1);
        if (!music)
            return false;
        return true;
    }

    void play(int loops = -1)
    {
        if (music)
            Mix_PlayMusic(music, loops);
    }
    void stop() { Mix_HaltMusic(); }
    Mix_Music *getMusic() { return music; }

private:
    Mix_Music *music;
};