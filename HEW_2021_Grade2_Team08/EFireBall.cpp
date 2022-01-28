#include "EFireBall.h"
#include "Texture.h"
#include "sound.h"
#include "AnimSpriteComponent.h"
#include "Enemy.h"
#include "Fireball.h"

#define _USE_MATH_DEFINES
#include <math.h>
EFireBall::EFireBall(Game* game, int layer, Vec2 pos, Enemy* player, Stage* stg):
    Skill(game)                                                                ,
    k_fireball_tex_(LoadTexture(L"Data/Image/skill/Eff_Fireball_Sheet.png"))   ,
    k_fireball_size_(Vec2(70, 70))                                             ,
    k_fireball_layer_(layer)                                                   ,
    k_fireball_g_(9.8)                                                         ,
    k_fireball_pos_init_(Vec2(pos.x_, pos.y_ - 20))                            ,
    k_fireball_deg_(40)                                                        ,
    k_fireball_distination_(Vec2(113 * 3 + (k_fireball_size_.x_ / 2), pos.y_)) ,
    k_Is_player_(false)                                                        ,
    k_fireball_delay_(6)                                                       ,
    k_fireball_SE_{                                                            
    LoadSound(L"Data/SE/Skill/fireball_init.wav"),                             
    LoadSound(L"Data/SE/Skill/fireball_atack.wav"),                            
    LoadSound(L"Data/SE/Skill/fireball_end.wav")}                              ,
    fireball_atk_affirmation(false)                                            
{
    fireball_pos_ = k_fireball_pos_init_;
    fireball_asc_ = new AnimSpriteComponent(this, 250);
    //fireball_asc_->SetTexture(k_fireball_tex_, k_fireball_size_, Vec2(0, 0), Vec2(1, 1));

    fireball_asc_->SetAnimTextures(k_fireball_tex_, k_fireball_size_, static_cast<int>(fireball_frame_num::IDLE), 5.f);

    SetPosition(Vec2(-100, 0));
    if (k_Is_player_ == false)
    {
        k_fireball_distination_ = (Vec2(113 * 3, pos.y_));
        fireball_stage_num_ = player->GetPosIndex() - 3;
    }

    PlaySound(k_fireball_SE_[static_cast<int>(fireball_SE_num::ADVENT)], 0);

    attackcount_ = 0;
    stg_ = stg;
}

EFireBall::~EFireBall()
{
}

void EFireBall::UpdateActor(float delta_time)
{
    Actor::UpdateActor(delta_time);

    //アニメーションに合わせて発射する
    attackcount_ += 5 * delta_time;

    if (attackcount_ >= k_fireball_delay_)
    {

        if (fireball_atk_affirmation == false)
        {
            fireball_atk_affirmation = true;
            PlaySound(k_fireball_SE_[static_cast<int>(fireball_SE_num::ATTACK)], 0);
        }

        Fireball_parabola(delta_time);
        Fireball_exprosion();
    }
}

void EFireBall::Fireball_parabola(float delta_time)
{
    float rad = k_fireball_deg_ * M_PI / 180;
    float g = k_fireball_g_ / delta_time;

    float v = sqrt(g * k_fireball_distination_.x_ / (2 * sinf(rad) * cosf(rad)));
    float t = k_fireball_distination_.x_ / (v * cosf(rad));

    fireball_pos_.x_ += (k_fireball_distination_.x_ / t) * delta_time;

    float x = fireball_pos_.x_ - k_fireball_pos_init_.x_;

    float y = fireball_pos_.y_ + 50 + -1 *
        (x * tan(rad) - (g / ((2 * v * v) * cos(rad) * cos(rad)) * x * x));

    float rot = 0;
    if (k_Is_player_)
    {
        SetPosition(Vec2(fireball_pos_.x_, y));
        //スプライトを放物線に合わせて回転させる
        rot = ((double)(0 - (double)k_fireball_deg_) + (((double)k_fireball_deg_ * 2) * (x / k_fireball_distination_.x_))) * M_PI / 180;
    }
    else
    {
        SetPosition(Vec2(k_fireball_pos_init_.x_ - x, y));
        //スプライトを放物線に合わせて回転させる
        rot = -1 * ((double)(180 - (double)k_fireball_deg_) + (((double)k_fireball_deg_ * 2) * (x / k_fireball_distination_.x_))) * M_PI / 180;
    }
    fireball_asc_->SetRot(rot);
}

void EFireBall::Fireball_exprosion()
{
    if (k_Is_player_)
    {
        if (GetPosition().x_ > k_fireball_pos_init_.x_ + k_fireball_distination_.x_)
        {
            stg_->SetSnow(fireball_stage_num_);

            auto a = new Firepillar(GetGame(), fireball_stage_num_, k_Is_player_, stg_, k_fireball_layer_);
            PlaySound(k_fireball_SE_[static_cast<int>(fireball_SE_num::LEAVE)], 0);
            SetState(Dead);
        }
    }
    else
    {
        if (GetPosition().x_ < k_fireball_pos_init_.x_ - k_fireball_distination_.x_)
        {
            stg_->SetSnow(fireball_stage_num_);

            auto a = new Firepillar(GetGame(), fireball_stage_num_, k_Is_player_, stg_, k_fireball_layer_);
            PlaySound(k_fireball_SE_[static_cast<int>(fireball_SE_num::LEAVE)], 0);
            SetState(Dead);
        }
    }
}
