#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class TextureManager{

    public:
        TextureManager();
        ~TextureManager();
        static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer *renderer);
        static void Draw( SDL_Renderer *renderer,SDL_Texture *tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip);


};
