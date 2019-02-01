#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include <stdio.h>
#include "Collision.h"
#include "AssetManager.h"
#include "Story.h"
#include "HighschoolWindow.h"
#include "CollegeWindow.h"
#include <string>

class KeyboardController : public Component
{
    public:
        KeyboardController(std::string id){
            windowId = id;
        }

        ~KeyboardController(){
            Mix_FreeChunk(jump);
        }
        TransformComponent *transformComponent;
        SpriteComponent *sprite;
        int playerXpos, playerYpos;
        int objectXpos, objectYpos;

        void init() override{
            transformComponent = &entity->getComponent<TransformComponent>();
            sprite = &entity->getComponent<SpriteComponent>();
        }

        void update() override{
            if(windowId == "endless"){
                endlessKeyboard();
            }else if(windowId == "elementary"){
                elementaryKeyboard();
            }else if(windowId == "highschool"){
                highSchoolKeyboard();
            }else if(windowId == "college"){
                collegeSchoolKeyboard();
            }
        }

        void endlessKeyboard(){

            cnt++;
            if(cnt > 20){
                transformComponent->velocity.y = 10;
            }else{
                transformComponent->velocity.y = -10;
                sprite->Play("Jump");
            }

            if(cnt == 40){
                keyUpDone = false;
                keyIsAlreadyPressed = false;
            }
            if(Game::event.type == SDL_KEYDOWN && !keyUpDone){
                if(!keyIsAlreadyPressed){
                    switch(Game::event.key.keysym.sym){
                    case SDLK_w:
                        cnt = 0;
                        Collision::yD = 50;
                        keyUpDone = true;
                        Mix_PlayChannel(-1,jump,0);
                        break;
                    case SDLK_SPACE:
                        cnt = 0;
                        keyUpDone = true;
                    case SDLK_s:
                        sprite->Play("Slide");
                        Collision::yD = 80;
                        break;
                    case SDLK_ESCAPE:
                        while(!AssetManager::textures.empty()){
                            AssetManager::textures.erase(AssetManager::textures.begin());
                        }
                        Game::isRunning = false;
                        break;
                    }
                }
            }

            if(Game::event.type == SDL_KEYUP){
                switch(Game::event.key.keysym.sym){
                case SDLK_w:
                    sprite->Play("Idle");
                    if(keyUpDone)
                        keyIsAlreadyPressed = true;
                    break;
                case SDLK_SPACE:
                    sprite->Play("Idle");
                    if(keyUpDone)
                        keyIsAlreadyPressed = true;
                    break;
                case SDLK_s:
                    sprite->Play("Idle");
                    Collision::yD = 35;
                    break;
                }
            }

        }

        void elementaryKeyboard(){

            cnt++;
            if(cnt > 20){
                transformComponent->velocity.y = 10;
            }else{
                transformComponent->velocity.y = -10;
                sprite->Play("Jump");
            }

            if(cnt == 40){
                keyUpDone = false;
                keyIsAlreadyPressed = false;
            }
            if(Story::event.type == SDL_KEYDOWN && !keyUpDone){
                if(!keyIsAlreadyPressed){
                    switch(Story::event.key.keysym.sym){
                    case SDLK_w:
                        cnt = 0;
                        Collision::yD = 50;
                        keyUpDone = true;
                        Mix_PlayChannel(-1,jump,0);
                        break;
                    case SDLK_SPACE:
                        cnt = 0;
                        keyUpDone = true;
                    case SDLK_s:
                        sprite->Play("Slide");
                        Collision::yD = 80;
                        break;
                    case SDLK_ESCAPE:
                        while(!AssetManager::textures.empty()){
                            AssetManager::textures.erase(AssetManager::textures.begin());
                        }
                        Game::isRunning = false;
                        break;
                    }
                }
            }

            if(Story::event.type == SDL_KEYUP){
                switch(Story::event.key.keysym.sym){
                case SDLK_w:
                    sprite->Play("Idle");
                    if(keyUpDone)
                        keyIsAlreadyPressed = true;
                    break;
                case SDLK_SPACE:
                    sprite->Play("Idle");
                    if(keyUpDone)
                        keyIsAlreadyPressed = true;
                    break;
                case SDLK_s:
                    sprite->Play("Idle");
                    Collision::yD = 35;
                    break;
                }
            }
        }

