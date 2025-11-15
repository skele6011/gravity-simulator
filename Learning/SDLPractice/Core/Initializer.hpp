#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class SDLInitializer {
private:
    bool initialized_;

public:
    SDLInitializer(Uint32 flags);

    ~SDLInitializer();

    bool initialized() const { return initialized_; }
};