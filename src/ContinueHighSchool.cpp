#include "ContinueHighSchool.h"
#include "Components.h"
#include "AssetManager.h"
#include "ButtonObject.h"
#include "fstream"
#include "HighschoolRetryWindow.h"
#include "Story.h"

Manager continueHSManager;
AssetManager *continueHSAssets = new AssetManager(&continueHSManager);
ButtonObject *yesBtnContinueHS, *noBtnContinueHS;
Mix_Chunk *highConBgm = nullptr;


auto& labelContinueHS(continueHSManager.addEntity());


SDL_Renderer *ContinueHighSchool::renderer;
SDL_Event ContinueHighSchool::event;
std::string ContinueHighSchool::windowName;

ContinueHighSchool::ContinueHighSchool(){}

ContinueHighSchool::~ContinueHighSchool(){}

void ContinueHighSchool::init(const char* title, int xpos, int ypos, int width, int height){

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(title,xpos,ypos,width,height,0);
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer)
            SDL_SetRenderDrawColor(renderer,46,76,61,255);

            isContinueHighschoolRunning = true;
        }else{
            isContinueHighschoolRunning = false;
        }


        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
            std::cout<< "Error:" << Mix_GetError() << std::endl;
        }

        highConBgm = Mix_LoadWAV("continue.wav");
        Mix_PlayChannel(-1,highConBgm,2);

        if(highConBgm == NULL){
            std::cout<< "Error:" << Mix_GetError() << std::endl;
        }


        if(TTF_Init() == -1){
            std::cout<< "Error" << std::endl;
        }
        SDL_Color red = {138,249,195,255};
        continueHSAssets->AddFont("Flipps","Flipps.otf",20);
        labelContinueHS.addComponent<UILabel>(renderer,continueHSAssets,20,0,"Level Complete!", "Flipps", red);
        labelContinueHS.addComponent<UILabel>(renderer,continueHSAssets,60,100,"Continue?", "Flipps", red);

        yesBtnContinueHS = new ButtonObject(renderer,"assets/yes.png",100,150,100,100,true,6,100);
        noBtnContinueHS = new ButtonObject(renderer,"assets/no.png",100,220,100,100,true,6,100);
}

void ContinueHighSchool::handlerEvent(){
    continueHSManager.refresh();
    continueHSManager.update();
    yesBtnContinueHS->update();
    noBtnContinueHS->update();

    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        isContinueHighschoolRunning = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if(MouseEvent::isMouseClicked(100,150,100,100,event) && !isClicked){
            Story::isFinishStory = false;
            isClicked = true;
            windowName = "highschool";
            isContinueHighschoolRunning = false;
            HighschoolWindow::isRunning = false;
        }else if(MouseEvent::isMouseClicked(100,220,100,100,event) && !isClicked){
            Story::isFinishStory = true;
            isClicked = true;
            windowName = "MainMenu";
            HighschoolRetryWindow::windowName = "MainMenu";
            isContinueHighschoolRunning = false;
            HighschoolWindow::isRunning = false;
        }
        break;
    case SDL_MOUSEBUTTONUP:
            isClicked = false;
        break;
    }


}

void ContinueHighSchool::render(){
    SDL_RenderClear(renderer);
    yesBtnContinueHS->render();
    noBtnContinueHS->render();
    labelContinueHS.draw();
    SDL_RenderPresent(renderer);
}

void ContinueHighSchool::clean(){

    while(!AssetManager::textures.empty()){
        AssetManager::textures.erase(AssetManager::textures.begin());
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_FreeChunk(highConBgm);
    highConBgm = nullptr;
    Mix_CloseAudio();
    Mix_Quit();

    SDL_Quit();
}
