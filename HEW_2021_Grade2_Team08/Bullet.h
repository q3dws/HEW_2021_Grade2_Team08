#pragma once
#ifndef BULLET_H
#define BULLET_H
#include "Actor.h"
#include "Game.h"

/*
    �쐬�ҁ@�N������
    �쐬�� 2021/11/07
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

    const float snow_vel_; //��̑���
};
#endif // !BULLET_H



