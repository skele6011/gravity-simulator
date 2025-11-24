#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <random>
#include <algorithm>

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
    Player player;

    // --- Game State Below ---
    int playerRadius_;
    std::vector<Enemy> enemies;
    int enemyAmount_;
    Uint32 lastTime_;
    float deltaTime_;
    float survivalTime_;
    float shieldTime_;
    const Uint32 TARGET_FPS = 360;
    const Uint32 FRAME_DELAY = 1000 / TARGET_FPS;
    // --- ---- ---- ---

public:
    // --- Constructor ---
    Survival() 
    // Core Classes 
    : windowWidth_(1920), windowHeight_(1080),
      sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO, IMG_INIT_PNG),
      window("Window", this->windowWidth_, this->windowHeight_),
      events(false),
      player(30), // single Player instance with radius 30 to match collision usage
      playerRadius_(30),
      enemyAmount_(25),
      lastTime_(0),
      deltaTime_(0.0f),
      survivalTime_(0.0f),
      shieldTime_(0.0f)
    { 
    }
    // --- ---- ---- ---

    // --- Restart ---
    // Resets enemies, survival time, and timing. Only method that reinitializes game state.
    void restart() {
        // --- Player initialization ---
        // player is a member already constructed with radius playerRadius_
        this->survivalTime_ = 0.0f;
        this->shieldTime_ = 3.0f;
        // --- ---- ---- ---

        // --- Enemy initialization ---
        this->enemies.clear();
        this->enemies.reserve(this->enemyAmount_);

        // Create a random number generator
        std::random_device rd;  // seed
        std::mt19937 gen(rd()); // mersenne twister engine
        std::uniform_int_distribution<> xDist(0, this->windowWidth_);  // x between 0 and windowWidth
        std::uniform_int_distribution<> yDist(0, this->windowHeight_); // y between 0 and windowHeight
        std::uniform_int_distribution<> vDist(150, 300); // Velocity distribution 
        
        for (int i = 0; i < this->enemyAmount_; i++) {
            this->enemies.push_back(Enemy(xDist(gen), yDist(gen), 75, 75, vDist(gen), vDist(gen)));
        }
        // --- ---- ---- ---

        // --- Timing reset ---
        this->lastTime_ = SDL_GetTicks();
        // --- ---- ---- ---
    }
    // --- ---- ---- ---

    // --- Handling Start ---
    int startGame() {
        // --- Error Checking --- 
        if (!this->sdl.sdlInitialized()) { return -1; }
        if (!this->sdl.imgInitialized()) { return -1; }
        // --- ---- ---- ---
        
        // --- DeltaTime setup ---
        // lastTime_ will be set in restart()
        // --- ---- ---- ---

        // initialize game state
        this->restart();

        // run the main survival loop
        return this->survivalGame();
    }
    // --- ---- ---- ---

    // --- Main Game ---
    // Returns 0 on quit, 1 if a restart was triggered (handled internally via restart()).
    int survivalGame() {
        // --- Set up score text ---
        SDL_Color white { 255, 255, 255, 255 };
        TTF_Font* font = sdl.openFont("src/simple_font.ttf", 50);
        SDL_Rect scoreRect { this->windowWidth_ - 100, 35, 35, 35 };

        SDL_Color red { 117, 20, 0, 255 };
        SDL_Color green { 6, 112, 0, 255 };
        SDL_Rect shieldRect { this->windowWidth_ - 100, 85, 35, 35 };
        // --- ---- ---- ---


        bool running = true;
        while (running) {
            // --- Events Stuff ---
            running = this->events.pollEvents();
            if (!running) {
                return 0; // window closed / quit
            }
            // --- ---- ---- ---
            
            // --- DeltaTime Stuff ---
            Uint32 frameStart = SDL_GetTicks();
            this->deltaTime_ = (frameStart - this->lastTime_) / 1000.0f; // in seconds
            this->lastTime_ = frameStart;
            
            this->survivalTime_ += this->deltaTime_;
            this->shieldTime_ = std::max(0.0f, this->shieldTime_ - this->deltaTime_);
            // --- ---- ---- ---
            
            // --- Frames Stuff ---
            this->window.beginFrame();

            // Score visualizer
            std::string scoreText = std::to_string(static_cast<int>(this->survivalTime_)) + "s";
            Texture::handleFont(font, scoreText, white, this->window.renderer(), scoreRect);

            // --- Shield stuff ---
            std::string shieldText = std::to_string(static_cast<int>(this->shieldTime_)) + "s";

            bool shieldOn = true;
            if (static_cast<int>(this->shieldTime_) <= 0) {
                shieldOn = false;
            }

            if (shieldOn) {
                Texture::handleFont(font, shieldText, green, this->window.renderer(), shieldRect);
            } else {
                Texture::handleFont(font, shieldText, red, this->window.renderer(), shieldRect);
            }

            // --- ---- ---- ---

            // 1. Update player
            this->player.updatePosition(this->events.mouseX(), this->events.mouseY());

            // 2. Update enemies
            for (auto& enemy : this->enemies) {
                enemy.update(this->deltaTime_, this->windowWidth_, this->windowHeight_);
            }

            // 3. Check collisions
            if (!shieldOn) {
                for (auto& enemy : this->enemies) {
                    if (Collision::circleRectCollision(this->events.mouseX(), this->events.mouseY(), this->playerRadius_, enemy.rect())) {
                        // Enter loss flow: lost() will handle showing the screen and return 1 to restart, 0 to quit.
                        int lostResult = this->lost();
                        if (lostResult == 1) {
                            // restart the game state and continue the main loop
                            this->restart();
                            break; // break out of collision loop and continue running (game restarted)
                        } else {
                            // quit requested by the player from lost screen
                            return 0;
                        }
                    }
                }
            }

            // 4. Render everything
            this->player.render(this->window.renderer());
            for (auto& enemy : this->enemies) {
                enemy.render(this->window.renderer());
            }
            
            this->window.endFrame();  
            // --- ---- ---- ---
            
            // --- Frame Limiting for 360 FPS ---
            Uint32 frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < FRAME_DELAY) {
                SDL_Delay(FRAME_DELAY - frameTime);
            }
            // --- ---- ---- ---
        }   
        return 0;
    }
    // --- ---- ---- ---

    // --- Lost Screen ---
    int lost() {
        SDL_Color white { 255, 255, 255, 255 };
        SDL_Rect textRect { (this->windowWidth_ / 2) - 400, (this->windowHeight_ / 2) - 50, 800, 100 };
        TTF_Font* font = sdl.openFont("src/Branda-yolq.ttf", 50);

        bool inLost = true;
        while (inLost) {
            Uint32 frameStart = SDL_GetTicks();

            // --- Wait for user input ---
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    return 0;
                }
                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_r) {
                        // Restart requested
                        return 1;
                    } else if (e.key.keysym.sym == SDLK_ESCAPE) {
                        // Quit requested
                        return 0;
                    }
                }
                // Allow mouse button to restart as well (left-click)
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        return 1;
                    }
                }
            }
            // --- ---- ---- ---

            // Render lost screen
            this->window.beginFrame();

            // Draw lost message
            Texture::handleFont(font, "You Lost! Press R or Left-Click to Retry, ESC to Quit", white, this->window.renderer(), textRect);

            this->window.endFrame();

            // Frame limiting
            Uint32 frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < FRAME_DELAY) {
                SDL_Delay(FRAME_DELAY - frameTime);
            }
        }

        return 0;
    }
};
