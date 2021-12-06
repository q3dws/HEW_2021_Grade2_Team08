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

class Bullet;

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
    //int * a[12]
  
    class AnimSpriteComponent* asc_;    
    int     player_mode_;                          //�v���C���[�̃X�e�[�g(Player�����Ŋ��������)
    float idlecount_;                                //�ҋ@��Ԃɓ���܂ł̃^�C�}�[
    int     idle_timeto_;                           //timeto�܂Ő�����Ƒҋ@��ԂɂȂ�

    const int k_player_snow_max_;     //�v���C���[�̎��Ă��̏��
    const int k_player_snow_min_ ;     //�v���C���[�̎��Ă��̉���

    const Vec2 k_player_pos_center_;      //9�}�X�̐^�񒆂̍��W
    const Vec2 k_player_pos_var_;          //�{�^�����������Ƃ��̃v���C���[�̈ړ��ʁ@
    const Vec2 k_player_vel_;          //�v���C���[�̈ړ����x
    const Vec2 k_player_size_;                      //�v���C���[�L�����̑傫��

    enum class PlayerMotion :int
    {
        IDLE,                   //�ҋ@
        ATTACK,             //�U��
        MOVE_FRONT,     //�O�ړ�
        MOVE_BACK,      //���ړ�
        COLLECT_IN,     //��W�ߊJ�n
        COLLECT_LOOP,   //��W�ߒ�
        COLLECT_OUT,       //��W�ߏI��
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
    virtual void Player_texchange(int texnum) = 0;
    //void Player_Draw(int mode);
};
#endif // PLAYER_H

