#pragma once

#pragma once
#include "Player.h"
class CharaB :
    public Player
{
private:
    std::vector<int> k_charaB_;
    
    enum class charaB_frame_num : int
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
        HIT = 1,
    };

public:
    CharaB(class Game* game, Stage* stg, bool Is_player)
        : Player(game, stg, Vec2(64 * 2.5, 64 * 2.5), Vec2(325, 246 + 33), 2, Is_player
        , static_cast<int>(WHO_Player::CHARAB))
        //固有スキルのコストはplayerの引数に直接渡して設定しています
        ,k_charaB_
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
            k_charaB_ =
            { LoadTexture(L"Data/Image/player/chara_B_taiki_Sheet.png")
             , LoadTexture(L"Data/Image/player/chara_B_attack_Sheet.png")
              ,LoadTexture(L"Data/Image/player/charaB_move_front.png")
              , LoadTexture(L"Data/Image/player/charaB_move_back.png")
                ,LoadTexture(L"Data/Image/player/chara_B_taiki_Sheet.png")
                ,LoadTexture(L"Data/Image/player/charaB_snow_in-Sheet.png")
               ,LoadTexture(L"Data/Image/player/charaB_snow_loop-Sheet.png")
               ,LoadTexture(L"Data/Image/player/charaB_snow_out-Sheet.png")
            ,LoadTexture(L"Data/Image/player/chara_B_skill_Sheet.png")
                 ,LoadTexture(L"Data/Image/player/charaB_damage.png")
            };
        }
        else
        {
            k_charaB_ =
            { LoadTexture(L"Data/Image/enemy/chara_B_taiki_Sheet.png")
                 , LoadTexture(L"Data/Image/enemy/chara_B_attack_Sheet.png")
                  , LoadTexture(L"Data/Image/enemy/charaB_move_back.png")
                ,LoadTexture(L"Data/Image/enemy/charaB_move_front.png")
                    ,LoadTexture(L"Data/Image/enemy/chara_B_taiki_Sheet.png")
                    ,LoadTexture(L"Data/Image/enemy/charaB_snow_in-Sheet.png")
                   ,LoadTexture(L"Data/Image/enemy/charaB_snow_loop-Sheet.png")
                   ,LoadTexture(L"Data/Image/enemy/charaB_snow_out-Sheet.png")
                ,LoadTexture(L"Data/Image/enemy/chara_B_skill_Sheet.png")
                 ,LoadTexture(L"Data/Image/enemy/charaB_damage.png")
            };
        }

        asc_->SetAnimTextures(k_charaB_[static_cast<int>(PlayerMotion::IDLE)], k_player_size_, 8, 5.f);
    };

    void Player_texchange(int texnum) override;
    void Player_UniqueSkill(void) override;
};


