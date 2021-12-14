#pragma once
#include "Skill.h"
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"

//スキルすくい投げのクラス
//作成者　君島朝日
// 作成日　2021/12/13
//

class Scoop :
    public Skill
{
public:
    Scoop(class Game* game, int layer, Vec2 pos);
    ~Scoop();
    void UpdateActor(float delta_time) override;
    void Scoop_parabola(float delta_time);
    void Scoop_exprosion();
private:
    class SpriteComponent* scoop_asc_;

    Vec2 scoop_pos_;                                //すくい投げの画面上の座標
    const Vec2 k_scoop_pos_init_;           //すくい投げ開始位置
    Vec2 scoop_distination_;                    //着弾点
    const int k_scoop_tex_;                       //すくい投げのテクスチャ
    const Vec2 k_scoop_vel_;                     //すくい投げの速さ
    const float k_scoop_g_;                     //重力加速度
    const int k_scoop_layer_;                   //すくいなげの描画優先度
    //const Vec2 k_bigsnow_Grow;                 //大玉の大きくなる速度
    const Vec2 k_scoop_size_; //すくい投げの大きさ
};

class MiniBullet :
    public Actor
{
public:
    MiniBullet(class Game* game, int tex, Vec2 pos, bool up);
    ~MiniBullet();
    void UpdateActor(float delta_time) override;
private:
    bool up_; //上に飛ぶかどうか
    const float snow_vel_; //雪の速さ
};