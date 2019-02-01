#include "CollegeContinue.h"
#include "Components.h"
#include "AssetManager.h"
#include "ButtonObject.h"
#include "fstream"
#include "RetryCollege.h"
#include "Story.h"


Manager continueCollManager;
AssetManager *continueCollAssets = new AssetManager(&continueCollManager);
ButtonObject *yesBtnContinueColl, *noBtnContinueColl;
Mix_Chunk *collConBgm = nullptr;


auto& labelContinueColl(continueCollManager.addEntity());


SDL_Renderer *CollegeContinue::renderer;
SDL_Event CollegeContinue::event;
std::string CollegeContinue::windowName;

CollegeContinue::CollegeContinue(){}

CollegeContinue::~CollegeContinue(){}

void CollegeContinue::init(const char* title, int xpos, int ypos, int width, int height){

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(title,xpos,ypos,width,height,0);
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer)
            SDL_SetRenderDrawColor(renderer,46,76,61,255);

            isContinueCollegeRunning = true;
        }else{
            isContinueCollegeRunning = false;
        }

         if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
            std::cout<< "Error:" << Mix_GetError() << std::endl;
        }

        collConBgm = Mix_LoadWAV("continue.wav");
        Mix_PlayChannel(-1,collConBgm,2);

        if(collConBgm == NULL){
            std::cout<< "Error:" << Mix_GetError() << std::endl;
        }

        if(TTF_Init() == -1){
            std::cout<< "Error" << std::endl;
        }

        SDL_Color red = {138,249,195,255};
        continueCollAssets->AddFont("Flipps","Flipps.otf",20);
        labelContinueColl.addComponent<UILabel>(renderer,continueCollAssets,20,0,"Level Complete!", "Flipps", red);
        labelContinueColl.addComponent<UILabel>(renderer,continueCollAssets,60,100,"Continue?", "Flipps", red);

        yesBtnContinueColl = new ButtonObject(renderer,"assets/yes.png",100,150,100,100,true,6,100);
        noBtnContinueColl = new ButtonObject(renderer,"assets/no.png",100,220,100,100,true,6,100);
}

void CollegeContinue::handlerEvent(){
    continueCollManager.refresh();
    continueCollManager.update();
    yesBtnContinueColl->update();
    noBtnContinueColl->update();

    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        isContinueCollegeRunning = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if(MouseEvent::isMouseClicked(100,150,100,100,event) && !isClicked){
            Story::isFinishStory = false;
            isClicked = true;
            windowName = "college";
            isContinueCollegeRunning = false;
            CollegeWindow::isRunning = false;
        }else if(MouseEvent::isMouseClicked(100,220,100,100,event) && !isClicked){
            Story::isFinishStory = true;
            isClicked = true;
            windowName = "MainMenu";
            RetryCollege::windowName = "MainMenu";
            isContinueCollegeRunning = false;
            CollegeWindow::isRunning = false;
        }
        break;
    case SDL_MOUSEBUTTONUP:
            isClicked = false;
        break;
    }


}

void CollegeContinue::render(){

    SDL_RenderClear(renderer);
    yesBtnContinueColl->render();
    noBtnContinueColl->render();
    labelContinueColl.draw();
    SDL_RenderPresent(renderer);

}

void CollegeContinue::clean(){
     while(!AssetManager::textures.empty()){
        AssetManager::textures.erase(AssetManager::textures.begin());
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_FreeChunk(collConBgm);
    collConBgm = nullptr;
    Mix_CloseAudio();
    Mix_Quit();

    SDL_Quit();
}
