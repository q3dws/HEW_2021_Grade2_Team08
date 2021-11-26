#pragma once
#ifndef BULLET_H
#define BULLET_H
#include "Actor.h"
#include "Game.h"

/*
    作成者　君島朝日
    作成日 2021/11/07
*/

class Bullet :
    public Actor
{
public:
    Bullet(class Game* game, int tex);
    ~Bullet();
    void UpdateActor(float delta_time) override;
private:
    float death_timer;

    const float snow_vel_; //雪の速さ
};
#endif // !BULLET_H



