#include "StoryRetryWindow.h"


Manager storyRetryManager;
AssetManager *storyRetAsset = new AssetManager(&storyRetryManager);
auto& storyRetLabel(storyRetryManager.addEntity());

SDL_Renderer *StoryRetryWindow::renderer;
SDL_Event StoryRetryWindow::event;
std::string StoryRetryWindow::windowName;
ButtonObject *yesBtnStoryRet, *noBtnStoryRet;
Mix_Music *bgmRetryElem = nullptr;


StoryRetryWindow::StoryRetryWindow(){}

StoryRetryWindow::~StoryRetryWindow(){}

void StoryRetryWindow::init(const char *title, int xpos, int ypos, int width, int height){

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(title,xpos,ypos,width,height,0);
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer)
            SDL_SetRenderDrawColor(renderer,0,0,0,255);

        isStoryRetryWindowRunning = true;
    }else{
        isStoryRetryWindowRunning = false;
    }


    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }

    bgmRetryElem = Mix_LoadMUS("dead.mp3");
    Mix_PlayMusic(bgmRetryElem,-1);

    if(bgmRetryElem == NULL){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }


    if(TTF_Init() == -1){
        std::cout<< "Error" << std::endl;
    }


    storyRetAsset->AddFont("Flipps","Flipps.otf",20);
    SDL_Color color = {255,255,255,255};

    storyRetLabel.addComponent<UILabel>(renderer,storyRetAsset,70,0,"You lose!", "Flipps", color);
    storyRetLabel.addComponent<UILabel>(renderer,storyRetAsset,70,40,"Try again?", "Flipps", color);

    yesBtnStoryRet = new ButtonObject(renderer,"assets/yes.png",100,320,100,100,true,6,100);
    noBtnStoryRet = new ButtonObject(renderer,"assets/no.png",100,390,100,100,true,6,100);


}

void StoryRetryWindow::handlerEvent(){
    storyRetryManager.refresh();
    storyRetryManager.update();
    yesBtnStoryRet->update();
    noBtnStoryRet->update();

    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        isStoryRetryWindowRunning = false;
        break;
    }
    switch(event.type){
    case SDL_MOUSEBUTTONDOWN:
        if(MouseEvent::isMouseClicked(100,320,100,100,event) && !isClicked){
            isStoryRetryWindowRunning = false;
            isClicked = true;
        }else if(MouseEvent::isMouseClicked(100,390,100,100,event) && !isClicked){
            Story::isFinishStory = true;
            windowName = "MainMenu";
            ContinueWindow::windowName = "MainMenu";
            isStoryRetryWindowRunning = false;
            isClicked = true;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        isClicked = false;
        break;
    }




}


void StoryRetryWindow::render(){
    SDL_RenderClear(renderer);
    yesBtnStoryRet->render();
    noBtnStoryRet->render();
    storyRetLabel.draw();
    SDL_RenderPresent(renderer);
}


void StoryRetryWindow::clean(){

    while(!AssetManager::textures.empty()){
        AssetManager::textures.erase(AssetManager::textures.begin());
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);


    Mix_FreeMusic(bgmRetryElem);
    bgmRetryElem = nullptr;
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}
