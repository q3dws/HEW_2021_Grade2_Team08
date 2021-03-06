#include "BigBullet.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Player.h"
#include "Armor.h"
#include "IceWall.h"
#include "Golem.h"
#include "sound.h"
#include "Enemy.h"
#include "EGolem.h"
#include "EArmor.h"
#include "EIceWall.h"
BigBullet::BigBullet(Game* game, bool Is_player, int layer, Vec2 pos) : Skill(game)
, k_bigsnow_vel_(10)
, k_bigsnow_tex_{LoadTexture(L"Data/Image/skill/snowball_big.png")
	, LoadTexture(L"Data/Image/Eff_Iceball_Sheet.png")
}
, k_bigsnow_Grow(Vec2(40,40))
,k_bigsnow_Growrot_(180)
,k_Is_player_(Is_player)
,k_bigsnow_layer_(layer + 1)
, bigsnow_pos_(pos)
, bigsnow_state_(static_cast<int>(bigsnow_Motion::IDLE))
,motioncount_(0)
, k_bigsnow_seplus_min_(3)
, k_bigsnow_SE_{
	LoadSound(L"Data/SE/Skill/bigsnow_init.wav"),
	LoadSound(L"Data/SE/Skill/bigsnow_hit.wav"),
}
{
	bigsnow_size_ = Vec2(20, 20);

	bigsnow_asc_ = new AnimSpriteComponent(this, k_bigsnow_layer_);
	//bigsnow_asc_->SetTexture(k_bigsnow_tex_, bigsnow_size_, Vec2(0, 0), Vec2(1, 1));
	bigsnow_asc_->SetAnimTextures(k_bigsnow_tex_[static_cast<int>(bigsnow_Motion::IDLE)], bigsnow_size_, static_cast<int>(bigsnow_frame_num::IDLE), 5.f);

	SetPosition(bigsnow_pos_);

	SetCollision(Rect(bigsnow_pos_, bigsnow_size_));
	bigsnow_rot_ = 0;
	bigsnow_power_ = 1;
	bigsnow_distance_count_ = 0;

	PlaySound(k_bigsnow_SE_[static_cast<int>(bigsnow_SE_num::ADVENT)], 0);
}

BigBullet::~BigBullet()
{
}

void BigBullet::UpdateActor(float delta_time)
{
	Actor::UpdateActor(delta_time);
	BigBullet::BigBullet_move(delta_time);
	BigBullet::BigBullet_ColligionCheck(delta_time);

	if (bigsnow_state_ == static_cast<int>(bigsnow_Motion::LEAVE))
	{
		motioncount_ += 5 * delta_time;
		if (motioncount_ >= static_cast<int>(bigsnow_frame_num::LEAVE))
		{
			
			SetState(Dead);
		}
	}
}

void BigBullet::BigBullet_move(float delta_time)
{
	if (bigsnow_state_ == static_cast<int>(bigsnow_Motion::LEAVE))
	{
		return;
	}

	bigsnow_size_ += k_bigsnow_Grow * delta_time;

	bigsnow_asc_->SetSize(bigsnow_size_);
	
	if (k_Is_player_)
	{
		SetPosition(Vec2(GetPosition().x_ + k_bigsnow_vel_, GetPosition().y_));
		bigsnow_rot_ += k_bigsnow_Growrot_ * delta_time;

		//??????????????
		MoveCollison(Vec2(k_bigsnow_vel_, 0));
	}
	else
	{
		SetPosition(Vec2(GetPosition().x_ - k_bigsnow_vel_, GetPosition().y_));
		bigsnow_rot_ -= k_bigsnow_Growrot_ * delta_time;
		
		//??????????????
		MoveCollison(Vec2(-k_bigsnow_vel_, 0));
	}
	bigsnow_asc_->SetRot(bigsnow_rot_ * M_PI / 180);

	
}

