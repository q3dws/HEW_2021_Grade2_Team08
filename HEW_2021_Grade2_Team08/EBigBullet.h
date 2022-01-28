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
    const int k_bigsnow_tex_;                       //��ʂ̃e�N�X�`��
    const float k_bigsnow_vel_;                     //��ʂ̑���
    const Vec2 k_bigsnow_Grow;                 //��ʂ̑傫���Ȃ鑬�x
    const float k_bigsnow_Growrot_;             //��ʂ̉�]���x
    const int k_bigsnow_layer_;
    Vec2 bigsnow_size_; //��ʂ̑傫��
    Vec2 bigsnow_pos_;
    const bool k_Is_player_;
    float bigsnow_rot_;                   //��ʂ̉�]�p
    int bigsnow_power_;                 //�q�b�g���̈З�
    float bigsnow_distance_count_;  //�ړ������𐔂���
    const int sounds_[2];
};
#endif // !EBIGBULLET_H