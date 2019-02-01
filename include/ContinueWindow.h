#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include "Story.h"

class ContinueWindow
{
    public:
        ContinueWindow();
        ~ContinueWindow();
         void init(const char* title, int xpos, int ypos, int width, int height);
         void handlerEvent();
         void render();
         void clean();
         bool running(){return isContinueWindowRunning;}
         static SDL_Renderer *renderer;
         static SDL_Event event;
         static std::string windowName;

    private:
        bool isContinueWindowRunning, isClicked = false;
        SDL_Window *window;
};
