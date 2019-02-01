#include "MainMenu.h"
#include "ButtonObject.h"
#include "time.h"

MainMenu::MainMenu(){
}

MainMenu::~MainMenu(){}



SDL_Renderer *MainMenu::renderer;
SDL_Event MainMenu::event;
ButtonObject *endless, *story, *bgButton;
Mix_Music *bgn;

std::string MainMenu::windowName;



void MainMenu::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(title,xpos,ypos,width,height,flags);
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer,100,255,255,255);
            printf("Window Created");
        }
        isMainMenuRunning = true;
        endlessButton = false;
        isClicked = false;
        isExit = true;
    }else{
        isMainMenuRunning = false;
    }


    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }

    bgn = Mix_LoadMUS("bgmenu.mp3");
    Mix_PlayMusic(bgn,-1);



    if(bgn == NULL){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }

    endless = new ButtonObject(renderer,"assets/start_button.png",300,250,200,200,true,5,100);
    story = new ButtonObject(renderer,"assets/exit_button.png",300,350,200,200,true,7,100);
    bgButton = new ButtonObject(renderer,"assets/bgtest.png",0,0,800,500,true,5,80,200,125);

}

void MainMenu::handlerEvent(){
    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exit(42);
        break;
    case SDL_MOUSEBUTTONDOWN:
            if(MouseEvent::isMouseClicked(300,250,200,150,event) && !isClicked){
                    if(!endlessButton)
                        endless = new ButtonObject(renderer,"assets/start_button.png",300,250,190,190,true,5,100);
                    cnt = 0;
                    if(endlessButton){
                        Game::windowName = "endless";
                        Story::isFinishStory = true;
                        isMainMenuRunning = false;
                    }
                    endlessButton = true;
                    isClicked = true;
                    isExit = false;

            }else if(MouseEvent::isMouseClicked(300,350,200,140,event) && !isClicked){
                printf("hey\n");
                if(isExit){
                    exit(42);
                }else{
                    Story::windowName = "story";
                    isMainMenuRunning = false;
                }
                isClicked = true;

            }

        break;
    case SDL_MOUSEBUTTONUP:
            if(cnt == 9){
                endless = new ButtonObject(renderer,"assets/start_button.png",300,250,200,200,true,5,100);
            }
            isClicked = false;
        break;
    }


    if(cnt == 10 && endlessButton){
        endless = new ButtonObject(renderer,"assets/endless_btn.png",300,250,200,200,true,4,100);
        story = new ButtonObject(renderer,"assets/story_btn.png",300,350,200,200,true,4,100);
    }

}

void MainMenu::update(){
    cnt++;
    bgButton->update();
    endless->update();
    story->update();

}

void MainMenu::render(){
    SDL_RenderClear(renderer);
    bgButton->render();
    endless->render();
    story->render();
    SDL_RenderPresent(renderer);
}

void MainMenu::clean(){



    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_FreeMusic(bgn);
    bgn = nullptr;
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}
