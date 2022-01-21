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
    class AnimSpriteComponent* fireball_asc_;

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

    float     attackcount_;                //火の玉の登場するまでの時間を数える    
    float     k_fireball_delay_;                //火の玉の登場するまでのコマ数    

    Stage* stg_;

    enum class fireball_frame_num : int
    {
        IDLE = 4,
        
    };
};


//火柱のクラス
class Firepillar :
    public Actor
{
public:
    Firepillar(class Game* game, int stage_num, bool is_player, Stage* stg, int layer);
    ~Firepillar();
    void UpdateActor(float delta_time) override;
    void Firepillar_ColligionCheck(float  delta_taime);
private:
    class AnimSpriteComponent* firepillar_asc_;

    const Vec2 k_firepillar_size_;
    const Vec2 k_firepillar_pos_;
    const int k_firepillar_tex_;                       //火柱のテクスチャ
    const bool k_Is_player_;
    const int k_firepillar_time_;                   //火柱の持続時間
    const int       k_firepillar_stage_num_;                     //溶かすマスの番号

    float deadcount_;                               //死ぬまでの時間を数える
    Stage* stg_;

    const int k_firepillar_power_;
    bool hitstate_;                                     //trueだとなにかにヒットしている

    enum class firepillar_frame_num : int
    {
        IDLE = 8,

    };
};

