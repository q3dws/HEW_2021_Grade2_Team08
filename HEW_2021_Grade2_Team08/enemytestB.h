#pragma once

#pragma once
#include "Player.h"


class EnemytestB :
    public Player
{
private:
    const int k_enemyB_[8];                          //キャラクターBのテクスチャを入れる配列
    enum class enemyB_frame_num : int       //アニメーションのコマ数
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
    //Player.cppのk_player_sizeに代入しているVec2を両方ともマイナスにして上下反転させて正しく表示しています
    //k_player_centerの位置をズラすことで全体の位置が移動しています
    //backとflontの画像をCharaBから入れ替えています
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
    }//敵はenemyファイルの上下反転した画像を使う
    {
        asc_->SetAnimTextures(k_enemyB_[static_cast<int>(PlayerMotion::IDLE)], k_player_size_, 8, 5.f);
    };

    void Player_texchange(int texnum) override;
};




