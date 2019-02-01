#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS.h"
#include "SDL2/SDL_ttf.h"

class AssetManager{
public:
    AssetManager(Manager *man);
    ~AssetManager(){}
    //game objects
    void CreateProjectile(Vector2D pos,Vector2D vel,int width, int height, int range,int nFrame,int nSpeed,std::string type, std::string id,SDL_Renderer *renderer, AssetManager *mainAssets);

    //texture management
    void AddTexture(std::string id, const char* path, SDL_Renderer *renderer);
    SDL_Texture* GetTexture(std::string id);
    static std::map<std::string,SDL_Texture*> textures;
    static std::map<std::string, TTF_Font*> fonts;

    void AddFont(std::string id, std::string path, int fSize);
    TTF_Font* GetFont(std::string id);

    enum groupLabels : std::size_t{
        groupMap,
        groupPlayers,
        groupColliders,
        groupProjectiles
    };


private:
    Manager *manager;
};
