#pragma once
#include "MainMenu.h"
#include "Animation.h"
#include <map>

class ButtonObject
{
private:


        SDL_Texture *texture;
        SDL_Rect srcRect, dstRect;
        SDL_Renderer *thisRenderer;

        bool animated = false;
        int frames = 1;
        int speed = 100;

        int x = 0;
        int y = 0;
        int w = 300;
        int h = 300;

public:
        int animIndex = 0;


        std::map<const char*, Animation> animations;

        ButtonObject(SDL_Renderer *renderer, const char* path, int xpos, int ypos, int width, int height, int isAnimated, int nframe, int nSpeed){
           Animation idle = Animation(0,nframe,nSpeed);
           animations.emplace("Animer",idle);

            x = xpos;
            y = ypos;
            w = width;
            h = height;

            srcRect.x = srcRect.y = 0;
            srcRect.w = 32;
            srcRect.h = 32;

            animated = isAnimated;
            frames = nframe;
            speed = nSpeed;

            Play("Animer");
            thisRenderer = renderer;
            setTexture(path);
        }

        ButtonObject(SDL_Renderer *renderer, const char* path, int xpos, int ypos, int width, int height, int isAnimated, int nframe, int nSpeed, int sw, int sh){
           Animation idle = Animation(0,nframe,nSpeed);
           animations.emplace("Animer",idle);

            x = xpos;
            y = ypos;
            w = width;
            h = height;

            srcRect.x = srcRect.y = 0;
            srcRect.w = sw;
            srcRect.h = sh;

            animated = isAnimated;
            frames = nframe;
            speed = nSpeed;

            Play("Animer");
            thisRenderer = renderer;
            setTexture(path);
        }

        ~ButtonObject(){
            SDL_DestroyTexture(texture);
        }

        void setTexture(const char* path){
            texture = TextureManager::LoadTexture(path,thisRenderer);
        }

        void update(){

            if(animated){
                srcRect.x = srcRect.w * static_cast<int> ((SDL_GetTicks()/speed) % frames );
            }

            dstRect.x = x;
            dstRect.y = y;
            dstRect.w = w;
            dstRect.h = h;

        }
        void render(){
            TextureManager::Draw(thisRenderer,texture,srcRect,dstRect,SDL_FLIP_NONE);
        }

        void Play(const char* animName){
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
        }


};


