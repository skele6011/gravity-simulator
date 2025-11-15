#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class Window {
private:
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;

public:
    Window(const char* title, int width, int height);
    ~Window();

    void beginFrame();
    void drawRedRectangle(SDL_Rect rect);
    void endFrame();

    SDL_Renderer* renderer() const { return renderer_; }
};
