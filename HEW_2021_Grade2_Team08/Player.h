#pragma once
#ifndef PLAYER_H
#define PLAYER_H
/*
    作成者　君島朝日
    作成日 2021/11/07
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
    D3DXVECTOR2 player_pos_;          //プレイヤーの画面上の座標
    int player_snow_;                     //プレイヤーの現在持っている雪
    int     player_pos_num_;                    //プレイヤーのいるマスの番号
    /*
    012
    345 それぞれの数字がマスの番号に対応
    678
    */
    //class Stage* pstage;
  
    int bullettex_;                              //弾のテクスチャ
    std::vector<class Bullet*> bullets_; //弾のオブジェクトを作る動的配列
  
    class AnimSpriteComponent* asc_[2];
    int     texbuffer_;                              //asc_の添え字
    float idlecount_;                                //待機状態に入るまでのタイマー

    const int k_player_snow_max_;     //プレイヤーの持てる雪の上限
    const int k_player_snow_min_ ;     //プレイヤーの持てる雪の下限

    const D3DXVECTOR2 k_player_pos_center_;      //9マスの真ん中の座標
    const D3DXVECTOR2 k_player_pos_var_;          //ボタンを押したときのプレイヤーの移動量　
    const D3DXVECTOR2 k_player_vel_;          //プレイヤーの移動速度
    const Vec2 k_player_size_;                      //プレイヤーキャラの大きさ

    const int k_charaA_[2];                          //キャラクターAのテクスチャ 0:待機 1:攻撃
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

