#include "IceWall.h"



IceWall::IceWall(Game* game, Vec2 playerpos,int layer,bool Is_player) : Skill(game)
,k_wall_pos_(Vec2(35,55))
,wall_size_(Vec2(-150,-150))
,k_wall_layer_(layer + 1)
,k_wall_cost_(2)
{
	k_wall_tex_[0] = LoadTexture(L"Data/Image/skill/Icewall_anim_Right.png");
	k_wall_tex_[1] = LoadTexture(L"Data/Image/skill/IceWall_Right.png");
	k_wall_tex_[2] = LoadTexture(L"Data/Image/skill/Icewall_breakeanim_Right.png");

	if (Is_player)
	{
		this->SetPosition(playerpos + k_wall_pos_);
	}
	else
	{
		k_wall_tex_[0] = LoadTexture(L"Data/Image/skill/IceWall_anim.png");
		k_wall_tex_[1] = LoadTexture(L"Data/Image/skill/IceWall.png");
		k_wall_tex_[2] = LoadTexture(L"Data/Image/skill/Icewall_breakeanim.png");

		wall_size_ = (Vec2(wall_size_.x_ * -1, wall_size_.y_ * -1));

		this->SetPosition(Vec2(playerpos.x_ - k_wall_pos_.x_ * 1.3, playerpos.y_ + k_wall_pos_.y_));
	}
	this->wall_asc_ = new AnimSpriteComponent(this, k_wall_layer_ );
	IceWall::IceWall_texchange(static_cast<int>(wall_Motion::ADVENT));

}

void IceWall::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);

	switch (wall_state_)
	{
	case static_cast<int>(wall_Motion::ADVENT):
		//登場中
		motioncount_ += 5 * deltatime;
		if (motioncount_ >= static_cast<int>(wall_frame_num::ADVENT))
		{
			IceWall_texchange(static_cast<int>(wall_Motion::IDLE));
			motioncount_ = 0;
		}
		break;
	case static_cast<int>(wall_Motion::IDLE) :
		//通常中
		motioncount_ += 5 * deltatime;
		if (motioncount_ >= 35)
		{
			IceWall_texchange(static_cast<int>(wall_Motion::LEAVE));
			motioncount_ = 0;
		}
		break;
	case static_cast<int>(wall_Motion::LEAVE):
		//退場中
		motioncount_ += 5 * deltatime;
		if (motioncount_ >= static_cast<int>(wall_frame_num::LEAVE))
		{
			SetState(Dead);
		}
		break;
	default:
		break;
	}
	
}

void IceWall::IceWall_texchange(int texnum)
{
	wall_state_ = texnum;

	this->RemoveComponent(wall_asc_);
	this->GetGame()->RemoveSprite(wall_asc_);
	wall_asc_ = new AnimSpriteComponent(this, k_wall_layer_);

	if (texnum == static_cast<int>(wall_Motion::ADVENT))
	{
		wall_asc_->SetAnimTextures(k_wall_tex_[texnum], wall_size_, static_cast<int>(wall_frame_num::ADVENT), 5.f);
	}

	if (texnum == static_cast<int>(wall_Motion::IDLE))
	{
		wall_asc_->SetAnimTextures(k_wall_tex_[texnum], wall_size_, static_cast<int>(wall_frame_num::IDLE), 5.f);
		//idle_timeto_ = static_cast<int>(charaA_frame_num::ATTACK); //一定時間後に待機状態に
	}

	if (texnum == static_cast<int>(wall_Motion::LEAVE))
	{
		//最後のアニメだけ向きが違うためプログラム側で対応します
		wall_size_ = (Vec2(wall_size_.x_ * -1, wall_size_.y_ * -1));

		wall_asc_->SetAnimTextures(k_wall_tex_[texnum], wall_size_, static_cast<int>(wall_frame_num::LEAVE), 5.f);
	}

}
