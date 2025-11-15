#include "Initializer.hpp"

SDLInitializer::SDLInitializer(Uint32 flags) { // Flags such as SDL_INIT_VIDEO are in Uint32
    if (SDL_Init(flags) != 0) { // SDL_Init returns 0 if success
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        initialized_ = false;
    } else {
        initialized_ = true;
    }
}

SDLInitializer::~SDLInitializer() {
    if (initialized_) { // Only quit if was initialized, otherwise, not necessary.
        SDL_Quit();
    }
}