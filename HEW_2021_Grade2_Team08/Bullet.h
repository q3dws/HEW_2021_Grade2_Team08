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

    void Bullet_texchange(int texnum);

private:
    bool Is_player_;

    const Vec2 snow_pos_;
    const float snow_vel_; //雪の速さ
    const int k_damagetime_;  //ダメージモーションの持続時間

    const int k_bullet_tex_[2];                       //壁のテクスチャ
    int bullet_state_;
    class AnimSpriteComponent* bullet_asc_;
    const Vec2 snow_size_;
    float motioncount_;

    enum class bullet_frame_num : int
    {
        IDLE = 1,
        LEAVE = 2,
       
    };
    enum class bullet_Motion :int
    {
        IDLE,     //通常
        LEAVE,      //退場
    };

};
#endif // !BULLET_H



