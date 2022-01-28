#pragma once
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"

//TIMEUPなどの表示を行うクラス
//作成者　君島朝日
// 作成日　2021/1/18


class Fight_Effects :
    public Actor
{
private:
    class AnimSpriteComponent*  fight_effects_asc_;

    const int k_fight_effects_layer_;
    Vec2 fight_effects_size_; //大きさ
    Vec2 fight_effects_pos_;

    int fight_effects_time_;
    int fight_effects_next_;
    float fight_effects_count_;
    float fight_effects_deadcount_;
    const int k_fight_effects_Deadtime_;

    const int k_fight_effects_tex_[26];
    enum class fight_effects_frame_num : int
    {
        CLEAR = 1,    
        LOSE = 1,
        WIN = 1,
        FIGHT = 1,     //
        READY = 1,
        TIMEUP = 1,
        DRAW = 1,
        SCORE = 1,
        WAKU = 1,
        CLEAR_ANIM = 6,     //
        LOSE_ANIM = 4,
        WIN_ANIM = 8,
        FIGHT_IN = 4,     //
        FIGHT_OUT = 4,     //
        READY_IN = 4,
        READY_OUT = 4,
        TIMEUP_IN = 4,
        TIMEUP_OUT = 4,
        DRAW_IN = 8,
        DRAW_OUT = 4,
        SCORE_IN = 5,
        SCORE_OUT = 4,
        WAKU_IN = 5,
        WAKU_OUT = 5,

        END = -1,
    };

   
public:
    Fight_Effects(Game* game,Vec2 pos, Vec2 size, int time, int texnum);
    ~Fight_Effects();
    void UpdateActor(float delttime)override;
    void Fight_Effects_texchange(int texnum);
    
    enum class fight_effects_Motion :int
    {
        CLEAR,     //登場
        LOSE,
        WIN,
        FIGHT,     //
        READY,
        TIMEUP,
        DRAW,
        SCORE,
        WAKU,
        CLEAR_ANIM,     //登場
        LOSE_ANIM,
        WIN_ANIM,
        FIGHT_IN,     //
        FIGHT_OUT,     //
        READY_IN,
        READY_OUT,
        TIMEUP_IN,
        TIMEUP_OUT,
        DRAW_IN,
        DRAW_OUT,
        SCORE_IN,
        SCORE_OUT,
        WAKU_IN,
        WAKU_OUT,
        END = -1,
    };


};

