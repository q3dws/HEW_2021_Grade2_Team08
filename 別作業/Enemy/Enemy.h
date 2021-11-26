#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "Actor.h"
#include "Game.h"
#include <vector>

class  Enemy : public Actor
{
private:
    D3DXVECTOR2 enemy_pos_;          //��ʏ�̍��W
    int     enemy_snow_;                     //���ݎ����Ă����
    int     enemy_pos_num_;   

    //�v���C���[�̂���}�X�̔ԍ�
    /*
    012
    345 ���ꂼ��̐������}�X�̔ԍ��ɑΉ�
    678
    */
    int     enemy_direction_;   //����
    int     enemy_hp_;
    //class Stage* pstage;

    int bullettex_;                              //�e�̃e�N�X�`��
    std::vector<class Bullet*> bullets_; //�e�̃I�u�W�F�N�g����铮�I�z��

    const int enemy_snow_max_;     //���Ă��̏��
    const int enemy_snow_min_;     //���Ă��̉���

    const D3DXVECTOR2 enemy_pos_center_;      //9�}�X�̐^�񒆂̍��W
    const D3DXVECTOR2 enemy_pos_var_;          //�ړ��ʁ@
    const D3DXVECTOR2 enemy_vel_;          //�ړ����x

    StateContext<Enemy>* penemy_state_context_;

public:
    Enemy(class Game* game);


    void UpdateActor(float deltatime) override;
    bool UpdateTimer(int ms);

    void enemy_move();
    void enemy_snow_collect();
    //void enemy_snow_throw();

    //enemy() : enemy_snow_max_(16){}
};
#endif // enemy_H