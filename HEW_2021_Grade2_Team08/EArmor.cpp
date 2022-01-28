#include "EArmor.h"
#include "Texture.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"
#include "Enemy.h"
#include "Math.h"
#include "sound.h"
EArmor::EArmor(Game* game, Vec2 pos, Enemy* player, Vec2 player_hitsize):
    Skill(game)                                     ,
    k_armor_pos_(Vec2(-30, 20))                     ,
    k_armor_size_(Vec2(64 , 64))                    ,
    k_armor_efect_time(120)                         ,
    k_armor_hitsize_(player_hitsize + Vec2(50,5))   ,
    k_Is_player_(false)                             ,
    k_armor_tex_{
    	LoadTexture(L"Data/Image/skill/armor_in-Sheet.png"),
    	LoadTexture(L"Data/Image/skill/armor_life3.png")   ,
    	LoadTexture(L"Data/Image/skill/armor_life2.png")   ,
    	LoadTexture(L"Data/Image/skill/armor_life1.png")   ,
    	LoadTexture(L"Data/Image/skill/armor_brake-Sheet.png")
    },
    k_effect_tex(LoadTexture(L"Data/Image/skill/armor_effect_Sheet.png")),
    sounds_{
        LoadSound(L"Data/SE/Skill/armor_end.wav"),
        LoadSound(L"Data/SE/Skill/armor_hit.wav")
    }
{
    this->motioncount_ = 0;
    this->armor_state_ = static_cast<int>(armor_Motion::ADVENT);

    this->armor_asc_ = new AnimSpriteComponent(this, 150);

    armor_life_ = 3;
    Armor_texchange(static_cast<int>(armor_Motion::ADVENT));
    enemy_ = player;
    enemy_->GetPosition();

    this->SetPosition(enemy_->GetPosition() - k_armor_pos_);

    //エフェクト側の設定
    temp_ = new Actor(game);
    effect_asc_ = new AnimSpriteComponent(temp_, 260);
    effect_asc_->SetAnimTextures(k_effect_tex, Vec2(64 * 1.5, 64 * 1.5), 7, 5.f);
    temp_->SetPosition(enemy_->GetPosition());

    //当たり判定の設定
    SetCollision(Rect(enemy_->GetCollision().center_, k_armor_hitsize_));
}
EArmor::~EArmor()
{
    PlaySound(sounds_[0], 0);
    GetGame()->RemoveEArmor(this);
    SetState(Dead);
}

void EArmor::UpdateActor(float deltatime)
{
    Actor::UpdateActor(deltatime);

    Armor_death_check(deltatime);

    temp_->SetPosition(enemy_->GetPosition());

    SetPosition(enemy_->GetPosition() - k_armor_pos_);

    //当たり判定の設定
    SetCollision(Rect(enemy_->GetCollision().center_, k_armor_hitsize_));

    if (armor_state_ == static_cast<int>(armor_Motion::ADVENT))
    {
        //登場中の場合はアニメが終わるのを待ってから攻撃状態に移る処理
        motioncount_ += 5 * deltatime;
        if (motioncount_ >= static_cast<int>(armor_frame_num::ADVENT))
        {
            Armor_texchange(static_cast<int>(armor_Motion::LIFE3));
            motioncount_ = 0;
        }
    }
    else if (armor_state_ != static_cast<int>(armor_Motion::LEAVE))
    {
        switch (armor_life_)
        {
        case 3:
            Armor_texchange(static_cast<int>(armor_Motion::LIFE3));
            break;
        case 2:
            Armor_texchange(static_cast<int>(armor_Motion::LIFE2));
            break;
        case 1:
            Armor_texchange(static_cast<int>(armor_Motion::LIFE1));
            break;
        case 0:
            Armor_texchange(static_cast<int>(armor_Motion::LEAVE));
            break;
        default:
            Armor_texchange(static_cast<int>(armor_Motion::LEAVE));
            break;
        }

        motioncount_ += 5 * deltatime;
        if (motioncount_ >= k_armor_efect_time)
        {
            armor_life_--;
            motioncount_ = 0;
        }

        if (armor_state_ == static_cast<int>(armor_Motion::LEAVE))
            motioncount_ = 0;
    }
}

void EArmor::Armor_death_check(float deltatime)
{
    if (armor_state_ == static_cast<int>(armor_Motion::LEAVE))
    {
        motioncount_ += 5 * deltatime;
        if (motioncount_ >= static_cast<int>(armor_frame_num::LEAVE))
        {
            SetState(Dead);
            temp_->SetState(Dead);
        }
    }
}

void EArmor::Armor_texchange(int texnum)
{
    armor_state_ = texnum;

    this->RemoveComponent(armor_asc_);
    this->GetGame()->RemoveSprite(armor_asc_);
    armor_asc_ = new AnimSpriteComponent(this, 150);

    if (texnum == static_cast<int>(armor_Motion::ADVENT))
    {
        armor_asc_->SetAnimTextures(k_armor_tex_[texnum], k_armor_size_, static_cast<int>(armor_frame_num::ADVENT), 5.f);
    }

    if (texnum == static_cast<int>(armor_Motion::LIFE3))
    {
        armor_asc_->SetAnimTextures(k_armor_tex_[texnum], k_armor_size_, static_cast<int>(armor_frame_num::LIFE3), 5.f);
        //idle_timeto_ = static_cast<int>(charaA_frame_num::ATTACK); //一定時間後に待機状態に
    }

    if (texnum == static_cast<int>(armor_Motion::LIFE2))
    {
        armor_asc_->SetAnimTextures(k_armor_tex_[texnum], k_armor_size_, static_cast<int>(armor_frame_num::LIFE2), 5.f);
        //idle_timeto_ = static_cast<int>(charaA_frame_num::ATTACK); //一定時間後に待機状態に
    }

    if (texnum == static_cast<int>(armor_Motion::LIFE1))
    {
        armor_asc_->SetAnimTextures(k_armor_tex_[texnum], k_armor_size_, static_cast<int>(armor_frame_num::LIFE1), 5.f);
        //idle_timeto_ = static_cast<int>(charaA_frame_num::ATTACK); //一定時間後に待機状態に
    }

    if (texnum == static_cast<int>(armor_Motion::LEAVE))
    {
        armor_asc_->SetAnimTextures(k_armor_tex_[texnum], k_armor_size_, static_cast<int>(armor_frame_num::LEAVE), 5.f);
    }
}
bool EArmor::Get_Isplayer()
{
    return false;
}

void EArmor::Set_Armorhit(int power)
{
    armor_life_ -= power;
    PlaySound(sounds_[1], 0);
	if (armor_state_ != static_cast<int>(armor_Motion::LEAVE)
		&& armor_state_ != static_cast<int>(armor_Motion::ADVENT)
		)
	motioncount_ = 0;
}

void EArmor::SetDead()
{
    SetState(Dead);
    temp_->SetState(Dead);
}
