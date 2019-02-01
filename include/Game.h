#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "RetryWindow.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "SDL2/SDL_ttf.h"
#include <fstream>
#include "SDL2/SDL_mixer.h"

class AssetManager;
class ColliderComponent;// NEW

class Game
{
    public:
        Game();
         ~Game();
         void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

         void handlerEvent();
         void update();
         bool running(){return isRunning;}
         void render();
         void clean();

         static SDL_Renderer *renderer;
         static SDL_Event event;
         static bool isRunning;
         static bool isDeleteAnimation;
         static std::string windowName;

    private:
        int cnt = 0;
        int score = 0, currentScore = 0, highscore = 0;
        SDL_Window *window;
        AssetManager *assets;

};


