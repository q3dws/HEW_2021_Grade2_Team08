#pragma once
#ifndef EARMOR_H
#define EARMOR_H
#include "Skill.h"
class EArmor :
    public Skill
{
    class AnimSpriteComponent* armor_asc_;
    class Actor* temp_;
    class AnimSpriteComponent* effect_asc_;

    int     armor_state_;            //�A�[�}�[�̏��
    float   motioncount_;             //�A�[�}�[�̓o��/�ޏ�A�j���̏I��鎞�Ԃ𐔂���
    int     deathcount;            //�������ʂ̐��𐔂���

    int     armor_life_;        //�A�[�}�[�̃��C�t�|�C���g

    const int k_effect_tex;
    const int k_armor_efect_time;                   //�A�[�}�[����i�K��������܂ł̎���
    const int k_armor_tex_[5];                       //�A�[�}�[�̃e�N�X�`��
    const Vec2 k_armor_pos_;                         //�A�[�}�[�̃v���C���[����̑��ΓI�Ȉʒu
    const Vec2 k_armor_size_;                      //�A�[�}�[�̑傫��
    const Vec2 k_armor_hitsize_;                    //�A�[�}�[�̓����蔻��̑傫��
    const bool k_Is_player_;
    const int sounds_[2];

    class Enemy *enemy_;
    enum class armor_frame_num : int
    {
        ADVENT = 4,
        LIFE3 = 1,     //
        LIFE2 = 1,
        LIFE1 = 1,
        LEAVE = 4,
    };

    enum class armor_Motion :int
    {
        ADVENT,     //�o��
        LIFE3,     //
        LIFE2,
        LIFE1,
        LEAVE,      //�ޏ�
    };


public:
    EArmor(Game* game, Vec2 pos, class Enemy* player, Vec2 player_hitsize);
    ~EArmor();
    void UpdateActor(float deltatime) override;
    void Armor_death_check(float deltatime);
    void Armor_texchange(int texnum);
    bool Get_Isplayer();
    void Set_Armorhit(int power);
    void SetDead();
};
#endif // !EARMOR_H