#pragma once
#ifndef TESTBULLET_H
#define TESTBULLET_H
#include "Actor.h"
#include "Game.h"
class TestBullet :
    public Actor
{
public:
    TestBullet(class Game* game);
    void UpdateActor(float delta_time) override;
private:
    float death_timer;
};
#endif // !TESTBULLET_H


