#pragma once
#ifndef EBIGBULLET_H
#define EBIGBULLET_H

#include "Skill.h"
class EBigBullet :
    public Skill
{
public:
    EBigBullet(class Game* game, Vec2 pos, int layer);
    ~EBigBullet();
    void UpdateActor(float delta_time) override;
    void BigBullet_move(float delta_time);
private:
    class SpriteComponent* bigsnow_asc_;
    const int k_bigsnow_tex_;                       //大玉のテクスチャ
    const float k_bigsnow_vel_;                     //大玉の速さ
    const Vec2 k_bigsnow_Grow;                 //大玉の大きくなる速度
    const float k_bigsnow_Growrot_;             //大玉の回転速度
    const int k_bigsnow_layer_;
    Vec2 bigsnow_size_; //大玉の大きさ
    Vec2 bigsnow_pos_;
    const bool k_Is_player_;
    float bigsnow_rot_;                   //大玉の回転角
    int bigsnow_power_;                 //ヒット時の威力
    float bigsnow_distance_count_;  //移動距離を数える
    const int sounds_[2];
};
#endif // !EBIGBULLET_H