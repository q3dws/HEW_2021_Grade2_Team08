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
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"

class Bullet;

class Player : public Actor
{
protected: 
    Vec2 player_pos_;          //プレイヤーの画面上の座標
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
    //int * a[12]
  
    class AnimSpriteComponent* asc_;    
    int     player_mode_;                          //プレイヤーのステート(Playerだけで完結する版)
    float idlecount_;                                //待機状態に入るまでのタイマー
    int     idle_timeto_;                           //timetoまで数えると待機状態になる

    const int k_player_snow_max_;     //プレイヤーの持てる雪の上限
    const int k_player_snow_min_ ;     //プレイヤーの持てる雪の下限

    const Vec2 k_player_pos_center_;      //9マスの真ん中の座標
    const Vec2 k_player_pos_var_;          //ボタンを押したときのプレイヤーの移動量　
    const Vec2 k_player_vel_;          //プレイヤーの移動速度
    const Vec2 k_player_size_;                      //プレイヤーキャラの大きさ

    enum class PlayerMotion :int
    {
        IDLE,                   //待機
        ATTACK,             //攻撃
        MOVE_FRONT,     //前移動
        MOVE_BACK,      //後ろ移動
        COLLECT_IN,     //雪集め開始
        COLLECT_LOOP,   //雪集め中
        COLLECT_OUT,       //雪集め終了
    };

    StateContext<Player>* pplayer_state_context_;
    Stage* stg_;

    
public:

    Player(class Game* game, Stage* stg ,Vec2 size, Vec2 center);
    virtual ~Player();
    void UpdateActor(float deltatime) override;

    void Player_move(float deltatime);
    void Player_snow_collect();
    void Player_snow_throw(float deltatime);
    void Player_idlecheck(float deltatime);
    virtual void Player_texchange(int texnum) = 0;
    //void Player_Draw(int mode);
};
#endif // PLAYER_H

