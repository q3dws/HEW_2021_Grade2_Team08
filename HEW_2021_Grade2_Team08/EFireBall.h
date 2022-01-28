#pragma once
#ifndef EFIREBALL_H
#define EFIREBALL_H

#include "Skill.h"

class EFireBall :
    public Skill
{
public:
    EFireBall(class Game* game, int layer, Vec2 pos, class Enemy* player, class Stage* stg);
    ~EFireBall();
    void UpdateActor(float delta_time) override;
    void Fireball_parabola(float delta_time);
    void Fireball_exprosion();
private:
    class AnimSpriteComponent* fireball_asc_;

    Vec2 fireball_pos_;                                //火の玉の画面上の座標
    const Vec2 k_fireball_pos_init_;           //火の玉開始位置
    Vec2 k_fireball_distination_;                    //着弾点
    const int k_fireball_tex_;                       //火の玉のテクスチャ
    const float k_fireball_g_;                     //重力加速度
    const int k_fireball_layer_;                   //火の玉の描画優先度
    const Vec2 k_fireball_size_; //火の玉の大きさ

    const float k_fireball_deg_;               //火の玉の開始角度

    const bool k_Is_player_;

    float       fireball_stage_num_;                     //溶かすマスの番号

    float     attackcount_;                //火の玉の登場するまでの時間を数える    
    float     k_fireball_delay_;                //火の玉の登場するまでのコマ数    

    class Stage* stg_;

    enum class fireball_frame_num : int
    {
        IDLE = 4,
        
    };

    const int k_fireball_SE_[3];
    bool fireball_atk_affirmation;          //火の玉が画面内に出現しているかどうか
    enum class fireball_SE_num :int
    {
        ADVENT,     //登場
        ATTACK,     //射撃音
        LEAVE,      //退場
    };
};
#endif // !EFIREBALL_H