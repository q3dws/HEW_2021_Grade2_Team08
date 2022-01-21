#pragma once
#include "Skill.h"
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"

//�X�L����ʂ̃N���X
//�쐬�ҁ@�N������
// �쐬���@2021/12/12
//

class BigBullet :
    public Skill
{
public:
    BigBullet(class Game* game, bool Is_player, int layer, Vec2 pos);
    ~BigBullet();
    void UpdateActor(float delta_time) override;
    void BigBullet_move(float delta_time);

    void BigBullet_ColligionCheck(float  delta_taime);
    void BigBullet_texchange(int texnum);

private:
    class AnimSpriteComponent* bigsnow_asc_;
    const int k_bigsnow_tex_[2];                       //��ʂ̃e�N�X�`��
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

    int bigsnow_state_;
    float motioncount_;

    enum class bigsnow_frame_num : int
    {
        IDLE = 1,
        LEAVE = 2,

    };

    enum class bigsnow_Motion :int
    {
        IDLE,     //�ʏ�
        LEAVE,      //�ޏ�
    };
};

