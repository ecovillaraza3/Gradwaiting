#include "Story.h"
#include "Map.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Components.h"
#include <sstream>
#include <fstream>

#include "StoryRetryWindow.h"

RetryWindow *elemRetryWindow = nullptr;
Mix_Music *bgmStory = nullptr;

Story::Story(){}

Story::~Story(){}

Map *elemMap = nullptr;
Manager elemManager;
std::string Story::windowName;
bool Story::isFinishStory;

SDL_Event Story::event;
SDL_Renderer *Story::renderer = nullptr;
bool Story::isRunning = false;
bool Story::isDeleteAnimation;

auto& elemPlayer(elemManager.addEntity());
auto& elemLabel(elemManager.addEntity());

void Story::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){

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
        elemTime = 21;
        levelString = "Grade 1 time : ";
        projSpeed = 10;
    }else if(level == 2){
        elemTime = 21;
        levelString = "Grade 2 time : ";
        projSpeed = 10;
    }else if(level == 3){
        elemTime = 21;
        levelString = "Grade 3 time : ";
        projSpeed = 10;
    }else if(level == 4){
        elemTime = 21;
        levelString = "Grade 4 time : ";
        projSpeed = 10;
    }else if(level == 5){
        elemTime = 21;
        levelString = "Grade 5 time : ";
        projSpeed = 15;
    }else if(level == 6){
        elemTime = 21;
        levelString = "GRAD WAITING!! time : ";
        projSpeed = 15;
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }

    bgmStory = Mix_LoadMUS("storybg.mp3");
    Mix_PlayMusic(bgmStory,-1);

    if(bgmStory == NULL){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }

    assets = new AssetManager(&elemManager);
    if(TTF_Init() == -1){
        std::cout<< "Error" << std::endl;
    }


    assets->AddTexture("terrain","assets/elem_tileset.png",renderer);
    assets->AddTexture("player","assets/player_anim_two.png",renderer);
    assets->AddTexture("door","assets/elem_door.png",renderer);
    assets->AddTexture("bookshelf","assets/elem_bookshelf.png",renderer);
    assets->AddTexture("window","assets/window_elem.png",renderer);
    assets->AddTexture("paper","assets/paper.png",renderer);
    assets->AddTexture("paper_two","assets/paper_two.png",renderer);
    assets->AddTexture("clock","assets/elem_clock.png",renderer);
    assets->AddTexture("vandalism","assets/elem_wall.png",renderer);
    assets->AddTexture("book","assets/notebook.png",renderer);
    assets->AddTexture("flag","assets/elem_flag.png",renderer);
    assets->AddFont("VintageParty","Flipps.otf",20);



    elemMap = new Map("terrain",4,4,"elementary");
    elemMap->LoadMap("assets/elemmap.txt",32,32,renderer,assets);

    elemPlayer.addComponent<TransformComponent>(50,330,32,32,4);
    elemPlayer.addComponent<SpriteComponent>("player",true,renderer,assets);
    elemPlayer.addComponent<KeyboardController>("elementary");
    elemPlayer.addComponent<ColliderComponent>("player");
    elemPlayer.addGroup(AssetManager::groupPlayers);

    SDL_Color color = {255,255,255,255};
    elemLabel.addComponent<UILabel>(renderer,assets,0,0, "", "VintageParty", color);


}


auto& elemTile(elemManager.getGroup(AssetManager::groupMap));
auto& elemPlayers(elemManager.getGroup(AssetManager::groupPlayers));
auto& elemColliders(elemManager.getGroup(AssetManager::groupColliders));
auto& elemProjectiles(elemManager.getGroup(AssetManager::groupProjectiles));

void Story::handlerEvent(){
    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        ContinueWindow::windowName = "MainMenu";
        isFinishStory = true;
        isRunning = false;
        break;
    }

}

void Story::update(){
    cnt++;
    flagCnt++;
    entCnt++;
    SDL_Rect playerCol = elemPlayer.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = elemPlayer.getComponent<TransformComponent>().position;


    std::stringstream ss;
    ss << levelString << elemTime;
    elemLabel.getComponent<UILabel>().setLabelText(ss.str(),"VintageParty");

    elemManager.refresh();
    elemManager.update();

    if(time(0) != temp){
        elemTime--;
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
            assets->CreateProjectile(Vector2D(1100,y),Vector2D(-x,0),32,32,100,2,5,"projectiles","book",renderer,assets);
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
            assets->CreateProjectile(Vector2D(1200,165),Vector2D(-7,0),32,32,100,2,1,"doorDesign","door",renderer,assets);
        break;
        case 210:
            assets->CreateProjectile(Vector2D(1000,yKalatBubbleGum),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper",renderer,assets);
            break;
        case 220:
            assets->CreateProjectile(Vector2D(1317,200),Vector2D(-7,0),60,60,100,2,1,"sign","vandalism",renderer,assets);
            assets->CreateProjectile(Vector2D(1000,yKalatIceCream),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper_two",renderer,assets);
            break;
        case 240:
                assets->CreateProjectile(Vector2D(1000,yKalatBubbleGum),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper",renderer,assets);
                cnt=0;
            break;
        break;
    }



    for(auto& c : elemColliders){
        SDL_Rect cCol = c -> getComponent<ColliderComponent>().collider;
        if(Collision::AABB(cCol, playerCol)){
            elemPlayer.getComponent<TransformComponent>().position = playerPos;
        }
    }


    if(entCnt > 80){
    // PROJECTILES
    for(auto& p : elemProjectiles){
        if(Collision::XXYY(elemPlayer.getComponent<ColliderComponent>().collider,p->getComponent<ColliderComponent>().collider)){
            printf("Hit!\n");
            p->destroy();


             Mix_FreeMusic(bgmStory);
             bgmStory = nullptr;
             Mix_CloseAudio();
             Mix_Quit();

             StoryRetryWindow *storRet = new StoryRetryWindow();
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

    if(elemTime == -1){

        Mix_FreeMusic(bgmStory);
        bgmStory = nullptr;
        Mix_CloseAudio();
        Mix_Quit();


        ContinueWindow *con = new ContinueWindow();
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
            setYearLevel << "highschool";
            setYearLevel.close();
            ContinueWindow::windowName = "highschool";
            StoryRetryWindow::windowName = "highschool";
        }

    }


}

void Story::render(){
    SDL_RenderClear(renderer);
   for(auto& col : elemColliders){
        col->draw();
   }

    for(auto& t : elemTile){
        t->draw();
    }

    for(auto& p : elemProjectiles){
        p->draw();
    }
    for(auto& p : elemPlayers){
        p->draw();
    }


    elemLabel.draw();

    SDL_RenderPresent(renderer);
}

void Story::clean(){

    elemManager.del();

    elemManager.refresh();
    elemManager.update();

    while(!AssetManager::textures.empty()){
        AssetManager::textures.erase(AssetManager::textures.begin());
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    cnt = 0;
    flagCnt = 0;
    level = 0;
    elemTime = 0;
    entCnt = 0;

    SDL_Quit();
}
