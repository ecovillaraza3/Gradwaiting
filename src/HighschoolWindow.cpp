#include "HighschoolWindow.h"
#include "Map.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Components.h"
#include <sstream>
#include <fstream>
#include "Story.h"


#include "HighschoolRetryWindow.h"

HighschoolWindow::HighschoolWindow(){}

HighschoolWindow::~HighschoolWindow(){}

std::string HighschoolWindow::windowName;
SDL_Renderer *HighschoolWindow::renderer = nullptr;
SDL_Event HighschoolWindow::event;
bool HighschoolWindow::isRunning;

Map *highMap = nullptr;
Manager highManager;
Mix_Music *bgmStoryHigh = nullptr;

auto& highPlayer(highManager.addEntity());
auto& highLabel(highManager.addEntity());


void HighschoolWindow::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){

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
        highTime = 21;
        levelString = "Grade 7 time : ";
        projSpeed = 10;
    }else if(level == 2){
        highTime = 21;
        levelString = "Grade 8 time : ";
        projSpeed = 15;
    }else if(level == 3){
        highTime = 21;
        levelString = "Grade 9 time : ";
        projSpeed = 20;
    }else if(level == 4){
        highTime = 21;
        levelString = "Grade 10 time : ";
        projSpeed = 30;
    }else if(level == 5){
        highTime = 21;
        levelString = "Grade 11 time : ";
        projSpeed = 35;
    }else if(level == 6){
        highTime = 21;
        levelString = "GRAD WAITING!! time : ";
        projSpeed = 40;
    }
      if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }

    bgmStoryHigh = Mix_LoadMUS("storybg.mp3");
    Mix_PlayMusic(bgmStoryHigh,-1);

    if(bgmStoryHigh == NULL){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }


    assets = new AssetManager(&highManager);
    if(TTF_Init() == -1){
        std::cout<< "Error" << std::endl;
    }

    assets->AddTexture("player","assets/player_anim_two.png",renderer);
    assets->AddTexture("terrain","assets/highschool_tileset.png",renderer);
    assets->AddTexture("door","assets/door_high.png",renderer);
    assets->AddTexture("bookshelf","assets/elem_bookshelf.png",renderer);
    assets->AddTexture("window","assets/window_high.png",renderer);
    assets->AddTexture("paper","assets/paper.png",renderer);
    assets->AddTexture("paper_two","assets/paper_two.png",renderer);
    assets->AddTexture("clock","assets/elem_clock.png",renderer);
    assets->AddTexture("vandalism","assets/elem_wall.png",renderer);
    assets->AddTexture("globe","assets/globe.png",renderer);
    assets->AddTexture("flag","assets/elem_flag.png",renderer);
    assets->AddFont("VintageParty","Flipps.otf",20);


    highMap = new Map("terrain",4,4,"highschool");
    highMap->LoadMap("assets/highschoolmap.txt",32,32,renderer,assets);

    highPlayer.addComponent<TransformComponent>(50,330,32,32,4);
    highPlayer.addComponent<SpriteComponent>("player",true,renderer,assets);
    highPlayer.addComponent<KeyboardController>("highschool");
    highPlayer.addComponent<ColliderComponent>("player");
    highPlayer.addGroup(AssetManager::groupPlayers);


    SDL_Color color = {255,255,255,255};
    highLabel.addComponent<UILabel>(renderer,assets,0,0, "", "VintageParty", color);


}


auto& highPlayers(highManager.getGroup(AssetManager::groupPlayers));
auto& highTile(highManager.getGroup(AssetManager::groupMap));
auto& highColliders(highManager.getGroup(AssetManager::groupColliders));
auto& highProjectiles(highManager.getGroup(AssetManager::groupProjectiles));

void HighschoolWindow::handlerEvent(){
    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        Story::isFinishStory = true;
        ContinueHighSchool::windowName = "MainMenu";
        isRunning = false;
        break;
    }

}


