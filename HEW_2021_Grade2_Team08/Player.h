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
#include "ScoreManager.h"

#include "Skillicon.h"
#include "SnowCost.h"
#include "SnowCost_tate.h"
#include "DEBUG_Comand.h"

//#define  ECSC static_cast<int> //enum class static castの略

class Bullet;
class Golem;

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
    
    
    class SnowCost* snowcost_;                        //持っている雪の数を表示するオブジェクトを作る
    //class SnowCost_tate* snowcost_tate_;
    class Skillicon* skillicon_;                        //スキルのUIを表示するオブジェクトを作る
    class DEBUG_Comand* debugcomand_;

    class AnimSpriteComponent* asc_;    
    int     player_mode_;                          //プレイヤーのステート(Playerだけで完結する版)
    float idlecount_;                                //待機状態に入るまでのタイマー
    float     idle_timeto_;                           //timetoまで数えると待機状態になる

    int     player_layer_;                           //プレイヤーの描画の優先度
    const int k_player_layer_var;           //プレイヤーの描画の優先度の変化量

    const int k_player_snow_max_;     //プレイヤーの持てる雪の上限
    const int k_player_snow_min_ ;     //プレイヤーの持てる雪の下限

    Vec2 k_player_pos_center_;      //9マスの真ん中の座標
    const Vec2 k_player_pos_var_;          //ボタンを押したときのプレイヤーの移動量　
    const Vec2 k_player_vel_;          //プレイヤーの移動速度
    Vec2 k_player_size_;                      //プレイヤーキャラの大きさ
    const Vec2 k_player_hit_size_;
    const Vec2 k_player_hit_pos_;         //コリジョンのプレイヤーに対する相対的な位置
    const int k_player_skillcost_[4];   //共通スキルのコスト
    const int k_who_player_;            //プレイヤーの種類を示す
    const bool k_Is_player_;                //trueならプレイヤー側 false なら敵側
    const int k_player_damagetime_;        //ダメージモーションの持続時間 (default)
    float damagetime_;                          //ため-じモーションの持続時間

    const float k_player_dushspd_;        //ダッシュ時のスピード倍率
    const float k_player_Inputtime_;       //ダッシュの入力可能時間
    float player_rightDashCount_ = 0;
    float player_leftDashCount_ = 0;

    enum class WHO_Player : int
    {
        CHARAA,
        CHARAB,
        CHARAC,
        CHARAD,
    };
    //キャラの画像の番号をステートを同時に表す列挙型
    enum class PlayerMotion :int
    {
        IDLE,                   //待機
        ATTACK,             //攻撃
        MOVE_FRONT,     //前移動
        MOVE_BACK,      //後ろ移動
        MOVE_UPANDDOWN,     //上下移動 

        COLLECT_IN,     //雪集め開始
        COLLECT_LOOP,   //雪集め中
        COLLECT_OUT,       //雪集め終了
        USE_SKILL,          //スキル使用中

        HIT,                    //被ヒット時

        USE_SKILL_IN,       //スキル開始
        USE_SKILL_LOOP, //スキル中
        USE_SKILL_OUT,  //スキル終了
    };

    StateContext<Player>* pplayer_state_context_;
    Stage* stg_;

    const int k_player_SE_[6];
    
    enum class playerl_SE_num :int
    {
        ATTACK,             //攻撃
        MOVE,

        COLLECT_IN,     //雪集め開始
        
        USE_SKILL,          //スキル使用中

        HIT,                    //被ヒット時

        SNOW_UP,       //ゲージが貯まる音
    };

public:

    Player(class Game* game, Stage* stg ,Vec2 size, Vec2 center,int uniquecost, bool Is_player, int who);
    virtual ~Player();
    void UpdateActor(float deltatime) override;

    void Player_move(float deltatime);
    void Player_setposnum();
    void Player_snow_collect();
    void Player_snow_throw(float deltatime);
    void Player_idlecheck(float deltatime);
    void Player_useskill(void);
    int Player_getstagenum(void);
    int Player_getsnow(void);
    virtual void Player_UniqueSkill(void) = 0;
    virtual void Player_texchange(int texnum) = 0;
    void Player_SetHit(float damagetime);
    Vec2 Player_Get_coligionpos(void);
    //void Player_Draw(int mode);

    
};
#endif // PLAYER_H

