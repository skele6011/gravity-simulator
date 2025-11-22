#include "Initializer.hpp"

SDLInitializer::SDLInitializer(Uint32 flags, int imgFlags)  { // Flags such as SDL_INIT_VIDEO are in Uint32
    if (SDL_Init(flags) != 0) { // SDL_Init returns 0 if success
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        sdlInitialized_ = false;
        return;
    } 
    sdlInitialized_ = true;

    if (!(IMG_Init(imgFlags)) & imgFlags) {
        std::cerr << "IMG_Init error: " << IMG_GetError() << std::endl;
        return;
    }
    imgInitialized_ = true;
}

SDLInitializer::~SDLInitializer() {
    if (sdlInitialized_) { // Only quit if was initialized, otherwise, not necessary.
        SDL_Quit();
    }
    if (imgInitialized_) {
        IMG_Quit();
    }
}