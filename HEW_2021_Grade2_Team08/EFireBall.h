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

    Vec2 fireball_pos_;                                //�΂̋ʂ̉�ʏ�̍��W
    const Vec2 k_fireball_pos_init_;           //�΂̋ʊJ�n�ʒu
    Vec2 k_fireball_distination_;                    //���e�_
    const int k_fireball_tex_;                       //�΂̋ʂ̃e�N�X�`��
    const float k_fireball_g_;                     //�d�͉����x
    const int k_fireball_layer_;                   //�΂̋ʂ̕`��D��x
    const Vec2 k_fireball_size_; //�΂̋ʂ̑傫��

    const float k_fireball_deg_;               //�΂̋ʂ̊J�n�p�x

    const bool k_Is_player_;

    float       fireball_stage_num_;                     //�n�����}�X�̔ԍ�

    float     attackcount_;                //�΂̋ʂ̓o�ꂷ��܂ł̎��Ԃ𐔂���    
    float     k_fireball_delay_;                //�΂̋ʂ̓o�ꂷ��܂ł̃R�}��    

    class Stage* stg_;

    enum class fireball_frame_num : int
    {
        IDLE = 4,
        
    };

    const int k_fireball_SE_[3];
    bool fireball_atk_affirmation;          //�΂̋ʂ���ʓ��ɏo�����Ă��邩�ǂ���
    enum class fireball_SE_num :int
    {
        ADVENT,     //�o��
        ATTACK,     //�ˌ���
        LEAVE,      //�ޏ�
    };
};
#endif // !EFIREBALL_H