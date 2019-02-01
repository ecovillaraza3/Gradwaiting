#ifndef GAME_H
#define GAME_H
#pragma once
#include "Game.h"
#include "SDL2/SDL.h"

class ColliderComponent;

class Collision{
public:
    Collision();
    ~Collision();

    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
    static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);

    static bool XXYY(const SDL_Rect& recA, const SDL_Rect& recB);
    static bool CollisionForSlide(const ColliderComponent& colA, const ColliderComponent& colB);

    static int yD;
private:
};

#endif
