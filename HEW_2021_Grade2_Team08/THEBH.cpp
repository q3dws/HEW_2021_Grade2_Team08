#include "THEBH.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"
#include "sound.h"


THEBH::THEBH(Game* game, int layer) : Actor(game)
, k_BH_pos_(Vec2(BH_POS_X, BH_POS_Y))
, BH_size_(Vec2(BLACKHOLE_SIZE, BLACKHOLE_SIZE))
, k_BH_layer_(layer + 1)
, k_BH_cost_(2)
, k_BH_hitsize_(Vec2(90, 90))
, BH_hp_(5)
, k_BH_SE_{
	0,
	0,
	0,
}
{
	k_BH_tex_[0] = LoadTexture(L"Data/Image/black hole_in.png");
	k_BH_tex_[1] = LoadTexture(L"Data/Image/black hole_anime.png");
	k_BH_tex_[2] = LoadTexture(L"Data/Image/black hole_out.png");
	k_BH_tex_[3] = LoadTexture(L"Data/Image/black hole_anime.png");


	this->SetPosition(k_BH_pos_);
	
	this->BH_asc_ = new AnimSpriteComponent(this, k_BH_layer_);
	THEBH::THEBH_texchange(static_cast<int>(BH_Motion::ADVENT));

	hitcount_ = 0;




}

THEBH::~THEBH()
{
	
}


void THEBH::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);

	switch (BH_state_)
	{
	case static_cast<int>(BH_Motion::ADVENT):
		//ìoèÍíÜ
		motioncount_ += 5 * deltatime;
		if (motioncount_ >= static_cast<int>(BH_frame_num::ADVENT))
		{
			//PlaySound(k_BH_SE_[static_cast<int>(BH_SE_num::ADVENT)], 0);
			THEBH_texchange(static_cast<int>(BH_Motion::IDLE));
			motioncount_ = 0;
		}
		break;
	case static_cast<int>(BH_Motion::IDLE):
		//í èÌíÜ
		motioncount_ += 5 * deltatime;
		if (motioncount_ >= BASEUSETIME || BH_hp_ <= 0)
		{
			THEBH_texchange(static_cast<int>(BH_Motion::LEAVE));
			motioncount_ = 0;
		}

		break;
	case static_cast<int>(BH_Motion::LEAVE):
		//ëﬁèÍíÜ
		SetCollision(Rect(Vec2(0, 0), Vec2(0, 0)));
		motioncount_ += 5 * deltatime;
		if (motioncount_ >= static_cast<int>(BH_frame_num::LEAVE))
		{
			//RemoveActor
			SetState(Dead);
		}
		break;
	case static_cast<int>(BH_Motion::HIT):
		//ëﬁèÍíÜ
		hitcount_ += 5 * deltatime;
		if (hitcount_ >= static_cast<int>(BH_frame_num::HIT))
		{
			THEBH_texchange(static_cast<int>(BH_Motion::IDLE));

		}

		if (BH_hp_ <= 0)
		{
			THEBH_texchange(static_cast<int>(BH_Motion::LEAVE));
			motioncount_ = 0;
		}

		break;
	default:
		break;
	}

}

void THEBH::THEBH_texchange(int texnum)
{
	BH_state_ = texnum;

	this->RemoveComponent(BH_asc_);
	this->GetGame()->RemoveSprite(BH_asc_);
	BH_asc_ = new AnimSpriteComponent(this, k_BH_layer_);

	if (texnum == static_cast<int>(BH_Motion::ADVENT))
	{
		BH_asc_->SetAnimTextures(k_BH_tex_[texnum], BH_size_, static_cast<int>(BH_frame_num::ADVENT), 5.f);
	}

	if (texnum == static_cast<int>(BH_Motion::IDLE))
	{
		BH_asc_->SetAnimTextures(k_BH_tex_[texnum], BH_size_, static_cast<int>(BH_frame_num::IDLE), 5.f);
		//idle_timeto_ = static_cast<int>(charaA_frame_num::ATTACK); //àÍíËéûä‘å„Ç…ë“ã@èÛë‘Ç…
	}

	if (texnum == static_cast<int>(BH_Motion::LEAVE))
	{
		//PlaySound(k_BH_SE_[static_cast<int>(BH_SE_num::LEAVE)], 0);
		BH_asc_->SetAnimTextures(k_BH_tex_[texnum], BH_size_, static_cast<int>(BH_frame_num::LEAVE), 5.f);
	}

	if (texnum == static_cast<int>(BH_Motion::HIT))
	{
		//PlaySound(k_BH_SE_[static_cast<int>(BH_SE_num::HIT)], 0);
		BH_asc_->SetAnimTextures(k_BH_tex_[texnum], BH_size_, static_cast<int>(BH_frame_num::HIT), 5.f);
	}
}




//ïXÇÃï«Ç…ÉqÉbÉgÇµÇΩÇ∆Ç´Ç…åƒÇ‘ä÷êî
void THEBH::Set_THEBHHit(int power)
{
	if (BH_state_ == static_cast<int>(BH_Motion::IDLE) || BH_state_ == static_cast<int>(BH_Motion::HIT))
	{
		hitcount_ = 0;
		BH_hp_ -= power;
		THEBH_texchange(static_cast<int>(BH_Motion::HIT));
	}
}

