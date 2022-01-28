#include "Fireball.h"
#include "Armor.h"
#include "Golem.h"
#include "Player.h"
#include "IceWall.h"
#include "EIceWall.h"
#include "EArmor.h"
#include "EGolem.h"
#include "Enemy.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "sound.h"

Fireball::Fireball(Game* game, int layer, Vec2 pos, Player* player, Stage* stg, bool Is_player) : Skill(game)
, k_fireball_tex_(LoadTexture(L"Data/Image/skill/Eff_Fireball_Sheet.png"))
, k_fireball_size_(Vec2(70, 70))
, k_fireball_layer_(layer)
, k_fireball_g_(9.8)
, k_fireball_pos_init_(Vec2(pos.x_, pos.y_ - 20))
, k_fireball_deg_(40)
, k_fireball_distination_(Vec2(113 * 3 + (k_fireball_size_.x_ / 2), pos.y_))
, k_Is_player_(Is_player)
, k_fireball_delay_(6)
, k_fireball_SE_{
	LoadSound(L"Data/SE/Skill/fireball_init.wav"),
	LoadSound(L"Data/SE/Skill/fireball_atack.wav"),
	LoadSound(L"Data/SE/Skill/fireball_end.wav")}
, fireball_atk_affirmation(false)
{
	fireball_pos_ = k_fireball_pos_init_;
	fireball_asc_ = new AnimSpriteComponent(this, 250);
	//fireball_asc_->SetTexture(k_fireball_tex_, k_fireball_size_, Vec2(0, 0), Vec2(1, 1));

	fireball_asc_->SetAnimTextures(k_fireball_tex_, k_fireball_size_, static_cast<int>(fireball_frame_num::IDLE), 5.f);

	SetPosition(Vec2(-100, 0));

	fireball_stage_num_ = player->Player_getstagenum() + 3;

	if (k_Is_player_ == false)
	{
		k_fireball_distination_ = (Vec2(113 * 3, pos.y_));
		fireball_stage_num_ = player->Player_getstagenum() - 3;
	}

	PlaySound(k_fireball_SE_[static_cast<int>(fireball_SE_num::ADVENT)], 0);

	attackcount_ = 0;
	stg_ = stg;
}

Fireball::~Fireball()
{
}

void Fireball::UpdateActor(float delta_time)
{
	Actor::UpdateActor(delta_time);

	//�A�j���[�V�����ɍ��킹�Ĕ��˂���
	attackcount_ += 5 * delta_time;

	if (attackcount_ >= k_fireball_delay_)
	{
	
		if (fireball_atk_affirmation == false)
		{
			fireball_atk_affirmation = true;
			PlaySound(k_fireball_SE_[static_cast<int>(fireball_SE_num::ATTACK)], 0);
		}

		Fireball::Fireball_parabola(delta_time);
		Fireball::Fireball_exprosion();
	}
	
}

//�������^�������֐�
//�g�����@�p�x�Əd�͉����x�ƒ��e�_��ݒ肷��Ǝ����ŕ������^������������܂�
void Fireball::Fireball_parabola(float delta_time)
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
		//�X�v���C�g��������ɍ��킹�ĉ�]������
		rot = ((double)(0 - (double)k_fireball_deg_) + (((double)k_fireball_deg_ * 2) * (x / k_fireball_distination_.x_))) * M_PI / 180;
	}
	else
	{
		SetPosition(Vec2(k_fireball_pos_init_.x_ - x, y));
		//�X�v���C�g��������ɍ��킹�ĉ�]������
		rot =-1 * ((double)(180 - (double)k_fireball_deg_) + (((double)k_fireball_deg_ * 2) * (x / k_fireball_distination_.x_))) * M_PI / 180;
	}
	fireball_asc_->SetRot(rot);
}

