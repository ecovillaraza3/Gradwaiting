#pragma once

#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"

class ProjectileComponent : public Component{

public:
    ProjectileComponent(int rng, int sp, Vector2D vel): range(rng),speed(sp), velocity(vel){
        range = 450;
    }

    ~ProjectileComponent(){}

    void init()override{
        transformComponent = &entity->getComponent<TransformComponent>();
        transformComponent-> velocity = velocity;

    }

    void update() override{
        distance += speed;

        if(distance > range){
            std::cout<<"Clear : Chunk deleted"<<std::endl;
            entity -> destroy();
        }



    }

private:

    TransformComponent* transformComponent;

    int range = 0;
    int speed = 0;
    int distance = 0;
    Vector2D velocity;
};
