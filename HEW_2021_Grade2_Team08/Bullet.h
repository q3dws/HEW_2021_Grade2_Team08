#pragma once
#ifndef BULLET_H
#define BULLET_H
#include "Actor.h"
#include "Game.h"

/*
    ì¬Ò@ŒN“‡’©“ú
    ì¬“ú 2021/11/07
*/

class Bullet :
    public Actor
{
public:
    Bullet(class Game* game, int tex, bool Is_player);
    ~Bullet();
    void UpdateActor(float delta_time) override;
private:
    bool Is_player_;

    const float snow_vel_; //á‚Ì‘¬‚³
};
#endif // !BULLET_H



