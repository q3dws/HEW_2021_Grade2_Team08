#pragma once
#include "Player.h"
#include "Fireball.h"
class CharaC :
    public Player
{
private:
    std::vector<int>  k_charaC_;                          //キャラクターCのテクスチャ

    std::vector<class Fireball*> fireballs_; //弾のオブジェクトを作る動的配列
   
    enum class charaC_frame_num : int
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
    };

public:
    CharaC(class Game* game, Stage* stg, bool Is_player)
        : Player(game, stg, Vec2(64 * 2.5, 64 * 2.5), Vec2(325, 246 + 33), 2, Is_player
        , static_cast<int>(WHO_Player::CHARAC))
        //固有スキルのコストはplayerの引数に直接渡して設定しています
        ,k_charaC_
    { LoadTexture(L"Data/Image/player/charaC_taiki_Sheet.png")
         , LoadTexture(L"Data/Image/player/charaC_attack_Sheet.png")
          ,LoadTexture(L"Data/Image/player/charaC_move_front.png")
          , LoadTexture(L"Data/Image/player/charaC_move_back.png")
        ,LoadTexture(L"Data/Image/player/charaC_taiki_Sheet.png")
            ,LoadTexture(L"Data/Image/player/charaC_snow_in_Sheet.png")
           ,LoadTexture(L"Data/Image/player/charaC_snow_loop_Sheet.png")
           ,LoadTexture(L"Data/Image/player/charaC_snow_out_Sheet.png")
           ,LoadTexture(L"Data/Image/player/chara_B_skill_Sheet.png")
         ,LoadTexture(L"Data/Image/player/charaC_damage.png")
    }
    {

        if (Is_player)
        {
            k_charaC_ =
            { LoadTexture(L"Data/Image/player/charaC_taiki_Sheet.png")
         , LoadTexture(L"Data/Image/player/charaC_attack_Sheet.png")
          ,LoadTexture(L"Data/Image/player/charaC_move_front.png")
          , LoadTexture(L"Data/Image/player/charaC_move_back.png")
        ,LoadTexture(L"Data/Image/player/charaC_taiki_Sheet.png")
            ,LoadTexture(L"Data/Image/player/charaC_snow_in_Sheet.png")
           ,LoadTexture(L"Data/Image/player/charaC_snow_loop_Sheet.png")
           ,LoadTexture(L"Data/Image/player/charaC_snow_out_Sheet.png")
           ,LoadTexture(L"Data/Image/player/chara_B_skill_Sheet.png")
                 ,LoadTexture(L"Data/Image/player/charaC_damage.png")
            };
        }
        else
        {
            k_charaC_ =
            { LoadTexture(L"Data/Image/enemy/chara_B_taiki_Sheet.png")
                 , LoadTexture(L"Data/Image/enemy/chara_B_attack_Sheet.png")
                  , LoadTexture(L"Data/Image/enemy/charaB_move_back.png")
                ,LoadTexture(L"Data/Image/enemy/charaB_move_front.png")
                    ,LoadTexture(L"Data/Image/enemy/chara_B_taiki_Sheet.png")
                    ,LoadTexture(L"Data/Image/enemy/charaB_snow_in-Sheet.png")
                   ,LoadTexture(L"Data/Image/enemy/charaB_snow_loop-Sheet.png")
                   ,LoadTexture(L"Data/Image/enemy/charaB_snow_out-Sheet.png")
                ,LoadTexture(L"Data/Image/enemy/chara_B_skill_Sheet.png")
                 ,LoadTexture(L"Data/Image/enemy/charaC_damage.png")
            };
        }
        asc_->SetAnimTextures(k_charaC_[static_cast<int>(PlayerMotion::IDLE)], k_player_size_, static_cast<int>(charaC_frame_num::IDLE), 5.f);
    };

    void Player_texchange(int texnum) override;
    void Player_UniqueSkill(void) override;
};