void HighschoolWindow::update(){
    cnt++;
    flagCnt++;
    entCnt++;
    SDL_Rect playerCol = highPlayer.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = highPlayer.getComponent<TransformComponent>().position;


    std::stringstream ss;
    ss << levelString << highTime;
    highLabel.getComponent<UILabel>().setLabelText(ss.str(),"VintageParty");

    highManager.refresh();
    highManager.update();

    if(time(0) != temp){
        highTime--;
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
        case 50:
            assets->CreateProjectile(Vector2D(1100,y),Vector2D(-x,0),32,32,100,2,4,"projectiles","globe",renderer,assets);
            assets->CreateProjectile(Vector2D(1317,300),Vector2D(-7,0),60,60,100,2,1,"sign","bookshelf",renderer,assets);
            assets->CreateProjectile(Vector2D(1000,0),Vector2D(-7,0),32,32,100,2,2,"windowDesign","window",renderer,assets);
            assets->CreateProjectile(Vector2D(1000,yKalatBubbleGum),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper",renderer,assets);
        break;
        case 100:
            assets->CreateProjectile(Vector2D(1317,300),Vector2D(-7,0),60,60,100,2,1,"sign","bookshelf",renderer,assets);
            assets->CreateProjectile(Vector2D(1000,0),Vector2D(-7,0),32,32,100,2,2,"windowDesign","window",renderer,assets);
                assets->CreateProjectile(Vector2D(1000,yKalatBubbleGum),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper",renderer,assets);
        break;
        case 150:
            assets->CreateProjectile(Vector2D(1317,300),Vector2D(-7,0),60,60,100,2,1,"sign","bookshelf",renderer,assets);
            assets->CreateProjectile(Vector2D(1000,0),Vector2D(-7,0),32,32,100,2,2,"windowDesign","window",renderer,assets);
            assets->CreateProjectile(Vector2D(1000,yKalatIceCream),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper_two",renderer,assets);
        break;
        case 200:
            assets->CreateProjectile(Vector2D(1317,90),Vector2D(-7,0),32,32,100,2,1,"sign","clock",renderer,assets);
            assets->CreateProjectile(Vector2D(1200,152),Vector2D(-7,0),32,32,100,2,3,"doorDesign","door",renderer,assets);
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
    for(auto& c : highColliders){
        SDL_Rect cCol = c -> getComponent<ColliderComponent>().collider;
        if(Collision::AABB(cCol, playerCol)){
            highPlayer.getComponent<TransformComponent>().position = playerPos;
        }
    }

// PROJECTILES
    if(entCnt > 80){
    for(auto& p : highProjectiles){
        if(Collision::XXYY(highPlayer.getComponent<ColliderComponent>().collider,p->getComponent<ColliderComponent>().collider)){
            printf("Hit!\n");
            p->destroy();


             Mix_FreeMusic(bgmStoryHigh);
             bgmStoryHigh = nullptr;
             Mix_CloseAudio();
             Mix_Quit();

            HighschoolRetryWindow *storRet = new HighschoolRetryWindow();
             storRet->init("Retry Window",400,SDL_WINDOWPOS_CENTERED,300,500);
             while(storRet->running()){
                storRet->handlerEvent();
                storRet->render();
             }

            isRunning = false;

        }
      }
    }

    if(flagCnt == 1165)
        assets->CreateProjectile(Vector2D(1000,250),Vector2D(-7,0),32,32,100,2,5,"flagDesign","flag",renderer,assets);

    if(highTime == -1){


        Mix_FreeMusic(bgmStoryHigh);
        bgmStoryHigh = nullptr;
        Mix_CloseAudio();
        Mix_Quit();


        ContinueHighSchool *con = new ContinueHighSchool();
        con->init("Continue Window",400,SDL_WINDOWPOS_CENTERED,300,500);
        while(con->running()){
            con->handlerEvent();
            con->render();
        }
        isRunning = false;

        std::ofstream setYearLevel;
        setYearLevel.open("yearlevel.txt");
        setYearLevel << level+1;
        setYearLevel.close();

        if(level == 6){
            std::ofstream setYearLevel;
            setYearLevel.open("yearlevel.txt");
            setYearLevel << 1;
            setYearLevel.close();

            setYearLevel.open("mainyear.txt");
            setYearLevel << "college";
            setYearLevel.close();
            ContinueHighSchool::windowName = "college";
            HighschoolRetryWindow::windowName = "college";
        }


    }




}

void HighschoolWindow::render(){
    SDL_RenderClear(renderer);

    for(auto& h: highColliders){
        h->draw();
    }

    for(auto& t : highTile){
        t->draw();
    }

    for(auto& p : highProjectiles){
        p->draw();
    }

    for(auto& p : highPlayers){
        p->draw();
    }

    highLabel.draw();

    SDL_RenderPresent(renderer);
}

void HighschoolWindow::clean(){


    highManager.refresh();
    highManager.update();

    while(!AssetManager::textures.empty()){
        AssetManager::textures.erase(AssetManager::textures.begin());
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    cnt = 0;
    flagCnt = 0;
    level = 0;
    highTime = 0;
    entCnt = 0;
    SDL_Quit();
}