void BigBullet::BigBullet_ColligionCheck(float delta_taime)
{
	//?????????????????????A?b?v
	bigsnow_distance_count_ += k_bigsnow_Growrot_ * delta_taime;
	if (bigsnow_distance_count_ >= 100)
	{
		bigsnow_power_++;
		bigsnow_distance_count_ = 0;
	}


	if (GetPosition().x_ > WINDOW_WIDTH + bigsnow_size_.x_)
		SetState(Dead);

	if (GetPosition().x_ < 0 - bigsnow_size_.x_)
		SetState(Dead);

	//?X??????????????????
	if (GetGame()->GetIceWallSize() != 0)
	{
		for (int i = 0; i < GetGame()->GetIceWallSize(); i++)
		{
			if (CollisionRC_NoInd(GetGame()->GetIceWall(i), this) && bigsnow_state_ == static_cast<int>(bigsnow_Motion::IDLE))
			{
				if (GetGame()->GetIceWall(i)->Get_Isplayer() != k_Is_player_)
				{
					//???u?????W??1?_???[?W??????????????????????????????
					if (bigsnow_power_ >= 2)
						GetGame()->GetIceWall(i)->Set_IceWallHit(bigsnow_power_ + 1);
					else
						GetGame()->GetIceWall(i)->Set_IceWallHit(bigsnow_power_ + 1);

					BigBullet_texchange(static_cast<int>(bigsnow_Motion::LEAVE));
				}
			}
		}
	}
    for (int i = 0; i < GetGame()->GetEIceWalls().size(); ++i)
    {
        if (GetGame()->GetEIceWalls().at(i))
        {
            if (GetGame()->GetEIceWalls().at(i)->Get_Isplayer() != k_Is_player_)
            {
                if (CollisionRC_NoInd(GetGame()->GetEIceWalls().at(i), this) && bigsnow_state_ == static_cast<int>(bigsnow_Motion::IDLE))
                {
                    GetGame()->GetEIceWalls().at(i)->Set_IceWallHit(bigsnow_power_ + 1);
                    BigBullet_texchange(static_cast<int>(bigsnow_Motion::LEAVE));
                }
            }
        }
    }

	//?A?[?}?[??????????????
	if (GetGame()->GetArmorSize() != 0)
	{
		for (int i = 0; i < GetGame()->GetArmorSize(); i++)
		{
			if (CollisionRC_NoInd(GetGame()->GetArmor(i), this) && bigsnow_state_ == static_cast<int>(bigsnow_Motion::IDLE))
			{
				if (GetGame()->GetArmor(i)->Get_Isplayer() != k_Is_player_)
				{
					GetGame()->GetArmor(i)->Set_Armorhit(bigsnow_power_);
					BigBullet_texchange(static_cast<int>(bigsnow_Motion::LEAVE));
					//SetState(Dead);
				}
			}
		}
	}
    for (int i = 0; i < GetGame()->GetEArmor().size(); ++i)
    {
        if (GetGame()->GetEArmor().at(i))
        {
            if (GetGame()->GetEArmor().at(i)->Get_Isplayer() != k_Is_player_)
            {
                if (CollisionRC_NoInd(GetGame()->GetEArmor().at(i), this) && bigsnow_state_ == static_cast<int>(bigsnow_Motion::IDLE))
                {
                    GetGame()->GetEArmor().at(i)->Set_Armorhit(bigsnow_power_);
                    BigBullet_texchange(static_cast<int>(bigsnow_Motion::LEAVE));
                }
            }
        }
    }


	//?S?[??????????????????
	if (GetGame()->GetGolemSize() != 0)
	{
		for (int i = 0; i < GetGame()->GetGolemSize(); i++)
		{
			if (CollisionRC_NoInd(GetGame()->GetGolem(i), this) && bigsnow_state_ == static_cast<int>(bigsnow_Motion::IDLE))
			{
				if (GetGame()->GetGolem(i)->Get_Isplayer() != k_Is_player_)
				{
					GetGame()->GetGolem(i)->Set_Golemhit(bigsnow_power_);
					BigBullet_texchange(static_cast<int>(bigsnow_Motion::LEAVE));
				}
			}
		}
	}

    for (int i = 0; i < GetGame()->GetEGolems().size(); ++i)
    {
        if (GetGame()->GetEGolems().at(i))
        {
            if (GetGame()->GetEGolems().at(i)->Get_Isplayer() != k_Is_player_)
            {
                if (CollisionRC_NoInd(GetGame()->GetEGolems().at(i), this) && bigsnow_state_ == static_cast<int>(bigsnow_Motion::IDLE))
                {
                    GetGame()->GetEGolems().at(i)->Set_Golemhit(bigsnow_power_);
                    BigBullet_texchange(static_cast<int>(bigsnow_Motion::LEAVE));
                }
            }
        }
    }


	if (k_Is_player_)//?v???C???[?????e
	{
		//?G???q?b?g??????????????
        if(GetGame()->GetPlayer2p())
		if (CollisionRC_NoInd(GetGame()->GetPlayer2p(), this) && bigsnow_state_ == static_cast<int>(bigsnow_Motion::IDLE))
		{
			GetGame()->GetPlayer2p()->Player_SetHit(bigsnow_power_ * 2);

			GetGame()->GetScoreManager()->AddScore(bigsnow_power_);

			BigBullet_texchange(static_cast<int>(bigsnow_Motion::LEAVE));
		}
        if (GetGame()->GetEnemy())
        {
            if (CollisionRC_NoInd(GetGame()->GetEnemy(), this) && bigsnow_state_ == static_cast<int>(bigsnow_Motion::IDLE))
            {
                //GetGame()->GetEnemy()->Player_SetHit(bigsnow_power_ * 2);

                GetGame()->GetScoreManager()->AddScore(bigsnow_power_);

                BigBullet_texchange(static_cast<int>(bigsnow_Motion::LEAVE));
            }
        }
	}
	else
	{
		//?v???C???[1???q?b?g??????????????
		if (CollisionRC_NoInd(GetGame()->GetPlayer(), this) && bigsnow_state_ == static_cast<int>(bigsnow_Motion::IDLE))
		{
			GetGame()->GetPlayer()->Player_SetHit(bigsnow_power_ * 2);

			GetGame()->GetScoreManager()->EnemyAddScore(bigsnow_power_);

			BigBullet_texchange(static_cast<int>(bigsnow_Motion::LEAVE));
		}

	}
}

void BigBullet::BigBullet_texchange(int texnum)
{
	bigsnow_state_ = texnum;

	this->RemoveComponent(bigsnow_asc_);
	this->GetGame()->RemoveSprite(bigsnow_asc_);
	bigsnow_asc_ = new AnimSpriteComponent(this, k_bigsnow_layer_);

	bigsnow_rot_ = 0;

	if (texnum == static_cast<int>(bigsnow_Motion::LEAVE))
	{
		if(bigsnow_power_ >= k_bigsnow_seplus_min_)
		PlaySound(k_bigsnow_SE_[static_cast<int>(bigsnow_SE_num::LEAVE)], 0);

		bigsnow_asc_->SetAnimTextures(k_bigsnow_tex_[texnum], bigsnow_size_, static_cast<int>(bigsnow_frame_num::LEAVE), 5.f);
	}

}
