#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>

#include "Core/Window.hpp"
#include "Core/Initializer.hpp"
#include "Core/EventManager.hpp"
#include "Core/Texture.hpp"

#include "utils/Collision.hpp"

void createCircleAndRect(Window& window, EventManager& events) {
// Draw rectangle
    int x1 = 750, y1 = 750;
    int x2 = 850, y2 = 850;
    boxRGBA(window.renderer(), x1, y1, x2, y2, 255, 255, 255, 100);

    // Create SDL_Rect to use for collision
    SDL_Rect rect;
    rect.x = x1;
    rect.y = y1;
    rect.w = x2 - x1; // 100
    rect.h = y2 - y1; // 100

    // Draw circle at mouse position
    int cx = events.mouseX();
    int cy = events.mouseY();
    int radius = 50;
    filledCircleRGBA(window.renderer(), cx, cy, radius, 156, 41, 28, 85);

    // Check collision
    bool collision = Collision::circleRectCollision(cx, cy, radius, rect);
    if (collision) {
        std::cout << "Collision detected!" << std::endl;
    }
}

int main() {
    SDLInitializer sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO, IMG_INIT_PNG);
    Window window("Window", 1250, 1000);
    EventManager events(false);

    if (!sdl.sdlInitialized()) { return -1; }
    if (!sdl.imgInitialized()) { return -1; }


    bool running = true;
    while (running) {
        running = events.pollEvents();

        std::cout << "Mouse: " << events.mouseX() << ", " << events.mouseY() << "\n";

        window.beginFrame();

        createCircleAndRect(window, events);

        window.endFrame();  

        SDL_Delay(16); // Around 60 FPS
    }
    return 0;
}