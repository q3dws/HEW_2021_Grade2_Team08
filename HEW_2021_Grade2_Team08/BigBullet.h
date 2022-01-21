#pragma once
#include "Skill.h"
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"

//スキル大玉のクラス
//作成者　君島朝日
// 作成日　2021/12/12
//

class BigBullet :
    public Skill
{
public:
    BigBullet(class Game* game, bool Is_player, int layer, Vec2 pos);
    ~BigBullet();
    void UpdateActor(float delta_time) override;
    void BigBullet_move(float delta_time);

    void BigBullet_ColligionCheck(float  delta_taime);
    void BigBullet_texchange(int texnum);

private:
    class AnimSpriteComponent* bigsnow_asc_;
    const int k_bigsnow_tex_[2];                       //大玉のテクスチャ
    const float k_bigsnow_vel_;                     //大玉の速さ
    const Vec2 k_bigsnow_Grow;                 //大玉の大きくなる速度
    const float k_bigsnow_Growrot_;             //大玉の回転速度
    const int k_bigsnow_layer_;
    Vec2 bigsnow_size_; //大玉の大きさ
    Vec2 bigsnow_pos_;
    const bool k_Is_player_;
    float bigsnow_rot_;                   //大玉の回転角
    int bigsnow_power_;                 //ヒット時の威力
    float bigsnow_distance_count_;  //移動距離を数える

    int bigsnow_state_;
    float motioncount_;

    enum class bigsnow_frame_num : int
    {
        IDLE = 1,
        LEAVE = 2,

    };

    enum class bigsnow_Motion :int
    {
        IDLE,     //通常
        LEAVE,      //退場
    };
};

