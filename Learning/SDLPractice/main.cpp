#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Core/Window.hpp"
#include "Core/Initializer.hpp"
#include "Core/EventManager.hpp"
#include "Core/Texture.hpp"

#include "Utils/Collision.hpp"
#include "Utils/Enemy.hpp"
#include "Utils/Player.hpp"

#include "Levels/Survival.cpp"

int main() {
    Survival survival;
    survival.startGame();
}

// int main() {
//     SDLInitializer sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO, IMG_INIT_PNG);
//     if (!sdl.sdlInitialized()) { return -1; }
//     if (!sdl.imgInitialized()) { return -1; }
//     if (!sdl.ttfInitialized()) { return -1; }

//     int windowWidth = 1920;
//     int windowHeight = 1080;
//     Window window("Window", windowWidth, windowHeight);
//     EventManager events(true);

//     Uint32 lastTime = SDL_GetTicks();
//     float deltaTime = 0.0f;

//     const int TARGET_FPS = 120;
//     const int FRAME_DELAY = 1000 / TARGET_FPS;

//     bool running = true;
//     while (running) {
//         running = events.pollEvents();
//         Uint32 frameStart = SDL_GetTicks();
//         deltaTime = (frameStart - lastTime) / 1000.0f;
//         lastTime = frameStart;
//         // ----------------------------------------------
//         window.beginFrame();
//         TTF_Font* font = sdl.openFont("src/Branda-yolq.ttf", 24);

//         SDL_Color white = {255, 255, 255, 255}; // RGBA
//         SDL_Rect textRect = {100, 100, 200, 100};
//         Texture::handleFont(font, "Hello There!", white, window.renderer(), textRect);

        
//         window.endFrame();
//         // --------------------------------------------
//         Uint32 frameTime = SDL_GetTicks() - frameStart;
//         if (frameStart < FRAME_DELAY) {
//             SDL_Delay(FRAME_DELAY - frameTime);
//         }
//     }
//     return 0;
// }