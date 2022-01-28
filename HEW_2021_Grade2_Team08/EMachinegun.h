#pragma once
#ifndef EMACHINGUN_H
#define EMACHINEGUN_H
#include "Skill.h"
class EMachinegun :
    public Skill
{
public:
    EMachinegun(Game* game, Vec2 pos, int bullettex, int bulletnum);
    ~EMachinegun() {}
    void UpdateActor(float delta_time) override;
    bool Is_MGEnd();
private:
    const bool  k_Is_player_;
    Vec2        machinegun_pos_;       //�e���o��ʒu
    const int   k_bullettex_;                     //�e�̃e�N�X�`��
    const int   k_bulletnum_;                 //�e�̐�
    const float k_machinegun_ver_;        //�e�̏o��Ԋu
    const float k_machinegun_power_;    //�e�̏o��ʂ̔{��
    const int   k_machingun_Lowestline_;  //�ʂ�������Œ�l
    float       machinegun_counttime_;          //�e�̏o�鎞�Ԃ𐔂���
    float       machinegun_countbullet_;        //�o�����e�𐔂���
    bool        mg_out_;
    const int sounds_[3];
};
#endif // !EMACHINGUN_H