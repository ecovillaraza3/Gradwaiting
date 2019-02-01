#include "CollegeWindow.h"
#include "Map.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Components.h"
#include <sstream>
#include <fstream>
#include "Story.h"

#include "RetryCollege.h"


CollegeWindow::CollegeWindow(){}

CollegeWindow::~CollegeWindow(){}


std::string CollegeWindow::windowName;
SDL_Renderer *CollegeWindow::renderer = nullptr;
SDL_Event CollegeWindow::event;
bool CollegeWindow::isRunning;

Map *collMap = nullptr;
Manager collManager;
Mix_Music *bgmCollege = nullptr;

auto& collPlayer(collManager.addEntity());
auto& collLabel(collManager.addEntity());

void CollegeWindow::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){

    int flags = 0;
    if(fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(title,xpos,ypos,width,height,flags);
        renderer = SDL_CreateRenderer(window,-1,0);

        if(renderer){
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            printf("Render Created \n");
        }

        isRunning = true;
    }else{
        isRunning = false;
    }
    std::ifstream getYearLevel;
    getYearLevel.open("yearlevel.txt");
    getYearLevel >> level;
    getYearLevel.close();

    if(level == 1){
        collTime = 21;
        levelString = "1st Year time : ";
        projSpeed = 10;
    }else if(level == 2){
        collTime = 21;
        levelString = "2nd Year time : ";
        projSpeed = 15;
    }else if(level == 3){
        collTime = 21;
        levelString = "3rd Year time : ";
        projSpeed = 20;
    }else if(level == 4){
        collTime = 21;
        levelString = "4th Year time : ";
        projSpeed = 30;
    }else if(level == 5){
        collTime = 21;
        levelString = "GRAD WAITING!! time : ";
        projSpeed = 35;
    }

     if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }

    bgmCollege = Mix_LoadMUS("storybg.mp3");
    Mix_PlayMusic(bgmCollege,-1);

    if(bgmCollege == NULL){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }


    assets = new AssetManager(&collManager);
    if(TTF_Init() == -1){
        std::cout<< "Error" << std::endl;
    }

    assets->AddTexture("player","assets/player_anim_two.png",renderer);
    assets->AddTexture("terrain","assets/college_tileset.png",renderer);

    assets->AddTexture("cos","assets/college_cos.png",renderer);
    assets->AddTexture("coe","assets/college_coe.png",renderer);
    assets->AddTexture("coa","assets/college_coa.png",renderer);
    assets->AddTexture("cla","assets/college_cla.png",renderer);
    assets->AddTexture("cie","assets/college_cie.png",renderer);
    assets->AddTexture("computer","assets/computer.png",renderer);


    assets->AddTexture("bookshelf","assets/elem_bookshelf.png",renderer);
    assets->AddTexture("window","assets/window.png",renderer);
    assets->AddTexture("paper","assets/paper.png",renderer);
    assets->AddTexture("paper_two","assets/paper_two.png",renderer);
    assets->AddTexture("clock","assets/elem_clock.png",renderer);
    assets->AddTexture("vandalism","assets/elem_wall.png",renderer);
    assets->AddTexture("singko","assets/singko.png",renderer);
    assets->AddTexture("usb","assets/usb.png",renderer);
    assets->AddTexture("flag","assets/elem_flag.png",renderer);
    assets->AddFont("VintageParty","Flipps.otf",20);

    collMap = new Map("terrain",4,4,"college");
    collMap->LoadMap("assets/collegemap.txt",32,32,renderer,assets);

    collPlayer.addComponent<TransformComponent>(50,330,32,32,4);
    collPlayer.addComponent<SpriteComponent>("player",true,renderer,assets);
    collPlayer.addComponent<KeyboardController>("college");
    collPlayer.addComponent<ColliderComponent>("player");
    collPlayer.addGroup(AssetManager::groupPlayers);


    SDL_Color color = {255,255,255,255};
    collLabel.addComponent<UILabel>(renderer,assets,0,0, "", "VintageParty", color);

}