//���e���攚�􂷂鏈��
void Fireball::Fireball_exprosion()
{
	
	if (k_Is_player_)
	{
		if (GetPosition().x_ > k_fireball_pos_init_.x_ + k_fireball_distination_.x_)
		{
			stg_->SetSnow(fireball_stage_num_);

			auto a = new Firepillar(GetGame(),fireball_stage_num_, k_Is_player_, stg_, k_fireball_layer_);
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


//---------------------------------------------------------------
//�Β���
//---------------------------------------------------------------

Firepillar::Firepillar(Game* game, int stage_num, bool is_player, Stage* stg, int layer) : Actor(game)
,k_Is_player_(is_player)
, k_firepillar_stage_num_(stage_num)
, k_firepillar_time_(7)
, k_firepillar_tex_(LoadTexture(L"Data/Image/skill/Eff_FireArea_Sheet.png"))
, k_firepillar_size_(Vec2(140,140))
, deadcount_(0)
,k_firepillar_pos_(Vec2(0, -20))
,k_firepillar_power_(1)
,hitstate_ (false)
{
	firepillar_asc_ = new AnimSpriteComponent(this, layer + 1);
	//fireball_asc_->SetTexture(k_fireball_tex_, k_fireball_size_, Vec2(0, 0), Vec2(1, 1));

	firepillar_asc_->SetAnimTextures(k_firepillar_tex_, k_firepillar_size_, static_cast<int>(firepillar_frame_num::IDLE), 5.f);

	//SetPosition(pos);

	int i = 0;

	if (k_firepillar_stage_num_ >= 0)
		i = 0;
	if (k_firepillar_stage_num_ >= 6)
		i = 1;
	if (k_firepillar_stage_num_ >= 12)
		i = 2;

	Vec2 position = k_firepillar_pos_ + Vec2(SNOW_POS_X + (k_firepillar_stage_num_ % 6) * 113, SNOW_POS_Y + i * 75);
	SetPosition(position);
	SetCollision(Rect(position, k_firepillar_size_));

	stg_ = stg;
}

Firepillar::~Firepillar()
{
	
}

void Firepillar::UpdateActor(float delta_time)
{
	Actor::UpdateActor(delta_time);
	Firepillar::Firepillar_ColligionCheck(delta_time);

	stg_->SetSnow(k_firepillar_stage_num_);

	deadcount_ += 5 * delta_time;
	if (deadcount_ >= k_firepillar_time_)
	{
		SetState(Dead);
	}
}

void Firepillar::Firepillar_ColligionCheck(float delta_taime)
{

	//�A�[�}�[�Ƃ̓����蔻��
	if (GetGame()->GetArmorSize() != 0)
	{
		for (int i = 0; i < GetGame()->GetArmorSize(); i++)
		{
			if (CollisionRC_NoInd(GetGame()->GetArmor(i), this) && !hitstate_)
			{
				if (GetGame()->GetArmor(i)->Get_Isplayer() != k_Is_player_)
				{
					GetGame()->GetArmor(i)->Set_Armorhit(k_firepillar_power_);
					hitstate_ = true;
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
                if (CollisionRC_NoInd(GetGame()->GetEArmor().at(i), this) && k_Is_player_)
                {
                    hitstate_ = true;
                    GetGame()->GetEArmor().at(i)->Set_Armorhit(1);
                }
            }
        }
    }

	//�S�[�����Ƃ̓����蔻��
	if (GetGame()->GetGolemSize() != 0)
	{
		for (int i = 0; i < GetGame()->GetGolemSize(); i++)
		{															//�S�[�����ɂ̓q�b�g�X�e�[�g�Ŕ��肳�����ɂ����n������悤�ɂ��Ă��܂�
			if (CollisionRC_NoInd(GetGame()->GetGolem(i), this))
			{
				if (GetGame()->GetGolem(i)->Get_Isplayer() != k_Is_player_)
				{
					GetGame()->GetGolem(i)->Set_Golemhit(k_firepillar_power_);
					hitstate_ = true;
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
                if (CollisionRC_NoInd(GetGame()->GetEGolems().at(i), this) && k_Is_player_)
                {
                    GetGame()->GetEGolems().at(i)->Set_Golemhit(1);
                    hitstate_ = true;
                }
            }
        }
    }


	if (k_Is_player_)//�v���C���[���̒e
	{
		//�G�Ƀq�b�g�����Ƃ��̏���
        if(GetGame()->GetPlayer2p())
		if (CollisionRC_NoInd(GetGame()->GetPlayer2p(), this) && !hitstate_)
		{
			GetGame()->GetPlayer2p()->Player_SetHit(2);

			GetGame()->GetScoreManager()->AddScore(k_firepillar_power_);

			hitstate_ = true;
		}
        if (GetGame()->GetEnemy())
        {
            if (CollisionRC_NoInd(GetGame()->GetEnemy(), this) && !hitstate_)
            {
                GetGame()->GetScoreManager()->AddScore(k_firepillar_power_);
                //GetGame()->GetEnemy()->Player_SetHit(k_damagetime_);

                hitstate_ = true;
            }
        }
	}
	else
	{
		//�v���C���[1�Ƀq�b�g�����Ƃ��̏���
		if (CollisionRC_NoInd(GetGame()->GetPlayer(), this) && !hitstate_)
		{
			GetGame()->GetPlayer()->Player_SetHit(2);

			GetGame()->GetScoreManager()->EnemyAddScore(k_firepillar_power_);

			hitstate_ = true;
		}

	}
}
