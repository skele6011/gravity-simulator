#pragma once 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Texture {
private:
    SDL_Texture* texture_;
    int width_;
    int height_;

public:
    Texture(SDL_Renderer* renderer, const std::string& file);
    ~Texture();

    void render(SDL_Renderer* renderer, int x, int y, int w = -1, int h = -1) const;

    int width() const { return width_; } 
    int height() const { return height_; } 

};