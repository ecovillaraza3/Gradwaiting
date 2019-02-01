#include "RetryCollege.h"



Manager collRetryManager;
AssetManager *collRetAsset = new AssetManager(&collRetryManager);
auto& collRetLabel(collRetryManager.addEntity());
Mix_Music *bgmRetryColl = nullptr;


SDL_Renderer *RetryCollege::renderer;
SDL_Event RetryCollege::event;
std::string RetryCollege::windowName;
ButtonObject *yesBtnCollRet, *noBtnCollRet;


RetryCollege::RetryCollege(){}

RetryCollege::~RetryCollege(){}


void RetryCollege::init(const char *title, int xpos, int ypos, int width, int height){

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(title,xpos,ypos,width,height,0);
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer)
            SDL_SetRenderDrawColor(renderer,0,0,0,255);

        isCollRetryWindowRunning = true;
    }else{
        isCollRetryWindowRunning = false;
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }

    bgmRetryColl = Mix_LoadMUS("dead.mp3");
    Mix_PlayMusic(bgmRetryColl,-1);

    if(bgmRetryColl == NULL){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }


    if(TTF_Init() == -1){
        std::cout<< "Error" << std::endl;
    }


    collRetAsset->AddFont("Flipps","Flipps.otf",20);
    SDL_Color color = {255,255,255,255};


    collRetLabel.addComponent<UILabel>(renderer,collRetAsset,70,0,"You lose!", "Flipps", color);
    collRetLabel.addComponent<UILabel>(renderer,collRetAsset,70,40,"Try again?", "Flipps", color);

    yesBtnCollRet = new ButtonObject(renderer,"assets/yes.png",100,320,100,100,true,6,100);
    noBtnCollRet = new ButtonObject(renderer,"assets/no.png",100,390,100,100,true,6,100);

}

void RetryCollege::handlerEvent(){

    collRetryManager.refresh();
    collRetryManager.update();
    yesBtnCollRet->update();
    noBtnCollRet->update();


    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        isCollRetryWindowRunning = false;
        break;
    }

    switch(event.type){
    case SDL_MOUSEBUTTONDOWN:
        if(MouseEvent::isMouseClicked(100,320,100,100,event) && !isClicked){
            isCollRetryWindowRunning = false;
            isClicked = true;
        }else if(MouseEvent::isMouseClicked(100,390,100,100,event) && !isClicked){
            Story::isFinishStory = true;
            windowName = "MainMenu";
            CollegeContinue::windowName = "MainMenu";
            isCollRetryWindowRunning = false;
            isClicked = true;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        isClicked = false;
        break;
    }

}


void RetryCollege::render(){
    SDL_RenderClear(renderer);
    yesBtnCollRet->render();
    noBtnCollRet->render();
    collRetLabel.draw();
    SDL_RenderPresent(renderer);
}


void RetryCollege::clean(){

    while(!AssetManager::textures.empty()){
        AssetManager::textures.erase(AssetManager::textures.begin());
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_FreeMusic(bgmRetryColl);
    bgmRetryColl = nullptr;
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

