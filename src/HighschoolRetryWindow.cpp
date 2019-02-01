#include "HighschoolRetryWindow.h"


Manager highRetryManager;
AssetManager *highRetAsset = new AssetManager(&highRetryManager);
auto& highRetLabel(highRetryManager.addEntity());
Mix_Music *bgmRetryHigh = nullptr;


SDL_Renderer *HighschoolRetryWindow::renderer;
SDL_Event HighschoolRetryWindow::event;
std::string HighschoolRetryWindow::windowName;
ButtonObject *yesBtnHighRet, *noBtnHighRet;

HighschoolRetryWindow::HighschoolRetryWindow(){}

HighschoolRetryWindow::~HighschoolRetryWindow(){}



void HighschoolRetryWindow::init(const char *title, int xpos, int ypos, int width, int height){

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(title,xpos,ypos,width,height,0);
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer)
            SDL_SetRenderDrawColor(renderer,0,0,0,255);

        isHighRetryWindowRunning = true;
    }else{
        isHighRetryWindowRunning = false;
    }


    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }

    bgmRetryHigh = Mix_LoadMUS("dead.mp3");
    Mix_PlayMusic(bgmRetryHigh,-1);

    if(bgmRetryHigh == NULL){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }


    if(TTF_Init() == -1){
        std::cout<< "Error" << std::endl;
    }

    highRetAsset->AddFont("Flipps","Flipps.otf",20);
    SDL_Color color = {255,255,255,255};

    highRetLabel.addComponent<UILabel>(renderer,highRetAsset,70,0,"You lose!", "Flipps", color);
    highRetLabel.addComponent<UILabel>(renderer,highRetAsset,70,40,"Try again?", "Flipps", color);

    yesBtnHighRet = new ButtonObject(renderer,"assets/yes.png",100,320,100,100,true,6,100);
    noBtnHighRet = new ButtonObject(renderer,"assets/no.png",100,390,100,100,true,6,100);


}

void HighschoolRetryWindow::handlerEvent(){
    highRetryManager.refresh();
    highRetryManager.update();
    yesBtnHighRet->update();
    noBtnHighRet->update();


    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        isHighRetryWindowRunning = false;
        break;
    }

    switch(event.type){
    case SDL_MOUSEBUTTONDOWN:
        if(MouseEvent::isMouseClicked(100,320,100,100,event) && !isClicked){
            isHighRetryWindowRunning = false;
            isClicked = true;
        }else if(MouseEvent::isMouseClicked(100,390,100,100,event) && !isClicked){
            Story::isFinishStory = true;
            windowName = "MainMenu";
            ContinueHighSchool::windowName = "MainMenu";
            isHighRetryWindowRunning = false;
            isClicked = true;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        isClicked = false;
        break;
    }


}

void HighschoolRetryWindow::render(){
    SDL_RenderClear(renderer);
    yesBtnHighRet->render();
    noBtnHighRet->render();
    highRetLabel.draw();
    SDL_RenderPresent(renderer);
}

void HighschoolRetryWindow::clean(){

    while(!AssetManager::textures.empty()){
        AssetManager::textures.erase(AssetManager::textures.begin());
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    Mix_FreeMusic(bgmRetryHigh);
    bgmRetryHigh = nullptr;
    Mix_CloseAudio();
    Mix_Quit();

    SDL_Quit();
}
