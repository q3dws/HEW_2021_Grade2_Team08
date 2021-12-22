#pragma once
#include "Skill.h"
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"
#include "Player.h"
#include "Stage.h"

class Fireball :
    public Skill
{
public:
    Fireball(class Game* game, int layer, Vec2 pos, Player* player, Stage* stg, bool Is_player);
    ~Fireball();
    void UpdateActor(float delta_time) override;
    void Fireball_parabola(float delta_time);
    void Fireball_exprosion();
private:
    class SpriteComponent* fireball_asc_;

    Vec2 fireball_pos_;                                //火の玉の画面上の座標
    const Vec2 k_fireball_pos_init_;           //火の玉開始位置
    Vec2 k_fireball_distination_;                    //着弾点
    const int k_fireball_tex_;                       //火の玉のテクスチャ
    const float k_fireball_g_;                     //重力加速度
    const int k_fireball_layer_;                   //火の玉の描画優先度
    const Vec2 k_fireball_size_; //火の玉の大きさ

    const float k_fireball_deg_;               //火の玉の開始角度

    const bool k_Is_player_;

    float       fireball_stage_num_;                     //溶かすマスの番号
    Stage* stg_;
};


