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


void drawAnImage(Window& window) {
    // Colors
    SDL_Color skyColor = {135, 206, 235, 255};    // Light blue
    SDL_Color sunColor = {255, 223, 0, 255};      // Yellow
    SDL_Color hillColor = {34, 139, 34, 255};     // Green
    SDL_Color cloudColor = {255, 255, 255, 255};  // White

    // Clear background with sky
    window.drawFilledRect({0, 0, 800, 600}, skyColor);

    // Draw hills using custom #include <SDL2_gfxPrimitives.h>filled triangles
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


        window.endFrame();  

        SDL_Delay(16); // Around 60 FPS
    }
    return 0;
}