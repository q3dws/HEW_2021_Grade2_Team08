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

    Vec2 scoop_pos_;                                //�����������̉�ʏ�̍��W
    const Vec2 k_scoop_pos_init_;           //�����������J�n�ʒu
    Vec2 k_scoop_distination_;                    //���e�_
    const int k_scoop_tex_;                       //�����������̃e�N�X�`��
    const float k_scoop_g_;                     //�d�͉����x
    const int k_scoop_layer_;                   //�������Ȃ��̕`��D��x
    const Vec2 k_scoop_size_; //�����������̑傫��

    int scoop_stage_num_;           //���e�_�̃}�X��
    const float k_scoop_deg_;               //�����������̊p�x
    const bool k_Is_player_;
    class Stage* stg_;
    const int k_scoop_SE_;
};
#endif // !ESCOOP_H