auto& collPlayers(collManager.getGroup(AssetManager::groupPlayers));
auto& collTile(collManager.getGroup(AssetManager::groupMap));
auto& collColliders(collManager.getGroup(AssetManager::groupColliders));
auto& collProjectiles(collManager.getGroup(AssetManager::groupProjectiles));

void CollegeWindow::handlerEvent(){
    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        Story::isFinishStory = true;
        CollegeContinue::windowName = "MainMenu";
        isRunning = false;
        break;
    }
}

void CollegeWindow::update(){
    cnt++;
    flagCnt++;
    entCnt++;
    SDL_Rect playerCol = collPlayer.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = collPlayer.getComponent<TransformComponent>().position;

    std::stringstream ss;
    ss << levelString << collTime;
    collLabel.getComponent<UILabel>().setLabelText(ss.str(),"VintageParty");

    collManager.refresh();
    collManager.update();

    if(time(0) != temp){
        collTime--;
    }
    temp = time(0);

      int x = rand()%30;
    int y = rand()%350;
    int yKalatIceCream = rand()%450;
    int yKalatBubbleGum = rand()%450;

    // INDEXING
    while(x <= 8){
        x = rand()%projSpeed;
    }
    while(y < 320){
        y = rand()%400;
    }
    while(yKalatIceCream < 410){
        yKalatIceCream = rand()%450;
    }
    while(yKalatBubbleGum < 410){
        yKalatBubbleGum = 1+rand()%450;
    }


    // DISPLAY
    switch(cnt){
        case 10:
                assets->CreateProjectile(Vector2D(1000,y),Vector2D(-9,0),32,32,100,2,4,"projectiles","usb",renderer,assets);
            assets->CreateProjectile(Vector2D(1200,117),Vector2D(-7,0),32,32,100,2,1,"doorDesign","cos",renderer,assets);
        break;
        case 36:
            assets->CreateProjectile(Vector2D(1200,200),Vector2D(-7,0),32,32,100,2,1,"computerDesign","computer",renderer,assets);
            break;
        case 50:
            assets->CreateProjectile(Vector2D(1200,117),Vector2D(-7,0),32,32,100,2,1,"doorDesign","coe",renderer,assets);
            assets->CreateProjectile(Vector2D(1100,y),Vector2D(-x,0),32,32,100,1,1,"projectiles","singko",renderer,assets);
            //assets->CreateProjectile(Vector2D(1000,0),Vector2D(-7,0),32,32,100,2,2,"windowDesign","window",renderer,assets);
            assets->CreateProjectile(Vector2D(1000,yKalatBubbleGum),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper",renderer,assets);
        break;
         case 83:
            assets->CreateProjectile(Vector2D(1200,200),Vector2D(-7,0),32,32,100,2,1,"computerDesign","computer",renderer,assets);
            break;
        case 100:
            assets->CreateProjectile(Vector2D(1200,117),Vector2D(-7,0),32,32,100,2,1,"doorDesign","coa",renderer,assets);
            //assets->CreateProjectile(Vector2D(1000,0),Vector2D(-7,0),32,32,100,2,2,"windowDesign","window",renderer,assets);
            assets->CreateProjectile(Vector2D(1000,yKalatBubbleGum),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper",renderer,assets);
        break;
         case 135:
            assets->CreateProjectile(Vector2D(1200,200),Vector2D(-7,0),32,32,100,2,1,"computerDesign","computer",renderer,assets);
            break;
        case 150:
            assets->CreateProjectile(Vector2D(1200,117),Vector2D(-7,0),32,32,100,2,1,"doorDesign","cla",renderer,assets);
            //assets->CreateProjectile(Vector2D(1000,0),Vector2D(-7,0),32,32,100,2,2,"windowDesign","window",renderer,assets);
            assets->CreateProjectile(Vector2D(1000,yKalatIceCream),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper_two",renderer,assets);
        break;
         case 180:
            assets->CreateProjectile(Vector2D(1200,200),Vector2D(-7,0),32,32,100,2,1,"computerDesign","computer",renderer,assets);
            break;
        case 200:
            assets->CreateProjectile(Vector2D(1200,117),Vector2D(-7,0),32,32,100,2,1,"doorDesign","cie",renderer,assets);
        break;
        case 210:
            assets->CreateProjectile(Vector2D(1000,yKalatBubbleGum),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper",renderer,assets);
            break;
        case 220:
            assets->CreateProjectile(Vector2D(1000,yKalatIceCream),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper_two",renderer,assets);
            break;
        case 240:
                assets->CreateProjectile(Vector2D(1000,yKalatBubbleGum),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper",renderer,assets);
                cnt=0;
            break;
        break;
    }

// COLLIDERS
    for(auto& c : collColliders){
        SDL_Rect cCol = c -> getComponent<ColliderComponent>().collider;
        if(Collision::AABB(cCol, playerCol)){
            collPlayer.getComponent<TransformComponent>().position = playerPos;
        }
    }

// PROJECTILES
    if(entCnt > 80){
    for(auto& p : collProjectiles){
        if(Collision::XXYY(collPlayer.getComponent<ColliderComponent>().collider,p->getComponent<ColliderComponent>().collider)){
            printf("Hit!\n");
            p->destroy();


             Mix_FreeMusic(bgmCollege);
             bgmCollege = nullptr;
             Mix_CloseAudio();
             Mix_Quit();

            RetryCollege *collRet = new RetryCollege();
             collRet->init("Retry Window",400,SDL_WINDOWPOS_CENTERED,300,500);
             while(collRet->running()){
                collRet->handlerEvent();
                collRet->render();
             }

            isRunning = false;
        }
      }
    }

    if(flagCnt == 1165)
        assets->CreateProjectile(Vector2D(1000,250),Vector2D(-7,0),32,32,100,2,5,"flagDesign","flag",renderer,assets);

    if(collTime == -1){


         Mix_FreeMusic(bgmCollege);
         bgmCollege = nullptr;
         Mix_CloseAudio();
         Mix_Quit();

        CollegeContinue *contineCollWindow = new CollegeContinue();
        contineCollWindow->init("Continue Window",400,SDL_WINDOWPOS_CENTERED,300,500);
        while(contineCollWindow->running()){
            contineCollWindow->handlerEvent();
            contineCollWindow->render();
        }
        isRunning = false;


        std::ofstream setYearLevel;
        setYearLevel.open("yearlevel.txt");
        setYearLevel << level+1;
        setYearLevel.close();

         if(level == 5){
            std::ofstream setYearLevel;
            setYearLevel.open("yearlevel.txt");
            setYearLevel << 1;
            setYearLevel.close();

            setYearLevel.open("mainyear.txt");
            setYearLevel << "Finish";
            setYearLevel.close();
            CollegeContinue::windowName = "Finish";
            RetryCollege::windowName = "Finish";
        }
    }

}


void CollegeWindow::render(){
    SDL_RenderClear(renderer);

    for(auto& h: collColliders){
        h->draw();
    }

    for(auto& t : collTile){
        t->draw();
    }

    for(auto& p : collProjectiles){
        p->draw();
    }

    for(auto& p : collPlayers){
        p->draw();
    }

    collLabel.draw();

    SDL_RenderPresent(renderer);


}

void CollegeWindow::clean(){

    collManager.refresh();
    collManager.update();


    while(!AssetManager::textures.empty()){
        AssetManager::textures.erase(AssetManager::textures.begin());
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    cnt = 0;
    flagCnt = 0;
    level = 0;
    collTime = 0;
    entCnt = 0;
    SDL_Quit();
}



