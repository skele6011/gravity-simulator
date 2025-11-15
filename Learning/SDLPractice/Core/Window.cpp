#include "Window.hpp"

Window::Window(const char* title, int width, int height) {
    window_ = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );

    if (!window_) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    }
}

void Window::beginFrame() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}

void Window::drawRedRectangle(SDL_Rect rect) {
    SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer_, &rect);
}

void Window::endFrame() {
    SDL_RenderPresent(renderer_);
}

Window::~Window() {
    if (renderer_) SDL_DestroyRenderer(renderer_);
    if (window_) SDL_DestroyWindow(window_);
}
