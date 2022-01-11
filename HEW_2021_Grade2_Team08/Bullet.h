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
    Bullet(class Game* game, int tex, bool Is_player, Vec2 pos);
    ~Bullet();
    void UpdateActor(float delta_time) override;
    void Bullet_ColligionCheck(float  delta_taime);
private:
    bool Is_player_;

    const Vec2 snow_pos_;
    const float snow_vel_; //雪の速さ
    const int k_damagetime_;  //ダメージモーションの持続時間
};
#endif // !BULLET_H



