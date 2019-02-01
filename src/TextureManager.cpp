#include "TextureManager.h"
#include "AssetManager.h"

TextureManager::TextureManager(){}

TextureManager::~TextureManager(){}

SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer *renderer){
    return IMG_LoadTexture(renderer,texture);
}



void TextureManager::Draw(SDL_Renderer *renderer, SDL_Texture *tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip){
    SDL_RenderCopyEx(renderer, tex,&src,&dst, NULL, NULL, flip);
}

