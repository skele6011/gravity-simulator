#include "Texture.hpp"
#include <iostream>

Texture::Texture(SDL_Renderer* renderer, const std::string& file) 
    : texture_(nullptr), width_(0), height_(0)
{

    // Load the image into a surface
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (!surface) {
        std::cerr << "Failed to load PNG: " << IMG_GetError() << std::endl;
        return;
    }

    // Create a texture from the surface
    texture_ = SDL_CreateTextureFromSurface(renderer, surface); // Convertts CPU-side surface into GPU-side texture
    if (!texture_) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    } else {
        // Simply get the width from surface struct and load them into our variables
        width_ = surface->w;
        height_ = surface->h;
    }

    SDL_FreeSurface(surface); // No use for it anymore, clear RAM.
}

Texture::~Texture() {
    if (texture_) {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }
}

void Texture::render(SDL_Renderer* renderer, int x, int y, int w, int h) const {
    if (!texture_) return; //  Nothing to rnder

    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = (w == -1) ? width_ : w;
    dstRect.h = (h == -1) ? height_ : h;

    SDL_RenderCopy(renderer, texture_, nullptr, &dstRect); // Draw texture onto the renderer. nullptr just means to use the entire texture, not just a part.
}

/*
Load PNG -> Surface (RAM) ->
Convert Surface -> Texture (VRAM) ->
Free surface (no longer need) ->
Draw using texture
*/