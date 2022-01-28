#pragma once
#include "Skill.h"
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"

//�X�L�������������̃N���X
//�쐬�ҁ@�N������
// �쐬���@2021/12/13
//

class Scoop :
    public Skill
{
public:
    Scoop(class Game* game, int layer, Vec2 pos, bool Is_player, Stage* stg, Player*player);
    ~Scoop();
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
    Stage* stg_;
    const int k_scoop_SE_;
};

class MiniBullet :
    public Actor
{
public:
    MiniBullet(class Game* game, int tex, Vec2 pos, bool up, bool is_player);
    ~MiniBullet();
    void UpdateActor(float delta_time) override;
private:
    bool up_; //��ɔ�Ԃ��ǂ���
    const float snow_vel_; //��̑���
    bool k_Is_player_;
    int k_damagetime_;
   
};

//---------------------------------------------------------------
//�X���̃N���X
//---------------------------------------------------------------
class Icepillar :
    public Actor
{
public:
    Icepillar(class Game* game, int stage_num, bool is_player, Stage* stg, int layer);
    ~Icepillar();
    void UpdateActor(float delta_time) override;
    void Icepillar_ColligionCheck(float  delta_taime);
private:
    class AnimSpriteComponent* icepillar_asc_;

    const Vec2 k_icepillar_size_;
    const Vec2 k_icepillar_pos_;
    const int k_icepillar_tex_;                       //�Β��̃e�N�X�`��
    const bool k_Is_player_;
    const int k_icepillar_time_;                   //�Β��̎�������
    const int       k_icepillar_stage_num_;                     //�n�����}�X�̔ԍ�


    float deadcount_;                               //���ʂ܂ł̎��Ԃ𐔂���
    Stage* stg_;

    const int k_icepillar_power_;
    bool hitstate_;                                     //true���ƂȂɂ��Ƀq�b�g���Ă���

    enum class icepillar_frame_num : int
    {
        IDLE = 8,

    };
};
