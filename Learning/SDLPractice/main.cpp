#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>

#include "Core/Window.hpp"
#include "Core/Initializer.hpp"
#include "Core/EventManager.hpp"

int main() {
    SDLInitializer sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if (!sdl.initialized()) { return 1; }

    Window window("Window", 640, 480);

    EventManager events(true);

    bool running = true;
    while (running) {
        running = events.pollEvents();

        // std::cout << "Mouse: " << events.mouseX() << ", " << events.mouseY() << "\n";

        window.beginFrame();

        

        window.endFrame();

        SDL_Delay(16); // Around 60 FPS
    }

    return 0;
}