        void highSchoolKeyboard(){

            cnt++;
            if(cnt > 20){
                transformComponent->velocity.y = 10;
            }else{
                transformComponent->velocity.y = -10;
                sprite->Play("Jump");
            }

            if(cnt == 40){
                keyUpDone = false;
                keyIsAlreadyPressed = false;
            }
            if(HighschoolWindow::event.type == SDL_KEYDOWN && !keyUpDone){
                if(!keyIsAlreadyPressed){
                    switch(HighschoolWindow::event.key.keysym.sym){
                    case SDLK_w:
                        cnt = 0;
                        Collision::yD = 50;
                        keyUpDone = true;
                        Mix_PlayChannel(-1,jump,0);
                        break;
                    case SDLK_SPACE:
                        cnt = 0;
                        keyUpDone = true;
                    case SDLK_s:
                        sprite->Play("Slide");
                        Collision::yD = 80;
                        break;
                    case SDLK_ESCAPE:
                        while(!AssetManager::textures.empty()){
                            AssetManager::textures.erase(AssetManager::textures.begin());
                        }
                        Game::isRunning = false;
                        break;
                    }
                }
            }

            if(HighschoolWindow::event.type == SDL_KEYUP){
                switch(HighschoolWindow::event.key.keysym.sym){
                case SDLK_w:
                    sprite->Play("Idle");
                    if(keyUpDone)
                        keyIsAlreadyPressed = true;
                    break;
                case SDLK_SPACE:
                    sprite->Play("Idle");
                    if(keyUpDone)
                        keyIsAlreadyPressed = true;
                    break;
                case SDLK_s:
                    sprite->Play("Idle");
                    Collision::yD = 35;
                    break;
                }
            }
        }

        void collegeSchoolKeyboard(){

            cnt++;
            if(cnt > 20){
                transformComponent->velocity.y = 10;
            }else{
                transformComponent->velocity.y = -10;
                sprite->Play("Jump");
            }

            if(cnt == 40){
                keyUpDone = false;
                keyIsAlreadyPressed = false;
            }
            if(CollegeWindow::event.type == SDL_KEYDOWN && !keyUpDone){
                if(!keyIsAlreadyPressed){
                    switch(CollegeWindow::event.key.keysym.sym){
                    case SDLK_w:
                        cnt = 0;
                        Collision::yD = 50;
                        keyUpDone = true;
                        Mix_PlayChannel(-1,jump,0);
                        break;
                    case SDLK_SPACE:
                        cnt = 0;
                        keyUpDone = true;
                    case SDLK_s:
                        sprite->Play("Slide");
                        Collision::yD = 80;
                        break;
                    case SDLK_ESCAPE:
                        while(!AssetManager::textures.empty()){
                            AssetManager::textures.erase(AssetManager::textures.begin());
                        }
                        Game::isRunning = false;
                        break;
                    }
                }
            }

            if(CollegeWindow::event.type == SDL_KEYUP){
                switch(CollegeWindow::event.key.keysym.sym){
                case SDLK_w:
                    sprite->Play("Idle");
                    if(keyUpDone)
                        keyIsAlreadyPressed = true;
                    break;
                case SDLK_SPACE:
                    sprite->Play("Idle");
                    if(keyUpDone)
                        keyIsAlreadyPressed = true;
                    break;
                case SDLK_s:
                    sprite->Play("Idle");
                    Collision::yD = 35;
                    break;
                }
            }
        }

    private:
        int cnt = 21;
        bool keyUpDone = true;
        bool keyIsAlreadyPressed = false;
        std::string windowId;
        Mix_Chunk *jump = Mix_LoadWAV("jump.wav");
};

