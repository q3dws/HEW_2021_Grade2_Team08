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
    Scoop(class Game* game, int layer, Vec2 pos, bool Is_player, Stage* stg, Player*player);
    ~Scoop();
    void UpdateActor(float delta_time) override;
    void Scoop_parabola(float delta_time);
    void Scoop_exprosion();
    void Scoop_summon_icepiller();
private:
    class SpriteComponent* scoop_asc_;

    Vec2 scoop_pos_;                                //すくい投げの画面上の座標
    const Vec2 k_scoop_pos_init_;           //すくい投げ開始位置
    Vec2 k_scoop_distination_;                    //着弾点
    const int k_scoop_tex_;                       //すくい投げのテクスチャ
    const float k_scoop_g_;                     //重力加速度
    const int k_scoop_layer_;                   //すくいなげの描画優先度
    const Vec2 k_scoop_size_; //すくい投げの大きさ
   
    int scoop_stage_num_;           //着弾点のマス目
    const float k_scoop_deg_;               //すくい投げの角度
    const bool k_Is_player_;
    Stage* stg_;
    const int k_scoop_SE_;
};

class MiniBullet :
    public Actor
{
public:
    MiniBullet(class Game* game, int tex, Vec2 pos, bool up, bool is_player);
    ~MiniBullet();
    void UpdateActor(float delta_time) override;
private:
    bool up_; //上に飛ぶかどうか
    const float snow_vel_; //雪の速さ
    bool k_Is_player_;
    int k_damagetime_;
   
};

//---------------------------------------------------------------
//氷柱のクラス
//---------------------------------------------------------------
class Icepillar :
    public Actor
{
public:
    Icepillar(class Game* game, int stage_num, bool is_player, Stage* stg, int layer);
    ~Icepillar();
    void UpdateActor(float delta_time) override;
    void Icepillar_ColligionCheck(float  delta_taime);
private:
    class AnimSpriteComponent* icepillar_asc_;

    const Vec2 k_icepillar_size_;
    const Vec2 k_icepillar_pos_;
    const int k_icepillar_tex_;                       //火柱のテクスチャ
    const bool k_Is_player_;
    const int k_icepillar_time_;                   //火柱の持続時間
    const int       k_icepillar_stage_num_;                     //溶かすマスの番号


    float deadcount_;                               //死ぬまでの時間を数える
    Stage* stg_;

    const int k_icepillar_power_;
    bool hitstate_;                                     //trueだとなにかにヒットしている

    enum class icepillar_frame_num : int
    {
        IDLE = 8,

    };
};
