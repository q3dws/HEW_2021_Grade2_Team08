#pragma once
#ifndef ANIMATIONTESTOBJ_H
#define ANIMATIONTESTOBJ_H

#include "Actor.h"
#include "Game.h"
class AnimationTestObj : public Actor
{
public:
    AnimationTestObj(class Game* game);
    void UpdateActor(float deltatime) override;
private:
    
};
#endif // !ANIMATIONTESTOBJ_H
