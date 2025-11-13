#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>

class SDLInitializer {
    private:
        bool _initialized;

    public:
        SDLInitializer(Uint32 flags) { // Flags such as SDL_INIT_VIDEO are in Uint32
            if (SDL_Init(flags) != 0) { // SDL_Init returns 0 if success
                std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
                _initialized = false;
            } else {
                _initialized = true;
            }
        }

        ~SDLInitializer() {
            if (_initialized) { // Only quit if was initialized, otherwise, not necessary.
                SDL_Quit();
            }
        }

        bool initialized() const { return _initialized; }
};

class Window {
    private:
        SDL_Window* _window = nullptr; 
        SDL_Renderer* _renderer = nullptr;

    public:
        Window(const char* title, int width, int height) {
            _window = SDL_CreateWindow(
                title, // Title
                SDL_WINDOWPOS_CENTERED, // x-pos
                SDL_WINDOWPOS_CENTERED, // y-pos
                width, height,          // width, height
                SDL_WINDOW_SHOWN
            );
            if (_window == nullptr) {
                std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            }

            _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
            if (_renderer == nullptr) {
                std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            }

        }

        void beginFrame() {
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255); // Black background
            SDL_RenderClear(_renderer); // Clear screen
        }

        void drawRectangle(SDL_Rect rect) {
            SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255); // Red
            SDL_RenderFillRect(_renderer, &rect);
        }

        void endFrame() {
            SDL_RenderPresent(_renderer);
        }

        ~Window() {
            if (_window) {
                SDL_DestroyWindow(_window);
                _window = nullptr;
            }

            if (_renderer) {
                SDL_DestroyRenderer(_renderer);
                _renderer = nullptr;
            }
        }

    SDL_Renderer* renderer() const { return _renderer; }

};

class EventManager {
    private: 
        SDL_Event _event; // _event will be our container struct that holds an event
    
    public: 
        EventManager() = default; // No reason to do constructor

        bool pollEvents() { // 
            while (SDL_PollEvent(&_event)) { // Pass through the address to write to it what event happened
                switch (_event.type) { // The event type is being checked
                    case SDL_QUIT: // If that event is is SDL_QUIT...
                        return false; // Return false
                    case SDL_KEYDOWN: // Check if a key is down
                        if (_event.key.keysym.sym == SDLK_SPACE) { // If that key is up...
                            std::cout << "Space was pressed!"; //  Do this
                        } break; // Break to stop executing the current case
                }
            } // Basically, else...
            return true; // Return true
        }
};

int main() {
    SDLInitializer sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if (!sdl.initialized()) { return 1; }

    Window window("Window", 640, 480);
    
    EventManager events;
    bool running = true;
    while (running) {
        running = events.pollEvents();

        window.beginFrame();

        window.drawRectangle({100, 100, 200, 150});
        window.drawRectangle({250, 300, 50, 50});

        window.endFrame();

        SDL_Delay(16); // Around 60 FPS
    }
    return 0;
}


// ----
// std::cout << "\n --- \n";

// std::cout << "Works!";

// std::cout << "\n --- \n\n";
// ----