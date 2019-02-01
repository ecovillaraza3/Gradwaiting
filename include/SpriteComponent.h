#pragma once
#include "Components.h"
#include "SDL2/SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>
#include "AssetManager.h"



class SpriteComponent : public Component{

private:
        TransformComponent *transformComponent;
        SDL_Texture *texture;
        SDL_Rect src, dst;
        SDL_Renderer *drawRender;
        AssetManager *spriteAssets;

        bool animated = false;
        int frames = 0;
        int speed = 100;

public:


    int animIndex = 0;
    std::map<const char*, Animation> animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    // NO ANIMATION
    SpriteComponent(const char *path, SDL_Renderer *renderer,AssetManager *assets){
        drawRender = renderer;
        spriteAssets = assets;
        setTexture(path,renderer);


        while(!animations.empty()){
            animations.erase(animations.begin());
        }

    }


    SpriteComponent() = default;

    // PROJECTILES ANIMATION
    SpriteComponent(std::string id, bool isAnimated, int nFrame, int nSpeed, SDL_Renderer *renderer,AssetManager *assets){
        animated = isAnimated;
        Animation projAnim = Animation(0,nFrame,nSpeed);
        animations.emplace("ProjAnim", projAnim);
        Play("ProjAnim");

        drawRender = renderer;
        spriteAssets = assets;
        setTex(id);
    }

    // CHARACTER ANIMATION
    SpriteComponent(std::string id, bool isAnimated, SDL_Renderer *renderer,AssetManager *assets){
        animated = isAnimated;

        Animation idle = Animation(0,5,100);
        Animation jump = Animation(1,7,100);
        Animation slide = Animation(2,3,100);

        animations.emplace("Jump", jump);
        animations.emplace("Idle", idle);
        animations.emplace("Slide", slide);

        Play("Idle");

        drawRender = renderer;
        spriteAssets = assets;
        setTex(id);
    }

    ~SpriteComponent(){
    }

    void setTex(std::string id){
        texture = spriteAssets->GetTexture(id);
    }

    void setTexture(const char* path, SDL_Renderer *renderer){
        texture = TextureManager::LoadTexture(path,renderer);
    }


    void init() override{

        transformComponent = &entity->getComponent<TransformComponent>();

        src.x = src.y = 0;
        src.w = transformComponent->width;
        src.h = transformComponent->height;



    }

    void update() override{

        if(animated){
            src.x = src.w * static_cast<int> ((SDL_GetTicks()/speed) % frames );
        }

        src.y = animIndex * transformComponent->height;

        dst.x = static_cast<int> (transformComponent->position.x);
        dst.y = static_cast<int> (transformComponent->position.y);
        dst.w = transformComponent->width * transformComponent->scale;
        dst.h = transformComponent->height * transformComponent->scale;
    }

    void draw() override{
        TextureManager::Draw(drawRender,texture, src, dst,spriteFlip);
    }

    void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};
