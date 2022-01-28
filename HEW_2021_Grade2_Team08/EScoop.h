#pragma once
#ifndef ESCOOP_H
#define ESCOOP_H

#include "Skill.h"
#include "Scoop.h"
class EScoop :
    public Skill
{
public:
    EScoop(class Game* game, int layer, Vec2 pos, class Stage* stg, class Enemy* player);
    ~EScoop();
    void UpdateActor(float delta_time) override;
    void Scoop_parabola(float delta_time);
    void Scoop_exprosion();
    void Scoop_summon_icepiller();
private:
    class SpriteComponent* scoop_asc_;

    Vec2 scoop_pos_;                                //すくい投げの画面上の座標
    const Vec2 k_scoop_pos_init_;           //すくい投げ開始位置
    Vec2 k_scoop_distination_;                    //着弾点
    const int k_scoop_tex_;                       //すくい投げのテクスチャ
    const float k_scoop_g_;                     //重力加速度
    const int k_scoop_layer_;                   //すくいなげの描画優先度
    const Vec2 k_scoop_size_; //すくい投げの大きさ

    int scoop_stage_num_;           //着弾点のマス目
    const float k_scoop_deg_;               //すくい投げの角度
    const bool k_Is_player_;
    class Stage* stg_;
    const int k_scoop_SE_;
};
#endif // !ESCOOP_H