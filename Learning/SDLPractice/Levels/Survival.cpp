#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <random>

#include "../Core/Window.hpp"
#include "../Core/Initializer.hpp"
#include "../Core/EventManager.hpp"
#include "../Core/Texture.hpp"

#include "../Utils/Collision.hpp"
#include "../Utils/Enemy.hpp"
#include "../Utils/Player.hpp"


class Survival {
private:
    int windowWidth_;
    int windowHeight_;
    SDLInitializer sdl;
    Window window;
    EventManager events;
public:
    // --- Constructor ---
    Survival() 
    // Core Classes 
    : windowWidth_(1920), windowHeight_(1080),
    sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO, IMG_INIT_PNG),
    window("Window", this->windowWidth_, this->windowHeight_),
    events(false)
    { 
    }
    // --- ---- ---- ---

    int startGame() {
                        
        // --- Error Checking --- 
        if (!this->sdl.sdlInitialized()) { return -1; }
        if (!this->sdl.imgInitialized()) { return -1; }
        // --- ---- ---- ---
        
        // --- DeltaTime setup ---
        Uint32 lastTime = SDL_GetTicks();
        float deltaTime;
        
        const int TARGET_FPS = 360;
        const int FRAME_DELAY = 1000 / TARGET_FPS; // should be ~8 ms
        // --- ---- ---- ---
        
        // --- Player initialization ---
        int playerRadius = 30;
        Player player(playerRadius);

        float survivalTime = 0.0f;
        // --- ---- ---- ---

        // --- Enemy initialization ---
        std::vector<Enemy> enemies;
        int enemyAmount = 25;
        enemies.reserve(enemyAmount);

        // Create a random number generator
        std::random_device rd;  // seed
        std::mt19937 gen(rd()); // mersenne twister engine
        std::uniform_int_distribution<> xDist(0, this->windowWidth_);  // x between 0 and windowWidth
        std::uniform_int_distribution<> yDist(0, this->windowHeight_); // y between 0 and windowHeight
        std::uniform_int_distribution<> vDist(150, 300); // Velocity distrubtion 
        
        for (int i = 0; i < enemyAmount; i++) {
            enemies.push_back(Enemy(xDist(gen), yDist(gen), 75, 75, vDist(gen), vDist(gen)));
        }
        // --- ---- ---- ---
        
        // --- Temporary ---
        
        // --- ---- ---- ---

        bool running = true;
        while (running) {
            // --- Events Stuff ---
            running = this->events.pollEvents();
            // std::cout << "Mouse: " << events.mouseX() << ", " << events.mouseY() << "\n";
            // --- ---- ---- ---
            
            // --- DeltaTime Stuff ---
            Uint32 frameStart = SDL_GetTicks();
            deltaTime = (frameStart - lastTime) / 1000.0f; // in seconds
            lastTime = frameStart;
            survivalTime += deltaTime;
            // --- ---- ---- ---
            
            // --- Frames Stuff ---
            this->window.beginFrame();

            // 1. Update player
            player.updatePosition(this->events.mouseX(), this->events.mouseY());
            // 2. Update enemies
            for (auto& enemy : enemies) {
                enemy.update(deltaTime, this->windowWidth_, this->windowHeight_);
            }
            // 3. Check collisions
            for (auto& enemy : enemies) {
                if (Collision::circleRectCollision(this->events.mouseX(), this->events.mouseY(), playerRadius, enemy.rect())) {
                    this->lost();
                }
            }
            // 4. Render everything
            player.render(this->window.renderer());
            for (auto& enemy : enemies) {
                enemy.render(this->window.renderer());
            }
            
            this->window.endFrame();  
            // --- ---- ---- ---
            
            // --- Frame Limiting for 120 FPS ---
            Uint32 frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < FRAME_DELAY) {
                SDL_Delay(FRAME_DELAY - frameTime);
            }
            // --- ---- ---- ---
        }   
        return 0;
    }

    void lost() {
        SDL_Color white { 255, 255, 255, 255 };
        SDL_Rect textRect { (this->windowWidth_ / 2) - 250, this->windowHeight_ / 2, 500, 250 };
        TTF_Font* font = sdl.openFont("src/Branda-yolq.ttf", 50);
        Texture::handleFont(font, "You Lost! Try Again?", white, this->window.renderer(), textRect);
    }
};
