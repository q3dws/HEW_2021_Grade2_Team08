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
#include "ScoreManager.h"
class Bullet;

class Player : public Actor
{
private: 
    D3DXVECTOR2 player_pos_;          //�v���C���[�̉�ʏ�̍��W
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
  
    class AnimSpriteComponent* asc_[2];
    int     texbuffer_;                              //asc_�̓Y����
    float idlecount_;                                //�ҋ@��Ԃɓ���܂ł̃^�C�}�[

    const int k_player_snow_max_;     //�v���C���[�̎��Ă��̏��
    const int k_player_snow_min_ ;     //�v���C���[�̎��Ă��̉���

    const D3DXVECTOR2 k_player_pos_center_;      //9�}�X�̐^�񒆂̍��W
    const D3DXVECTOR2 k_player_pos_var_;          //�{�^�����������Ƃ��̃v���C���[�̈ړ��ʁ@
    const D3DXVECTOR2 k_player_vel_;          //�v���C���[�̈ړ����x
    const Vec2 k_player_size_;                      //�v���C���[�L�����̑傫��

    const int k_charaA_[2];                          //�L�����N�^�[A�̃e�N�X�`�� 0:�ҋ@ 1:�U��
    enum class PlayerMotion :int
    {
        IDLE,
        ATTACK,
    };

    StateContext<Player>* pplayer_state_context_;
    Stage* stg_;

    
public:
    Player(class Game* game, Stage* stg);
    
    void UpdateActor(float deltatime) override;

    void Player_move(float deltatime);
    void Player_snow_collect();
    void Player_snow_throw(float deltatime);
    void Player_idlecheck(float deltatime);
    void Player_texchange(int texnum);

    ScoreManager* p_ScoreManager;

    
};
#endif // PLAYER_H

