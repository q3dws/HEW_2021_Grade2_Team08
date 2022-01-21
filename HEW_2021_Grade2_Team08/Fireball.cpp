#include "Fireball.h"
#include "Armor.h"
#include "Golem.h"
#include "Player.h"
#include "IceWall.h"

#define _USE_MATH_DEFINES
#include <math.h>

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

	attackcount_ = 0;
	stg_ = stg;
}

Fireball::~Fireball()
{
}

void Fireball::UpdateActor(float delta_time)
{
	Actor::UpdateActor(delta_time);

	//アニメーションに合わせて発射する
	attackcount_ += 5 * delta_time;

	if (attackcount_ >= k_fireball_delay_)
	{
		Fireball::Fireball_parabola(delta_time);
		Fireball::Fireball_exprosion();
	}
	
}

//放物線運動を作る関数
//使い方　角度と重力加速度と着弾点を設定すると自動で放物線運動が生成されます
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
		//スプライトを放物線に合わせて回転させる
		rot = ((double)(0 - (double)k_fireball_deg_) + (((double)k_fireball_deg_ * 2) * (x / k_fireball_distination_.x_))) * M_PI / 180;
	}
	else
	{
		SetPosition(Vec2(k_fireball_pos_init_.x_ - x, y));
		//スプライトを放物線に合わせて回転させる
		rot =-1 * ((double)(180 - (double)k_fireball_deg_) + (((double)k_fireball_deg_ * 2) * (x / k_fireball_distination_.x_))) * M_PI / 180;
	}
	fireball_asc_->SetRot(rot);
}

//着弾次第爆裂する処理
void Fireball::Fireball_exprosion()
{
	
	if (k_Is_player_)
	{
		if (GetPosition().x_ > k_fireball_pos_init_.x_ + k_fireball_distination_.x_)
		{
			stg_->SetSnow(fireball_stage_num_);

			auto a = new Firepillar(GetGame(),fireball_stage_num_, k_Is_player_, stg_, k_fireball_layer_);

			SetState(Dead);
		}
	}
	else
	{
		if (GetPosition().x_ < k_fireball_pos_init_.x_ - k_fireball_distination_.x_)
		{
			stg_->SetSnow(fireball_stage_num_);

			auto a = new Firepillar(GetGame(), fireball_stage_num_, k_Is_player_, stg_, k_fireball_layer_);

			SetState(Dead);
		}
	}
}


//---------------------------------------------------------------
//火柱側
//---------------------------------------------------------------

Firepillar::Firepillar(Game* game, int stage_num, bool is_player, Stage* stg, int layer) : Actor(game)
,k_Is_player_(is_player)
, k_firepillar_stage_num_(stage_num)
, k_firepillar_time_(20)
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

	//アーマーとの当たり判定
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

	//ゴーレムとの当たり判定
	if (GetGame()->GetGolemSize() != 0)
	{
		for (int i = 0; i < GetGame()->GetGolemSize(); i++)
		{															//ゴーレムにはヒットステートで判定させずにすぐ溶かせるようにしています
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


	if (k_Is_player_)//プレイヤー側の弾
	{
		//敵にヒットしたときの処理
		if (CollisionRC_NoInd(GetGame()->GetPlayer2p(), this) && !hitstate_)
		{
			GetGame()->GetPlayer2p()->Player_SetHit(2);

			GetGame()->GetScoreManager()->AddScore(k_firepillar_power_);

			hitstate_ = true;
		}
	}
	else
	{
		//プレイヤー1にヒットしたときの処理
		if (CollisionRC_NoInd(GetGame()->GetPlayer(), this) && !hitstate_)
		{
			GetGame()->GetPlayer()->Player_SetHit(2);

			GetGame()->GetScoreManager()->EnemyAddScore(k_firepillar_power_);

			hitstate_ = true;
		}

	}
}
