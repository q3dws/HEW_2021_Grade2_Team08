#pragma once
#include "Player.h"
#include "Machinegun.h"

class CharaD :
    public Player
{
private:
    std::vector<int>  k_charaD_;                          //キャラクターCのテクスチャ

    std::vector<class Machinegun*> machineguns_; //弾のオブジェクトを作る動的配列

   
    enum class charaD_frame_num : int
    {
        IDLE = 16,
        ATTACK = 8,
        MOVE_FRONT = 1,
        MOVE_BACK = 1,
        MOVE_UPANDDOWN = 16,
        COLLECT_IN = 5,
        COLLECT_LOOP = 3,
        COLLECT_OUT = 5,
        USE_SKILL = 13,
        HIT = 1,

        USE_SKILL_IN = 6,
        USE_SKILL_LOOP = 2,
        USE_SKILL_OUT = 6,
    };

public:
    CharaD(class Game* game, Stage* stg, bool Is_player)
        : Player(game, stg, Vec2(64 * 2.5, 64 * 2.5), Vec2(315, 300), 1, Is_player
        , static_cast<int>(WHO_Player::CHARAD))
        //固有スキルのコストはplayerの引数に直接渡して設定しています
        , k_charaD_
    { LoadTexture(L"Data/Image/player/chara_B_taiki_Sheet.png")
         , LoadTexture(L"Data/Image/player/chara_B_attack_Sheet.png")
          ,LoadTexture(L"Data/Image/player/charaB_move_front.png")
          , LoadTexture(L"Data/Image/player/charaB_move_back.png")
        ,LoadTexture(L"Data/Image/player/chara_B_taiki_Sheet.png")
            ,LoadTexture(L"Data/Image/player/charaB_snow_in-Sheet.png")
           ,LoadTexture(L"Data/Image/player/charaB_snow_loop-Sheet.png")
           ,LoadTexture(L"Data/Image/player/charaB_snow_out-Sheet.png")
           ,LoadTexture(L"Data/Image/player/chara_B_skill_Sheet.png")

    }
    {

        if (Is_player)
        {
            k_charaD_ =
            { LoadTexture(L"Data/Image/player/charaD_taiki_Sheet.png")
         , LoadTexture(L"Data/Image/player/charaD_attack_Sheet.png")
          ,LoadTexture(L"Data/Image/player/charaD_move_front.png")
          , LoadTexture(L"Data/Image/player/charaD_move_back.png")
        ,LoadTexture(L"Data/Image/player/charaD_taiki_Sheet.png")
            ,LoadTexture(L"Data/Image/player/charaD_snow_in_Sheet.png")
           ,LoadTexture(L"Data/Image/player/charaD_snow_loop_Sheet.png")
           ,LoadTexture(L"Data/Image/player/charaD_snow_out_Sheet.png")
           ,LoadTexture(L"Data/Image/player/chara_B_skill_Sheet.png")
                 ,LoadTexture(L"Data/Image/player/charaD_damage.png")

                ,LoadTexture(L"Data/Image/player/charaD_skill_in_Sheet.png")
                ,LoadTexture(L"Data/Image/player/charaD_skill_loop_Sheet.png")
                ,LoadTexture(L"Data/Image/player/charaD_skill_out_Sheet.png")
            };
        }
        else
        {
            k_charaD_ =
            { 
               
                LoadTexture(L"Data/Image/enemy/charaD_taiki_Sheet.png")
         , LoadTexture(L"Data/Image/enemy/charaD_attack_Sheet.png")
          ,LoadTexture(L"Data/Image/enemy/charaD_move_front.png")
          , LoadTexture(L"Data/Image/enemy/charaD_move_back.png")
        ,LoadTexture(L"Data/Image/enemy/charaD_taiki_Sheet.png")
            ,LoadTexture(L"Data/Image/enemy/charaD_snow_in_Sheet.png")
           ,LoadTexture(L"Data/Image/enemy/charaD_snow_loop_Sheet.png")
           ,LoadTexture(L"Data/Image/enemy/charaD_snow_out_Sheet.png")
           ,LoadTexture(L"Data/Image/enemy/chara_B_skill_Sheet.png")
                 ,LoadTexture(L"Data/Image/enemy/charaD_damage.png")

                ,LoadTexture(L"Data/Image/enemy/charaD_skill_in_Sheet.png")
                ,LoadTexture(L"Data/Image/enemy/charaD_skill_loop_Sheet.png")
                ,LoadTexture(L"Data/Image/enemy/charaD_skill_out_Sheet.png")
            };
        }
        asc_->SetAnimTextures(k_charaD_[static_cast<int>(PlayerMotion::IDLE)], k_player_size_, static_cast<int>(charaD_frame_num::IDLE), 5.f);
    };

    void Player_texchange(int texnum) override;
    void Player_UniqueSkill(void) override;
};

