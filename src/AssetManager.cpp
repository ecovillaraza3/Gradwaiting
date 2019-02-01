#include "AssetManager.h"
#include "Components.h"


AssetManager::AssetManager(Manager *man) : manager(man)
{

}

std::map<std::string,SDL_Texture*> AssetManager::textures;
std::map<std::string, TTF_Font*> AssetManager::fonts;

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel,int width,int heigth, int range, int speed, int nFrame,std::string type ,std::string id,SDL_Renderer *renderer, AssetManager *mainAssets){

        if(type == "flagDesign"){
            auto& projectile(manager->addEntity());
            projectile.addComponent<TransformComponent>(pos.x,pos.y,width,heigth,6);
            projectile.addComponent<SpriteComponent>(id,true,nFrame,500,renderer,mainAssets);
            projectile.addComponent<ProjectileComponent>(range,speed,vel);
            projectile.addComponent<ColliderComponent>(type);
            projectile.addGroup(groupMap);
        }

        if(type == "windowDesign"){
            auto& projectile(manager->addEntity());
            projectile.addComponent<TransformComponent>(pos.x,pos.y,width,heigth,10);
            projectile.addComponent<SpriteComponent>(id,true,nFrame,500,renderer,mainAssets);
            projectile.addComponent<ProjectileComponent>(range,speed,vel);
            projectile.addComponent<ColliderComponent>(type);
            projectile.addGroup(groupMap);
        }

        if(type == "sign"){
            auto& projectile(manager->addEntity());
            projectile.addComponent<TransformComponent>(pos.x,pos.y,width,heigth,3);
            projectile.addComponent<SpriteComponent>(id,true,nFrame,50,renderer,mainAssets);
            projectile.addComponent<ProjectileComponent>(range,speed,vel);
            projectile.addComponent<ColliderComponent>(type);
            projectile.addGroup(groupMap);
        }

        if(type == "doorDesign"){
            auto& projectile(manager->addEntity());
            projectile.addComponent<TransformComponent>(pos.x,pos.y,width,heigth,10);
            projectile.addComponent<SpriteComponent>(id,true,nFrame,500,renderer,mainAssets);
            projectile.addComponent<ProjectileComponent>(range,speed,vel);
            projectile.addComponent<ColliderComponent>(type);
            projectile.addGroup(groupMap);

        }

        if(type == "computerDesign"){
            auto& projectile(manager->addEntity());
            projectile.addComponent<TransformComponent>(pos.x,pos.y,width,heigth,5);
            projectile.addComponent<SpriteComponent>(id,true,nFrame,500,renderer,mainAssets);
            projectile.addComponent<ProjectileComponent>(range,speed,vel);
            projectile.addComponent<ColliderComponent>(type);
            projectile.addGroup(groupMap);

        }


        if(type == "kalatSaLapag"){
            auto& projectile(manager->addEntity());
            projectile.addComponent<TransformComponent>(pos.x,pos.y,width,heigth,2);
            projectile.addComponent<SpriteComponent>(id,true,nFrame,speed,renderer,mainAssets);
            projectile.addComponent<ProjectileComponent>(range,speed,vel);
            projectile.addComponent<ColliderComponent>(type);
            projectile.addGroup(groupMap);
        }


        if(type == "projectiles"){
            auto& projectile(manager->addEntity());
            projectile.addComponent<TransformComponent>(pos.x,pos.y,width,heigth,3);
            projectile.addComponent<SpriteComponent>(id,true,nFrame,50,renderer,mainAssets);
            projectile.addComponent<ProjectileComponent>(range,speed,vel);
            projectile.addComponent<ColliderComponent>(type);
            projectile.addGroup(groupProjectiles);
        }


}




void AssetManager::AddTexture(std::string id, const char* path, SDL_Renderer *renderer){
    textures.emplace(id, TextureManager::LoadTexture(path,renderer));
}

SDL_Texture* AssetManager::GetTexture(std::string id){
    return textures[id];
}


void AssetManager::AddFont(std::string id, std::string path, int fSize){
    fonts.emplace(id, TTF_OpenFont(path.c_str(),fSize));

}
TTF_Font* AssetManager::GetFont(std::string id){
    return fonts[id];
}
