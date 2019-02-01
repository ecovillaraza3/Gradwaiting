#pragma once
#include "ECS.h"
#include "SDL2/SDL.h"
#include "Vector2D.h"
#include "Game.h"
#include "TextureManager.h"

class TileComponent: public Component{

public:

    SDL_Texture* texture;
    SDL_Rect srcRect, dstRect;
    SDL_Renderer *drawRend;

    TileComponent() = default;

    ~TileComponent(){
        SDL_DestroyTexture(texture);
    }



    TileComponent(SDL_Renderer *renderer, int srcX, int srcY, int xpos, int ypos,int tSize, int tScale, std::string id,AssetManager *assets){
       texture = assets->GetTexture(id);

       srcRect.x = srcX;
       srcRect.y = srcY;
       srcRect.w = srcRect.h = tSize;

       dstRect.x = xpos;
       dstRect.y = ypos;
       dstRect.h = tSize * tScale;
       dstRect.w = tSize * tScale * 50;
       drawRend = renderer;

    }

    void draw() override{
        TextureManager::Draw(drawRend, texture, srcRect, dstRect, SDL_FLIP_NONE);
    }


};
