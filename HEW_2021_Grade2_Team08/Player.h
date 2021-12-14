#pragma once
#ifndef PLAYER_H
#define PLAYER_H
/*
    �쐬�ҁ@�N������
    �쐬�� 2021/11/07
*/


#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"

#include "SnowCost.h"

class Bullet;
class Golem;

class Player : public Actor
{
protected: 
    Vec2 player_pos_;          //�v���C���[�̉�ʏ�̍��W
    int player_snow_;                     //�v���C���[�̌��ݎ����Ă����
    int     player_pos_num_;                    //�v���C���[�̂���}�X�̔ԍ�
    /*
    012
    345 ���ꂼ��̐������}�X�̔ԍ��ɑΉ�
    678
    */
    //class Stage* pstage;
  
    int bullettex_;                              //�e�̃e�N�X�`��
    std::vector<class Bullet*> bullets_; //�e�̃I�u�W�F�N�g����铮�I�z��
    
    std::vector<class Golem*> golems_; //�S�[�����̃I�u�W�F�N�g����铮�I�z��
    class SnowCost* snowcost_;                        //�����Ă����̐���\������I�u�W�F�N�g�����

    class AnimSpriteComponent* asc_;    
    int     player_mode_;                          //�v���C���[�̃X�e�[�g(Player�����Ŋ��������)
    float idlecount_;                                //�ҋ@��Ԃɓ���܂ł̃^�C�}�[
    int     idle_timeto_;                           //timeto�܂Ő�����Ƒҋ@��ԂɂȂ�

    int     player_layer_;                           //�v���C���[�̕`��̗D��x
    const int k_player_layer_var;           //�v���C���[�̕`��̗D��x�̕ω���

    const int k_player_snow_max_;     //�v���C���[�̎��Ă��̏��
    const int k_player_snow_min_ ;     //�v���C���[�̎��Ă��̉���

    const Vec2 k_player_pos_center_;      //9�}�X�̐^�񒆂̍��W
    const Vec2 k_player_pos_var_;          //�{�^�����������Ƃ��̃v���C���[�̈ړ��ʁ@
    const Vec2 k_player_vel_;          //�v���C���[�̈ړ����x
    const Vec2 k_player_size_;                      //�v���C���[�L�����̑傫��

    //�L�����̉摜�̔ԍ����X�e�[�g�𓯎��ɕ\���񋓌^
    enum class PlayerMotion :int
    {
        IDLE,                   //�ҋ@
        ATTACK,             //�U��
        MOVE_FRONT,     //�O�ړ�
        MOVE_BACK,      //���ړ�
        MOVE_UPANDDOWN,     //�㉺�ړ� 

        COLLECT_IN,     //��W�ߊJ�n
        COLLECT_LOOP,   //��W�ߒ�
        COLLECT_OUT,       //��W�ߏI��
        USE_SKILL,          //�X�L���g�p��
    };

    StateContext<Player>* pplayer_state_context_;
    Stage* stg_;

    
public:

    Player(class Game* game, Stage* stg ,Vec2 size, Vec2 center);
    virtual ~Player();
    void UpdateActor(float deltatime) override;

    void Player_move(float deltatime);
    void Player_snow_collect();
    void Player_snow_throw(float deltatime);
    void Player_idlecheck(float deltatime);
    void Player_useskill(void);
    int Player_getsnow(void);
    virtual void Player_UniqueSkill(void) = 0;
    virtual void Player_texchange(int texnum) = 0;
    //void Player_Draw(int mode);
};
#endif // PLAYER_H

