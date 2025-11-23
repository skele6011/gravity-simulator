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
#include "utils/Enemy.hpp"
#include "utils/Player.hpp"



int main() {

    // --- Core Classes ---
    SDLInitializer sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO, IMG_INIT_PNG);
    Window window("Window", 1920, 1080);
    EventManager events(false);
    // --- ---- ---- ---

    // --- Error Checking --- 
    if (!sdl.sdlInitialized()) { return -1; }
    if (!sdl.imgInitialized()) { return -1; }
    // --- ---- ---- ---

    // --- DeltaTime setup ---
    Uint32 lastTime = SDL_GetTicks();
    float deltaTime;

    const int TARGET_FPS = 360;
    const int FRAME_DELAY = 1000 / TARGET_FPS; // should be ~8 ms
    // --- ---- ---- ---

    // --- Temporary ---
    Player player(30);
    Enemy enemy1(50, 50, 75, 75, 100, 100);
    // --- ---- ---- ---

    bool running = true;
    while (running) {
        // --- Events Stuff ---
        running = events.pollEvents();
        // std::cout << "Mouse: " << events.mouseX() << ", " << events.mouseY() << "\n";
        // --- ---- ---- ---

        // --- DeltaTime Stuff ---
        Uint32 frameStart = SDL_GetTicks();
        deltaTime = (frameStart - lastTime) / 1000.0f; // in seconds
        lastTime = frameStart;
        // --- ---- ---- ---

        // --- Frames Stuff ---
        window.beginFrame();
        
        enemy1.update(deltaTime, 1920, 1080);
        enemy1.render(window.renderer());
        
        player.updatePosition(events.mouseX(), events.mouseY());
        player.render(window.renderer());

        if (Collision::circleRectCollision(events.mouseX(), events.mouseY(), 30, enemy1.rect())) {
            std::cout << "COLLISION!";
        }

        window.endFrame();  
        // --- ---- ---- ---

        // --- Frame Limiting for 120 FPS ---

        
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
        // SDL_Delay(16);
        // --- ---- ---- ---
    }   
    return 0;
}