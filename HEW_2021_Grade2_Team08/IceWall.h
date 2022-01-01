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

    int k_wall_tex_[3];                       //壁のテクスチャ
    const Vec2 k_wall_pos_;                         //かべの位置
    Vec2 wall_size_;                      //壁の大きさ
    const int k_wall_layer_;                    //壁の描画優先度
    const int k_wall_cost_;                 //壁のコスト

    enum class wall_frame_num : int
    {
        ADVENT = 5,
        IDLE = 1,
        LEAVE = 8,
    };

    enum class wall_Motion :int
    {
        ADVENT,     //登場
        IDLE,     //通常
        LEAVE,      //退場
    };

public:
    IceWall(Game* game, Vec2 playerpos, int layer, bool Is_player);
    void UpdateActor(float deltatime) override;
    void IceWall_texchange(int texnum);
};

