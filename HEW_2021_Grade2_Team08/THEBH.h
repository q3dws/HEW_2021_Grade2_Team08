#pragma once
#include "Actor.h"

#define BLACKHOLE_SIZE  200
#define BASEUSETIME		20
#define BH_POS_X		480
#define BH_POS_Y		120

class THEBH :
    public Actor
{
private:
    class AnimSpriteComponent* BH_asc_;
    int BH_state_;
    float motioncount_;
    float hitcount_;

    int k_BH_tex_[4];                       //壁のテクスチャ
    const Vec2 k_BH_pos_;                         //かべの位置
    Vec2 BH_size_;                      //壁の大きさ
    const Vec2 k_BH_hitsize_;
    const int k_BH_layer_;                    //壁の描画優先度
    const int k_BH_cost_;                 //壁のコスト
    
    int BH_hp_;               //壁の耐久力

    enum class BH_frame_num : int
    {
        ADVENT = 5,
        IDLE = 8,
        LEAVE = 5,
        HIT = 4
    };

    enum class BH_Motion :int
    {
        ADVENT,     //登場
        IDLE,     //通常
        LEAVE,      //退場
        HIT,        //ヒット時
    };

    const int k_BH_SE_[3];

    enum class BH_SE_num :int
    {
        ADVENT,     //登場
        LEAVE,      //退場
        HIT,     //被弾音
    };

public:
    THEBH(Game* game, int layer);
    ~THEBH();
    void UpdateActor(float deltatime) override;
    void THEBH_texchange(int texnum);
  
    void Set_THEBHHit(int power);
};

