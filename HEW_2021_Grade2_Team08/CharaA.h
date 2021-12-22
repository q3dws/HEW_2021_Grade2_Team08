#pragma once
#include "Player.h"
#include "Scoop.h"
class CharaA :
    public Player
{
private:
    std::vector<int> k_charaA_;                          //�L�����N�^�[A�̃e�N�X�`��
    const int k_charaA_player_tex[9];
    const int k_charaA_notplayer_tex[9];
    const int k_charaA_skillcost_;                      //�L����A�̃X�L���̃R�X�g
    std::vector<class Scoop*> scoops_; //�e�̃I�u�W�F�N�g����铮�I�z��

    //std::unique_ptr<Scoop> scoops{ new Scoop(GetGame(), player_layer_, player_pos_) };


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
    CharaA(class Game* game, Stage* stg,bool Is_player) 
        : Player(game, stg , Vec2(64 * 2.5, 64 * 2.5) , Vec2(325, 246 + 33),Is_player)
        , k_charaA_skillcost_(2)
        ,k_charaA_player_tex
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
        , k_charaA_notplayer_tex
    { LoadTexture(L"Data/Image/enemy/chara_A_taiki_Sheet.png")
         , LoadTexture(L"Data/Image/enemy/chara_A_attack_Sheet.png")
          ,LoadTexture(L"Data/Image/enemy/charaA_move_front.png")
          , LoadTexture(L"Data/Image/enemy/charaA_move_back.png")
            ,LoadTexture(L"Data/Image/enemy/chara_A_taiki_Sheet.png")
            ,LoadTexture(L"Data/Image/enemy/charaA_snow_in-Sheet.png")
           ,LoadTexture(L"Data/Image/enemy/charaA_snow_loop-Sheet.png")
           ,LoadTexture(L"Data/Image/enemy/charaA_snow_out-Sheet.png")
        ,LoadTexture(L"Data/Image/enemy/chara_A_skill_Sheet.png")
    }
    {
       
        if (Is_player)
        {
            k_charaA_ =
            { LoadTexture(L"Data/Image/player/chara_A_taiki_Sheet.png")
             , LoadTexture(L"Data/Image/player/chara_A_attack_Sheet.png")
              ,LoadTexture(L"Data/Image/player/charaA_move_front.png")
              , LoadTexture(L"Data/Image/player/charaA_move_back.png")
                ,LoadTexture(L"Data/Image/player/chara_A_taiki_Sheet.png")
                ,LoadTexture(L"Data/Image/player/charaA_snow_in-Sheet.png")
               ,LoadTexture(L"Data/Image/player/charaA_snow_loop-Sheet.png")
               ,LoadTexture(L"Data/Image/player/charaA_snow_out-Sheet.png")
            ,LoadTexture(L"Data/Image/player/chara_A_skill_Sheet.png")
            };
        }
        else
        {
            k_charaA_ =
            { LoadTexture(L"Data/Image/enemy/chara_A_taiki_Sheet.png")
                 , LoadTexture(L"Data/Image/enemy/chara_A_attack_Sheet.png")
                  , LoadTexture(L"Data/Image/enemy/charaA_move_back.png")
                ,LoadTexture(L"Data/Image/enemy/charaA_move_front.png")
                    ,LoadTexture(L"Data/Image/enemy/chara_A_taiki_Sheet.png")
                    ,LoadTexture(L"Data/Image/enemy/charaA_snow_in-Sheet.png")
                   ,LoadTexture(L"Data/Image/enemy/charaA_snow_loop-Sheet.png")
                   ,LoadTexture(L"Data/Image/enemy/charaA_snow_out-Sheet.png")
                ,LoadTexture(L"Data/Image/enemy/chara_A_skill_Sheet.png")
            };
        }

        asc_->SetAnimTextures(k_charaA_[static_cast<int>(PlayerMotion::IDLE)], k_player_size_, 8, 5.f);
    };

    void Player_texchange(int texnum) override;
    void Player_UniqueSkill(void) override;
};

