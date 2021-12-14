#include "Armor.h"

#include "Armor.h"
#include "Bullet.h"

Armor::Armor(Game* game, Vec2 pos, Player* player) : Skill(game)
, k_armor_pos_(Vec2(-30, 20))
, k_armor_size_(Vec2(64 , 64))
,k_armor_efect_time(60)
, k_armor_tex_{
		LoadTexture(L"Data/Image/skill/armor_in-Sheet.png")
		,LoadTexture(L"Data/Image/skill/armor_life3.png")
		,LoadTexture(L"Data/Image/skill/armor_life2.png")
		,LoadTexture(L"Data/Image/skill/armor_life1.png")
		,LoadTexture(L"Data/Image/skill/armor_brake-Sheet.png")

	}
{
	
	this->motioncount_ = 0;
	this->armor_state_ = static_cast<int>(armor_Motion::ADVENT);

	this->armor_asc_ = new AnimSpriteComponent(this, 150);

	armor_life_ = 3;
	Armor::Armor_texchange(static_cast<int>(armor_Motion::ADVENT));
	player_ = player;
	player_->GetPosition();

	this->SetPosition(player_->GetPosition() - k_armor_pos_);
}

void Armor::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);

	Armor::Armor_death_check(deltatime);

	SetPosition(player_->GetPosition() - k_armor_pos_);

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
	else if(armor_state_ != static_cast<int>(armor_Motion::LEAVE))
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

//アーマーのテクスチャを切り替える処理
void Armor::Armor_texchange(int texnum)
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

//アーマーの退場アニメが終わったら消え失せる処理
void Armor::Armor_death_check(float deltatime)
{
	if (armor_state_ == static_cast<int>(armor_Motion::LEAVE))
	{
		motioncount_ += 5 * deltatime;
		if (motioncount_ >= static_cast<int>(armor_frame_num::LEAVE))
		{
			SetState(Dead);
		}
	}
}
