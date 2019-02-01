#include "Collision.h"
#include "ColliderComponent.h"
#include <stdio.h>

int Collision::yD;

Collision::Collision(){
    yD = 35;
}

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB){
    if(
       recA.x + recA.w > recB.x+35 &&
       recA.y + recA.h > recB.y+35 &&
       recB.x + recB.w > recA.x+35 &&
       recB.y + recB.h > recA.y+35
       ){
           return true;
       }
       return false;
}

bool Collision::XXYY(const SDL_Rect& recA, const SDL_Rect& recB){
    if(
       recA.x + recA.w > recB.x+90 &&
       recA.y + recA.h > recB.y+yD &&
       recB.x + recB.w > recA.x+90 &&
       recB.y + recB.h > recA.y+yD
       ){
           return true;
       }
       return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB){
    if(AABB(colA.collider, colB.collider)){
        std::cout<<colA.tag<< "hit:" << colB.tag <<std::endl;
        return true;
    }else{
        return false;
    }

}

bool Collision::CollisionForSlide(const ColliderComponent& colA, const ColliderComponent& colB){
    if(XXYY(colA.collider, colB.collider)){
        std::cout<<colA.tag<< "hit:" << colB.tag <<std::endl;
        return true;
    }else{
        return false;
    }

}
