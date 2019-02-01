#ifndef MAINMENU_H
#define MAINMENU_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include "TextureManager.h"
#include "MouseEvent.h"
#include <string>
#include "SDL2/SDL_ttf.h"
#include <time.h>
#include <stdio.h>
#include "Story.h"
#include "Game.h"
#include "SDL2/SDL_mixer.h"

class MainMenu
{
    public:
        MainMenu();
         ~MainMenu();

         void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
         void handlerEvent();
         void update();
         void render();
         void clean();

         static SDL_Renderer *renderer;
         static SDL_Event event;

         bool running(){return isMainMenuRunning;}
         static std::string windowName;
         bool mainMenuLoop(){return isMenu;}

    private:
        bool isMenu = true;
        bool isMainMenuRunning;
        bool endlessButton = false;
        bool isClicked = false;
        bool isExit;
        int cnt = 0;

        SDL_Window *window;

};

#endif // MAINMENU_H
