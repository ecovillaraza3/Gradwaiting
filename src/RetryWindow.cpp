#include "RetryWindow.h"
#include "Components.h"
#include "AssetManager.h"
#include "ButtonObject.h"
#include "fstream"
#include "Story.h"

RetryWindow::RetryWindow(){}

RetryWindow::~RetryWindow(){}

SDL_Renderer *RetryWindow::renderer;

SDL_Event RetryWindow::event;
Manager manageer;
ButtonObject *yesBtn, *noBtn;
Mix_Music *bgmRetryEnd = nullptr;

AssetManager *assets = new AssetManager(&manageer);

auto& labelRetry(manageer.addEntity());
std::string RetryWindow::windowName;

void RetryWindow::init(const char *title, int xpos, int ypos, int width, int height){

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(title,xpos,ypos,width,height,0);
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer)
            SDL_SetRenderDrawColor(renderer,0,0,0,255);

        isRetryWindowRunning = true;
    }else{
        isRetryWindowRunning = false;
    }


    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }

    bgmRetryEnd = Mix_LoadMUS("dead.mp3");
    Mix_PlayMusic(bgmRetryEnd,-1);

    if(bgmRetryEnd == NULL){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }


    if(TTF_Init() == -1){
        std::cout<< "Error" << std::endl;
    }



    SDL_Color color = {255,255,255,255};
    SDL_Color red = {200,0,0,255};
    assets->AddFont("Flipps","Flipps.otf",20);
    std::string currentScore = "0", highScore = "0";
    std::ifstream getCurrentScore, getHighScore;
    getCurrentScore.open("currentscore.txt");
    getHighScore.open("highscore.txt");
    getCurrentScore >> currentScore;
    getHighScore >> highScore;
    getCurrentScore.close();
    getHighScore.close();

    labelRetry.addComponent<UILabel>(renderer,assets,70,0,"Best Score", "Flipps", color);
    labelRetry.addComponent<UILabel>(renderer,assets,140,40,highScore, "Flipps", red);
    labelRetry.addComponent<UILabel>(renderer,assets,70,80,"Your Score", "Flipps", color);
    labelRetry.addComponent<UILabel>(renderer,assets,140,120,currentScore, "Flipps", red);
    labelRetry.addComponent<UILabel>(renderer,assets,50,200,"You're dead! ", "Flipps", color);
    labelRetry.addComponent<UILabel>(renderer,assets,100,270,"Re-try?", "Flipps", color);
    yesBtn = new ButtonObject(renderer,"assets/yes.png",100,320,100,100,true,6,100);
    noBtn = new ButtonObject(renderer,"assets/no.png",100,390,100,100,true,6,100);

}

void RetryWindow::handlerEvent(){
    manageer.refresh();
    manageer.update();
    yesBtn->update();
    noBtn->update();

    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_MOUSEBUTTONDOWN:
        if(MouseEvent::isMouseClicked(100,320,80,80,event) && !isClicked){
            Story::isFinishStory = true;
            isRetryWindowRunning = false;
            Game::isRunning = false;
            printf("Yes");
            windowName = "endless";
            isClicked = true;
        }else if(MouseEvent::isMouseClicked(100,390,80,80,event) && !isClicked){
            printf("Poooop\n");
            Story::isFinishStory = true;
            isRetryWindowRunning = false;
            Game::isRunning = false;
            windowName = "MainMenu";
            Game::windowName = "MainMenu";
            isClicked = true;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        isClicked = false;
        break;
    }

}

void RetryWindow::render(){
    SDL_RenderClear(renderer);
    yesBtn->render();
    noBtn->render();
    labelRetry.draw();
    SDL_RenderPresent(renderer);
}

void RetryWindow::clean(){

    while(!AssetManager::textures.empty()){
        AssetManager::textures.erase(AssetManager::textures.begin());
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    Mix_FreeMusic(bgmRetryEnd);
    bgmRetryEnd = nullptr;
    Mix_CloseAudio();
    Mix_Quit();

    SDL_Quit();
}


