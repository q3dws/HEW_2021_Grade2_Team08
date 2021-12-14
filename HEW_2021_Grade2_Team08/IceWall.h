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
   
    const int k_wall_tex_;                       //壁のテクスチャ
    const Vec2 k_wall_pos_;                         //かべの位置
    const Vec2 k_wall_size_;                      //壁の大きさ
    const int k_wall_layer_;                    //壁の描画優先度

public:
    IceWall(Game* game, Vec2 playerpos, int layer);
    void UpdateActor(float deltatime) override;
   
};

