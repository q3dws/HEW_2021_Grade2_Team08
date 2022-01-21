#pragma once
#include "Skill.h"
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"
#include "Player.h"
#include "Stage.h"

class Fireball :
    public Skill
{
public:
    Fireball(class Game* game, int layer, Vec2 pos, Player* player, Stage* stg, bool Is_player);
    ~Fireball();
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

    Stage* stg_;

    enum class fireball_frame_num : int
    {
        IDLE = 4,
        
    };
};


//�Β��̃N���X
class Firepillar :
    public Actor
{
public:
    Firepillar(class Game* game, int stage_num, bool is_player, Stage* stg, int layer);
    ~Firepillar();
    void UpdateActor(float delta_time) override;
    void Firepillar_ColligionCheck(float  delta_taime);
private:
    class AnimSpriteComponent* firepillar_asc_;

    const Vec2 k_firepillar_size_;
    const Vec2 k_firepillar_pos_;
    const int k_firepillar_tex_;                       //�Β��̃e�N�X�`��
    const bool k_Is_player_;
    const int k_firepillar_time_;                   //�Β��̎�������
    const int       k_firepillar_stage_num_;                     //�n�����}�X�̔ԍ�

    float deadcount_;                               //���ʂ܂ł̎��Ԃ𐔂���
    Stage* stg_;

    const int k_firepillar_power_;
    bool hitstate_;                                     //true���ƂȂɂ��Ƀq�b�g���Ă���

    enum class firepillar_frame_num : int
    {
        IDLE = 8,

    };
};

