#pragma once
#include "Player.h"
#include "Scoop.h"
class CharaA :
    public Player
{
private:
    const int k_charaA_[9];                          //�L�����N�^�[A�̃e�N�X�`��

    std::vector<class Scoop*> scoops_; //�e�̃I�u�W�F�N�g����铮�I�z��

    enum class charaA_frame_num : int
    {
        IDLE = 8,
        ATTACK = 8,
        MOVE_FRONT = 1,
        MOVE_BACK = 1,
        MOVE_UPANDDOWN = 8, 
        COLLECT_IN = 5,
        COLLECT_LOOP = 3,
        COLLECT_OUT = 5,
        USE_SKILL = 13,      
    };  //���ꂼ��̃��[�V�����̃R�}��
public:
    CharaA(class Game* game, Stage* stg) : Player(game, stg , Vec2(64 * 2.5, 64 * 2.5) , Vec2(325, 246 + 33))
        , k_charaA_
        {LoadTexture(L"Data/Image/player/chara_A_taiki_Sheet.png")
             , LoadTexture(L"Data/Image/player/chara_A_attack_Sheet.png")
              ,LoadTexture(L"Data/Image/player/charaA_move_front.png")
              , LoadTexture(L"Data/Image/player/charaA_move_back.png")
                ,LoadTexture(L"Data/Image/player/chara_A_taiki_Sheet.png")
                ,LoadTexture(L"Data/Image/player/charaA_snow_in-Sheet.png")
               ,LoadTexture(L"Data/Image/player/charaA_snow_loop-Sheet.png")
               ,LoadTexture(L"Data/Image/player/charaA_snow_out-Sheet.png")
            ,LoadTexture(L"Data/Image/player/chara_A_skill_Sheet.png")
         }
    {
        asc_->SetAnimTextures(k_charaA_[static_cast<int>(PlayerMotion::IDLE)], k_player_size_, 8, 5.f);
    };

    void Player_texchange(int texnum) override;
    void Player_UniqueSkill(void) override;
};

