#pragma once
#include "Game.h"
#include "MouseEvent.h"

class RetryWindow
{
    public:
        RetryWindow();
         ~RetryWindow();

         void init(const char* title, int xpos, int ypos, int width, int height);
         void handlerEvent();
         void render();
         void clean();
         bool running(){return isRetryWindowRunning;}
         static SDL_Renderer *renderer;
         static SDL_Event event;
         static std::string windowName;

    private:
        bool isRetryWindowRunning, isClicked = false;
        SDL_Window *window;

};

