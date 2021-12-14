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
    Scoop(class Game* game, int layer, Vec2 pos);
    ~Scoop();
    void UpdateActor(float delta_time) override;
    void Scoop_parabola(float delta_time);
    void Scoop_exprosion();
private:
    class SpriteComponent* scoop_asc_;

    Vec2 scoop_pos_;                                //�����������̉�ʏ�̍��W
    const Vec2 k_scoop_pos_init_;           //�����������J�n�ʒu
    Vec2 scoop_distination_;                    //���e�_
    const int k_scoop_tex_;                       //�����������̃e�N�X�`��
    const Vec2 k_scoop_vel_;                     //�����������̑���
    const float k_scoop_g_;                     //�d�͉����x
    const int k_scoop_layer_;                   //�������Ȃ��̕`��D��x
    //const Vec2 k_bigsnow_Grow;                 //��ʂ̑傫���Ȃ鑬�x
    const Vec2 k_scoop_size_; //�����������̑傫��
};

class MiniBullet :
    public Actor
{
public:
    MiniBullet(class Game* game, int tex, Vec2 pos, bool up);
    ~MiniBullet();
    void UpdateActor(float delta_time) override;
private:
    bool up_; //��ɔ�Ԃ��ǂ���
    const float snow_vel_; //��̑���
};