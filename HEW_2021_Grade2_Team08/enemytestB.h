#pragma once

#pragma once
#include "Player.h"


class EnemytestB :
    public Player
{
private:
    const int k_enemyB_[8];                          //�L�����N�^�[B�̃e�N�X�`��������z��
    enum class enemyB_frame_num : int       //�A�j���[�V�����̃R�}��
    {
        IDLE = 8,
        ATTACK = 8,
        MOVE_FRONT = 1,
        MOVE_BACK = 1,
        COLLECT_IN = 5,
        COLLECT_LOOP = 3,
        COLLECT_OUT = 5,
    };

public:
    //Player.cpp��k_player_size�ɑ�����Ă���Vec2�𗼕��Ƃ��}�C�i�X�ɂ��ď㉺���]�����Đ������\�����Ă��܂�
    //k_player_center�̈ʒu���Y�������ƂőS�̂̈ʒu���ړ����Ă��܂�
    //back��flont�̉摜��CharaB�������ւ��Ă��܂�
    EnemytestB(class Game* game, Stage* stg, bool Is_player)
        : Player(game, stg, Vec2(64 * 2.5, 64 * 2.5), Vec2(325, 246 + 33), Is_player)
        , k_enemyB_
    {

         LoadTexture(L"Data/Image/enemy/chara_B_taiki_Sheet.png")
         , LoadTexture(L"Data/Image/enemy/chara_B_attack_Sheet.png")
          , LoadTexture(L"Data/Image/enemy/charaB_move_back.png")
        ,LoadTexture(L"Data/Image/enemy/charaB_move_front.png")
            ,LoadTexture(L"Data/Image/enemy/charaB_snow_in-Sheet.png")
           ,LoadTexture(L"Data/Image/enemy/charaB_snow_loop-Sheet.png")
           ,LoadTexture(L"Data/Image/enemy/charaB_snow_out-Sheet.png")
    }//�G��enemy�t�@�C���̏㉺���]�����摜���g��
    {
        asc_->SetAnimTextures(k_enemyB_[static_cast<int>(PlayerMotion::IDLE)], k_player_size_, 8, 5.f);
    };

    void Player_texchange(int texnum) override;
};




