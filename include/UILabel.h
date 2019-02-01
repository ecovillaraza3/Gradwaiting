#pragma once
#include "ECS.h"
#include "AssetManager.h"
#include "TextureManager.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class UILabel : public Component
{
public:

    UILabel(SDL_Renderer *renderer,AssetManager *assets, int xpos, int ypos, std::string text, std::string font, SDL_Colour &colour):
        labelText(text), labelFont(font), textColour(colour)
    {
        position.x = xpos;
        position.y = ypos;

        drawRen = renderer;
        assetManager = assets;
        setLabelText(labelText, labelFont);
    }

    ~UILabel(){
        SDL_DestroyTexture(labelTexture);
    }

    void setLabelText(std::string text, std::string font){
        SDL_Surface *surf = TTF_RenderText_Blended(assetManager->GetFont(font), text.c_str(), textColour);
        labelTexture = SDL_CreateTextureFromSurface(drawRen, surf);
        SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);

    }

    void draw() override{
        SDL_RenderCopy(drawRen, labelTexture, nullptr, &position);
    }

private:
    SDL_Rect position;
    std::string labelText;
    std::string labelFont;
    SDL_Color textColour;
    SDL_Texture *labelTexture;
    SDL_Renderer *drawRen;
    AssetManager *assetManager;

};
