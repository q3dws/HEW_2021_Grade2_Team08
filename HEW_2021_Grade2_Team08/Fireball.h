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
    class SpriteComponent* fireball_asc_;

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
    Stage* stg_;
};


