#pragma once
#include "Skill.h"
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"
#include "Player.h"

class Armor :
    public Skill
{
    class AnimSpriteComponent* armor_asc_;
    class Actor* temp_;
    class AnimSpriteComponent* effect_asc_;

    int     armor_state_;            //アーマーの状態
    float     motioncount_;             //アーマーの登場/退場アニメの終わる時間を数える
    int     deathcount;            //投げた玉の数を数える

    int     armor_life_;        //アーマーのライフポイント

    const int k_effect_tex;
    const int k_armor_efect_time;                   //アーマーが一段階減少するまでの時間
    const int k_armor_tex_[5];                       //アーマーのテクスチャ
    const Vec2 k_armor_pos_;                         //アーマーのプレイヤーからの相対的な位置
    const Vec2 k_armor_size_;                      //アーマーの大きさ

    Player* player_;
    enum class armor_frame_num : int
    {
        ADVENT = 4,
        LIFE3 = 1,     //
        LIFE2 = 1,
        LIFE1 = 1,
        LEAVE = 4,
    };

    enum class armor_Motion :int
    {
        ADVENT,     //登場
        LIFE3,     //
        LIFE2,      
        LIFE1,
        LEAVE,      //退場
    };


public:
    Armor(Game* game, Vec2(pos), Player* player);
    void UpdateActor(float deltatime) override;
    void Armor_death_check(float deltatime);
    void Armor_texchange(int texnum);
};

