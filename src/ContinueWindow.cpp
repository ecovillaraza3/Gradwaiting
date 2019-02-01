#include "ContinueWindow.h"
#include "Components.h"
#include "AssetManager.h"
#include "ButtonObject.h"
#include "fstream"
#include "StoryRetryWindow.h"


Manager continueManager;
AssetManager *continueAssets = new AssetManager(&continueManager);
ButtonObject *yesBtnContinue, *noBtnContinue;
Mix_Chunk *elemConBgm = nullptr;


auto& labelContinue(continueManager.addEntity());

ContinueWindow::ContinueWindow(){}

ContinueWindow::~ContinueWindow(){}

SDL_Renderer *ContinueWindow::renderer;
SDL_Event ContinueWindow::event;
std::string ContinueWindow::windowName;

void ContinueWindow::init(const char* title, int xpos, int ypos, int width, int height){

      if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(title,xpos,ypos,width,height,0);
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer)
            SDL_SetRenderDrawColor(renderer,46,76,61,255);

            isContinueWindowRunning = true;
        }else{
            isContinueWindowRunning = false;
        }

        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
            std::cout<< "Error:" << Mix_GetError() << std::endl;
        }

        elemConBgm = Mix_LoadWAV("continue.wav");
        Mix_PlayChannel(-1,elemConBgm,2);

        if(elemConBgm == NULL){
            std::cout<< "Error:" << Mix_GetError() << std::endl;
        }


        if(TTF_Init() == -1){
            std::cout<< "Error" << std::endl;
        }
        SDL_Color red = {138,249,195,255};

        continueAssets->AddFont("Flipps","Flipps.otf",20);
        labelContinue.addComponent<UILabel>(renderer,continueAssets,20,0,"Level Complete!", "Flipps", red);
        labelContinue.addComponent<UILabel>(renderer,continueAssets,60,100,"Continue?", "Flipps", red);

        yesBtnContinue = new ButtonObject(renderer,"assets/yes.png",100,150,100,100,true,6,100);
        noBtnContinue = new ButtonObject(renderer,"assets/no.png",100,220,100,100,true,6,100);


}
void ContinueWindow::handlerEvent(){

    continueManager.refresh();
    continueManager.update();

    yesBtnContinue->update();
    noBtnContinue->update();

    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        isContinueWindowRunning = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if(MouseEvent::isMouseClicked(100,150,100,100,event) && !isClicked){
            Story::isFinishStory = false;
            isClicked = true;
            windowName = "elementary";
            isContinueWindowRunning = false;
            Story::isRunning = false;
        }else if(MouseEvent::isMouseClicked(100,220,100,100,event) && !isClicked){
            Story::isFinishStory = true;
            isClicked = true;
            windowName = "MainMenu";
            StoryRetryWindow::windowName = "MainMenu";
            isContinueWindowRunning = false;
            Story::isRunning = false;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        isClicked = false;
        break;
    }

}

void ContinueWindow::render(){
    SDL_RenderClear(renderer);
    yesBtnContinue->render();
    noBtnContinue->render();
    labelContinue.draw();
    SDL_RenderPresent(renderer);
}

void ContinueWindow::clean(){

    while(!AssetManager::textures.empty()){
        AssetManager::textures.erase(AssetManager::textures.begin());
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);


    Mix_FreeChunk(elemConBgm);
    elemConBgm = nullptr;
    Mix_CloseAudio();
    Mix_Quit();

    SDL_Quit();
}

