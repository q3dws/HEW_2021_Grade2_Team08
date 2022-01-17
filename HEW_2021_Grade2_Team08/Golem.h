#pragma once
#include "Skill.h"
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"

class Golem :
    public Skill
{
private:
    class AnimSpriteComponent* golem_asc_;
    int     golem_state_;            //ゴーレムの状態
    float     attackcount_;                //ゴーレムの攻撃するまでの時間を数える    
    float     motioncount_;             //ゴーレムの登場/退場アニメの終わる時間を数える
    int     deathcount;            //投げた玉の数を数える

    int golem_tex_[3];                       //ゴーレムのテクスチャ
    const Vec2 k_golem_pos_;                         //ゴーレムの位置
    Vec2 k_golem_size_;                      //ゴーレムの大きさ
    const int k_golem_layer;                    //ゴーレムの描画の優先度
    const int k_bullettex_;                         //弾のテクスチャ
    const bool  k_Is_player_;                   //プレイヤー側かどうかの変数
    std::vector<class Bullet*> bullets_; //弾のオブジェクトを作る動的配列
    int golem_hp_;                          //ゴーレムの耐久値

    enum class golem_frame_num : int
    {
        ADVENT = 17,
        ATTACK = 14,
        LEAVE = 8,
    };

    enum class golem_Motion :int
    {
        ADVENT,     //登場
        ATTACK,     //攻撃中
        LEAVE,      //退場
    };


public:
    Golem(Game* game, Vec2(pos), int bullettex, int layer, bool Is_player_);
    ~Golem();
    void UpdateActor(float deltatime) override;
    void Golem_snow_throw(float deltatime);
    void Golem_death_check(float deltatime);
    void Golem_texchange(int texnum) ;
    void Set_Golemhit(int power);
    bool Get_Isplayer();
};

