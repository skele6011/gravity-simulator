#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>

class SDLInitializer {
private:
    bool sdlInitialized_;
    bool imgInitialized_;

public:
    SDLInitializer(Uint32 flags, int imgFlags);

    ~SDLInitializer();

    bool sdlInitialized() const { return sdlInitialized_; }
    bool imgInitialized() const { return imgInitialized_; }
};

