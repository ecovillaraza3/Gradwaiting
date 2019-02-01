#include "Game.h"

#include "Map.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Components.h"
#include <sstream>


RetryWindow * retryWindow = nullptr;

Map *maper = nullptr;
Manager manager;
Mix_Music *bgm = nullptr;

std::string Game::windowName;

SDL_Renderer *Game::renderer = nullptr;
bool Game::isDeleteAnimation;
SDL_Event Game::event;
bool Game::isRunning = false;
auto& player(manager.addEntity());
auto& label(manager.addEntity());

Game::Game(){
    isDeleteAnimation = false;
}

Game::~Game(){

}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
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

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }

    bgm = Mix_LoadMUS("endlessbg.mp3");
    Mix_PlayMusic(bgm,-1);

    if(bgm == NULL){
        std::cout<< "Error:" << Mix_GetError() << std::endl;
    }

    assets = new AssetManager(&manager);
    if(TTF_Init() == -1){
        std::cout<< "Error" << std::endl;
    }


    assets->AddTexture("terrain","assets/tilemo.png",renderer);
    assets->AddTexture("player","assets/player_anim_two.png",renderer);
    assets->AddTexture("book", "assets/book.png",renderer);
    assets->AddTexture("chembook", "assets/chem_book.png",renderer);
    assets->AddTexture("window","assets/window.png",renderer);
    assets->AddTexture("door","assets/door.png",renderer);
    assets->AddTexture("paper_two","assets/paper_two.png",renderer);
    assets->AddTexture("paper","assets/paper.png",renderer);
    assets->AddTexture("sign","assets/sign.png",renderer);
    assets->AddFont("VintageParty","Flipps.otf",20);



    maper = new Map("terrain",4,4,"endless");
    maper->LoadMap("assets/map.txt",32,32,renderer,assets);


    player.addComponent<TransformComponent>(50,330,32,32,4);
    player.addComponent<SpriteComponent>("player",true,renderer,assets);
    player.addComponent<KeyboardController>("endless");
    player.addComponent<ColliderComponent>("player");
    player.addGroup(AssetManager::groupPlayers);

    SDL_Color color = {255,255,255,255};
    label.addComponent<UILabel>(renderer,assets,0,0, "0", "VintageParty", color);;

}


auto& tile(manager.getGroup(AssetManager::groupMap));
auto& players(manager.getGroup(AssetManager::groupPlayers));
auto& colliders(manager.getGroup(AssetManager::groupColliders));
auto& projectiles(manager.getGroup(AssetManager::groupProjectiles));


void Game::handlerEvent(){
    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        isDeleteAnimation = true;
        isRunning = false;
        RetryWindow::windowName = "MainMenu";
        windowName = "MainMenu";
        break;
    }
}

void Game::update(){

    cnt++;
    score++;
    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;

    std::stringstream ss;
    ss << "Score: " <<score;
    label.getComponent<UILabel>().setLabelText(ss.str(),"VintageParty");

    manager.refresh();
    manager.update();

    //generate random number
    int x = rand()%30;
    int y = rand()%350;
    int yKalatIceCream = rand()%450;
    int yKalatBubbleGum = rand()%450;
    // INDEXING
    while(x <= 8){
        x = rand()%30;
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
            assets->CreateProjectile(Vector2D(1100,y),Vector2D(-x,0),32,32,100,2,4,"projectiles","book",renderer,assets);
            assets->CreateProjectile(Vector2D(1000,0),Vector2D(-7,0),32,32,100,2,2,"windowDesign","window",renderer,assets);
            assets->CreateProjectile(Vector2D(1000,yKalatBubbleGum),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper",renderer,assets);
        break;
        case 100:
            assets->CreateProjectile(Vector2D(1000,0),Vector2D(-7,0),32,32,100,2,2,"windowDesign","window",renderer,assets);
                assets->CreateProjectile(Vector2D(1000,yKalatBubbleGum),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper",renderer,assets);
        break;
        case 150:
            assets->CreateProjectile(Vector2D(1000,0),Vector2D(-7,0),32,32,100,2,2,"windowDesign","window",renderer,assets);
            assets->CreateProjectile(Vector2D(1000,yKalatIceCream),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper_two",renderer,assets);
        break;
        case 200:
            assets->CreateProjectile(Vector2D(1317,90),Vector2D(-7,0),32,32,100,2,1,"sign","sign",renderer,assets);
            assets->CreateProjectile(Vector2D(1200,152),Vector2D(-7,0),32,32,100,2,3,"doorDesign","door",renderer,assets);
        break;
        case 210:
            assets->CreateProjectile(Vector2D(1100,y),Vector2D(-x,0),32,32,100,2,4,"projectiles","book",renderer,assets);
            assets->CreateProjectile(Vector2D(1000,yKalatBubbleGum),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper",renderer,assets);
            break;
        case 220:
                assets->CreateProjectile(Vector2D(1000,yKalatIceCream),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper_two",renderer,assets);
            break;
        case 240:
                assets->CreateProjectile(Vector2D(1000,yKalatBubbleGum),Vector2D(-7,0),32,32,100,2,1,"kalatSaLapag","paper",renderer,assets);
            break;
        case 280:
               cnt=0;
            break;
    }

    for(auto& c : colliders){
        SDL_Rect cCol = c -> getComponent<ColliderComponent>().collider;
        if(Collision::AABB(cCol, playerCol)){
            player.getComponent<TransformComponent>().position = playerPos;
        }
    }
    printf("%i\n",score);



// PROJECTILES
    if(score > 80){
    for(auto& p : projectiles){
        if(Collision::XXYY(player.getComponent<ColliderComponent>().collider,p->getComponent<ColliderComponent>().collider)){
            printf("Hit!\n");
            p->destroy();

            std::ifstream getCurrentScore, getHighScore;
            std::ofstream setCurrentScore;
            setCurrentScore.open("currentscore.txt");
            getCurrentScore.open("currentscore.txt");
            getHighScore.open("highscore.txt");
            setCurrentScore << score-1 << std::endl;
            getCurrentScore >> currentScore;
            getHighScore >> highscore;
            getCurrentScore.close();
            setCurrentScore.close();
            getHighScore.close();

            if(currentScore > highscore){
                std::ofstream setHighScore;
                setHighScore.open("highscore.txt");
                setHighScore << currentScore << std::endl;
                setHighScore.close();
            }


            Mix_FreeMusic(bgm);
            bgm = nullptr;
            Mix_CloseAudio();
            Mix_Quit();

            retryWindow = new RetryWindow();
            retryWindow->init("Retry Window",400,SDL_WINDOWPOS_CENTERED,300,500);
            while(retryWindow->running()){
                retryWindow->handlerEvent();
                retryWindow->render();
            }

            isRunning = false;
        }
    }
    }

}


void Game::render(){
    SDL_RenderClear(renderer);

   for(auto& col : colliders){
        col->draw();
   }

    for(auto& t : tile){
        t->draw();
    }

    for(auto& p : projectiles){
        p->draw();
    }

    for(auto& p : players){
        p->draw();
    }

    label.draw();

    SDL_RenderPresent(renderer);
}

void Game::clean(){
    manager.del();

    manager.refresh();
    manager.update();


    manager.refresh();
    manager.update();

    while(!AssetManager::textures.empty()){
        AssetManager::textures.erase(AssetManager::textures.begin());
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    score = 0;
    cnt = 0;
    maper = nullptr;

    SDL_Quit();
}

