#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include "CollegeWindow.h"


class CollegeContinue
{
    public:
        CollegeContinue();
         ~CollegeContinue();
         void init(const char* title, int xpos, int ypos, int width, int height);
         void handlerEvent();
         void render();
         void clean();
         bool running(){return isContinueCollegeRunning;}
         static SDL_Renderer *renderer;
         static SDL_Event event;
         static std::string windowName;

    private:
        bool isContinueCollegeRunning, isClicked = false;
        SDL_Window *window;
};
