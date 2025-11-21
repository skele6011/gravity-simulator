#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>

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

        std::cout << "Mouse: " << events.mouseX() << ", " << events.mouseY() << "\n";

        window.beginFrame();

        SDL_Color green {0, 69, 11, 255};
        // window.drawTriangle(50, 50, 100, 200, 200, 100, green);
        // window.drawFilledTriangle(50, 50, 100, 200, 200, 100, green);
        window.drawCircle(320, 240, 200, green);

        filledCircleRGBA(window.renderer(), 200, 200, 50, 255, 0, 0, 255);

        window.endFrame();  

        SDL_Delay(16); // Around 60 FPS
    }

    return 0;
}