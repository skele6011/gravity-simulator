#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "Core/Window.hpp"
#include "Core/Initializer.hpp"
#include "Core/EventManager.hpp"


void drawAnImage(Window& window) {
    // Colors
    SDL_Color skyColor = {135, 206, 235, 255};    // Light blue
    SDL_Color sunColor = {255, 223, 0, 255};      // Yellow
    SDL_Color hillColor = {34, 139, 34, 255};     // Green
    SDL_Color cloudColor = {255, 255, 255, 255};  // White

    // Clear background with sky
    window.drawFilledRect({0, 0, 800, 600}, skyColor);

    // Draw hills using custom filled triangles
    window.drawFilledTriangle(0, 400, 200, 250, 400, 400, hillColor);
    window.drawFilledTriangle(300, 400, 500, 250, 700, 400, hillColor);
    window.drawFilledTriangle(600, 400, 750, 300, 800, 400, hillColor);

    // Draw sun using SDL2_gfx filled circle
    filledCircleRGBA(window.renderer(), 650, 100, 50, sunColor.r, sunColor.g, sunColor.b, sunColor.a);

    // Draw sun rays using custom lines
    for(int angle = 0; angle < 360; angle += 30) {
        float rad = angle * 3.14159 / 180.0;
        int x1 = 650 + int(50 * cos(rad));
        int y1 = 100 + int(50 * sin(rad));
        int x2 = 650 + int(80 * cos(rad));
        int y2 = 100 + int(80 * sin(rad));
        window.drawLine(x1, y1, x2, y2, sunColor);
    }

    // Draw clouds using SDL2_gfx circles
    filledCircleRGBA(window.renderer(), 200, 100, 30, cloudColor.r, cloudColor.g, cloudColor.b, cloudColor.a);
    filledCircleRGBA(window.renderer(), 230, 100, 25, cloudColor.r, cloudColor.g, cloudColor.b, cloudColor.a);
    filledCircleRGBA(window.renderer(), 215, 80, 20, cloudColor.r, cloudColor.g, cloudColor.b, cloudColor.a);

    // Add some points (birds) using custom drawPoint
    window.drawPoint(100, 150, {0, 0, 0, 255});
    window.drawPoint(110, 160, {0, 0, 0, 255});
    window.drawPoint(120, 150, {0, 0, 0, 255});

}


int main() {
    SDLInitializer sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if (!sdl.initialized()) { return 1; }

    Window window("Window", 800, 600);

    EventManager events(true);

    bool running = true;
    while (running) {
        running = events.pollEvents();

        std::cout << "Mouse: " << events.mouseX() << ", " << events.mouseY() << "\n";

        window.beginFrame();

        SDL_Color green {0, 69, 11, 255};

        drawAnImage(window);

        window.endFrame();  

        SDL_Delay(16); // Around 60 FPS
    }

    return 0;
}