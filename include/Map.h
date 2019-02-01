#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "AssetManager.h"

extern Manager manager;
extern Manager elemManager;
extern Manager highManager;
extern Manager collManager;

class Map
{
    public:
        Map(std::string tID, int ms, int ts, std::string managerID);

         ~Map();

         void LoadMap(std::string path, int sizeX, int sizeY, SDL_Renderer *renderer,AssetManager *assets);
         void AddTile(int srcX, int srcY, int xpos, int ypos, SDL_Renderer *renderer);

    private:
        std::string texID;
        std::string idManager;
        int mapScale;
        int tileSize;
        int scaledSize;
        AssetManager *mapAssets;

};
