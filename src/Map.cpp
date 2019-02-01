#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS.h"
#include "Components.h"



Map::Map(std::string tID, int ms, int ts, std::string managerID) : texID(tID), mapScale(ms), tileSize(ts)
{
    scaledSize = ms * ts;
    idManager = managerID;
}


Map::~Map(){

}

void Map::LoadMap(std::string path, int sizeX, int sizeY, SDL_Renderer *renderer, AssetManager *assets){
    char c;
    std::fstream mapFile;
    mapFile.open(path);
    mapAssets = assets;

    int srcX, srcY;

    for(int y = 0; y < sizeY; y++){
        for(int x=0; x < sizeX; x++){
            mapFile.get(c);
            srcY = atoi(&c) *tileSize;
            mapFile.get(c);
            srcX = atoi(&c) *tileSize;
            AddTile(srcX,srcY,x*scaledSize, y*scaledSize,renderer);
            mapFile.ignore();
        }
    }

    mapFile.ignore();

    for(int y=0; y < sizeY; y++){
        for(int x=0; x < sizeX; x++){
            mapFile.get(c);
            if(c=='1'){
                if(idManager == "endless"){
                    auto& tool(manager.addEntity());
                    tool.addComponent<ColliderComponent>("terrain" , x * scaledSize, y * scaledSize, scaledSize );
                    tool.addGroup(AssetManager::groupColliders);
                }else if(idManager == "elementary"){
                    auto& tool(elemManager.addEntity());
                    tool.addComponent<ColliderComponent>("terrain" , x * scaledSize, y * scaledSize, scaledSize );
                    tool.addGroup(AssetManager::groupColliders);
                }else if(idManager == "highschool"){
                    auto& tool(highManager.addEntity());
                    tool.addComponent<ColliderComponent>("terrain" , x * scaledSize, y * scaledSize, scaledSize );
                    tool.addGroup(AssetManager::groupColliders);
                }else if(idManager == "college"){
                    auto& tool(collManager.addEntity());
                    tool.addComponent<ColliderComponent>("terrain" , x * scaledSize, y * scaledSize, scaledSize );
                    tool.addGroup(AssetManager::groupColliders);
                }


            }
            mapFile.ignore();

        }
    }

    mapFile.close();
}


void  Map::AddTile(int srcX, int srcY, int xpos, int ypos, SDL_Renderer *renderer){
    if(idManager == "endless"){
        auto &tile(manager.addEntity());
        tile.addComponent<TileComponent>(renderer, srcX, srcY, xpos, ypos,tileSize, mapScale, texID,mapAssets);
        tile.addGroup(AssetManager::groupMap);
    }else if(idManager == "elementary"){
        auto &tile(elemManager.addEntity());
        tile.addComponent<TileComponent>(renderer, srcX, srcY, xpos, ypos,tileSize, mapScale, texID,mapAssets);
        tile.addGroup(AssetManager::groupMap);
    }else if(idManager == "highschool"){
        auto &tile(highManager.addEntity());
        tile.addComponent<TileComponent>(renderer, srcX, srcY, xpos, ypos,tileSize, mapScale, texID,mapAssets);
        tile.addGroup(AssetManager::groupMap);
    }else if(idManager == "college"){
        auto &tile(collManager.addEntity());
        tile.addComponent<TileComponent>(renderer, srcX, srcY, xpos, ypos,tileSize, mapScale, texID,mapAssets);
        tile.addGroup(AssetManager::groupMap);
    }
}

