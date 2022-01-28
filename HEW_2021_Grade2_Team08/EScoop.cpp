#include "EScoop.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Player.h"
#include "Golem.h"
#include "Armor.h"
#include "Game.h"
#include "Enemy.h"
#include "sound.h"
EScoop::EScoop(Game* game, int layer, Vec2 pos, Stage* stg, Enemy* player):
    Skill(game)                                                             ,
    k_scoop_tex_(LoadTexture(L"Data/Image/skill/snowball_big.png"))         ,
    k_scoop_size_(Vec2(30, 30))                                             ,
    k_scoop_layer_(layer)                                                   ,
    k_scoop_g_(9.8)                                                         ,
    k_scoop_pos_init_(Vec2(pos.x_, pos.y_ + 50))                            ,
    k_scoop_deg_(60)                                                        ,
    k_scoop_distination_(Vec2(113 * 3 + (k_scoop_size_.x_ / 2), pos.y_))    ,
    k_Is_player_(false)                                                     ,
    stg_(stg)                                                               ,
    k_scoop_SE_{LoadSound(L"Data/SE/Skill/scoop_icepiller.wav")}        
{
    scoop_pos_ = pos;
    scoop_asc_ = new SpriteComponent(this, 250);
    scoop_asc_->SetTexture(k_scoop_tex_, k_scoop_size_, Vec2(0, 0), Vec2(1, 1));

    if (k_Is_player_ == false)
    {
        k_scoop_distination_ = (Vec2(113 * 3, pos.y_));
        scoop_stage_num_ = player->GetPosIndex() - 3;
    }

    SetPosition(k_scoop_pos_init_);
}

EScoop::~EScoop()
{
    PlaySound(k_scoop_SE_, 0);
}

void EScoop::UpdateActor(float delta_time)
{
    Actor::UpdateActor(delta_time);
    Scoop_parabola(delta_time);
    Scoop_exprosion();
}

void EScoop::Scoop_parabola(float delta_time)
{
    //Žg‚¢•û@Šp“x‚Æd—Í‰Á‘¬“x‚Æ’…’e“_‚ðÝ’è‚·‚é‚ÆŽ©“®‚Å•ú•¨ü‰^“®‚ª¶¬‚³‚ê‚Ü‚·

    float rad = k_scoop_deg_ * M_PI / 180;
    float g = k_scoop_g_ / delta_time;

    float v = sqrt(g * k_scoop_distination_.x_ / (2 * sinf(rad) * cosf(rad)));
    float t = k_scoop_distination_.x_ / (v * cosf(rad));

    scoop_pos_.x_ += (k_scoop_distination_.x_ / t) * delta_time;

    float x = scoop_pos_.x_ - k_scoop_pos_init_.x_;

    float y = scoop_pos_.y_ + 50 + -1 *
        (x * tan(rad) - (g / ((2 * v * v) * cos(rad) * cos(rad)) * x * x));

    if (k_Is_player_)
    {
        SetPosition(Vec2(scoop_pos_.x_, y));
    }
    else
    {
        SetPosition(Vec2(k_scoop_pos_init_.x_ - x, y));
    }
}

void EScoop::Scoop_exprosion()
{
    if (k_Is_player_)
    {
        if (GetPosition().x_ > k_scoop_pos_init_.x_ + k_scoop_distination_.x_)
        {
            /*auto a = new MiniBullet(GetGame(), k_scoop_tex_, GetPosition(), true,k_Is_player_);
            auto b = new MiniBullet(GetGame(), k_scoop_tex_, GetPosition(), false, k_Is_player_);*/

            Scoop_summon_icepiller();

            SetState(Dead);
        }
    }
    else
    {
        if (GetPosition().x_ < k_scoop_pos_init_.x_ - k_scoop_distination_.x_)
        {
            /*auto a = new MiniBullet(GetGame(), k_scoop_tex_, GetPosition(), true, k_Is_player_);
            auto b = new MiniBullet(GetGame(), k_scoop_tex_, GetPosition(), false, k_Is_player_);*/

            Scoop_summon_icepiller();

            SetState(Dead);
        }
    }
}

void EScoop::Scoop_summon_icepiller()
{
    int i = 6;
    int j = 12;

    if (scoop_stage_num_ >= 0)
    {
        i = 6;
        j = 12;
    }

    if (scoop_stage_num_ >= 6)
    {
        i = -6;
        j = 6;
    }

    if (scoop_stage_num_ >= 12)
    {
        i = -12;
        j = -6;
    }

    auto a = new Icepillar(GetGame(), scoop_stage_num_, k_Is_player_, stg_, k_scoop_layer_);
    auto b = new Icepillar(GetGame(), scoop_stage_num_ + i
        , k_Is_player_, stg_, k_scoop_layer_ + i);

    auto c = new Icepillar(GetGame(), scoop_stage_num_ + j
        , k_Is_player_, stg_, k_scoop_layer_ + j);
}
