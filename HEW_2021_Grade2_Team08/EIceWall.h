#pragma once
#ifndef EICEWALL_H
#define EICEWALL_H


#include "Skill.h"
class EIceWall :
    public Skill
{
public:
    EIceWall(Game* game, Vec2 playerpos, int layer, int posidx);
    ~EIceWall();
    void UpdateActor(float deltatime) override;
    void IceWall_texchange(int texnum);
    bool Get_Isplayer();
    void Set_IceWallHit(int power);
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
};
#endif // !EICEWALL_H