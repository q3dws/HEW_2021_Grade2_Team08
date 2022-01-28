#pragma once
#include "Skill.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"

class IceWall :
    public Skill
{
private:
    class AnimSpriteComponent* wall_asc_;
    int wall_state_;
    float motioncount_;
    float hitcount_;

    int k_wall_tex_[4];                       //壁のテクスチャ
    const Vec2 k_wall_pos_;                         //かべの位置
    Vec2 wall_size_;                      //壁の大きさ
    const Vec2 k_wall_hitsize_;
    const int k_wall_layer_;                    //壁の描画優先度
    const int k_wall_cost_;                 //壁のコスト
    const bool k_Is_player_;
    int wall_hp_;               //壁の耐久力

    enum class wall_frame_num : int
    {
        ADVENT = 5,
        IDLE = 1,
        LEAVE = 8,
        HIT = 4
    };

    enum class wall_Motion :int
    {
        ADVENT,     //登場
        IDLE,     //通常
        LEAVE,      //退場
        HIT,        //ヒット時
    };

    const int k_wall_SE_[3];
    
    enum class wall_SE_num :int
    {
        ADVENT,     //登場
        LEAVE,      //退場
        HIT,     //被弾音
    };

public:
    IceWall(Game* game, Vec2 playerpos, int layer, bool Is_player);
    ~IceWall();
    void UpdateActor(float deltatime) override;
    void IceWall_texchange(int texnum);
    bool Get_Isplayer();
    void Set_IceWallHit(int power);
};

