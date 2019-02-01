#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include "Components.h"
#include "AssetManager.h"
#include "UILabel.h"
#include "ButtonObject.h"
#include "MouseEvent.h"
#include "CollegeContinue.h"

class RetryCollege
{
    public:
        RetryCollege();
         ~RetryCollege();
         void init(const char* title, int xpos, int ypos, int width, int height);
         void handlerEvent();
         void render();
         void clean();

         bool running(){return isCollRetryWindowRunning;}
         static SDL_Renderer *renderer;
         static SDL_Event event;
         static std::string windowName;

    private:
        bool isCollRetryWindowRunning, isClicked = false;
        SDL_Window *window;
};
