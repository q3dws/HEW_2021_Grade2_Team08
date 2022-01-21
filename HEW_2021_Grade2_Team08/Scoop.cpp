#include "Scoop.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Player.h"
#include "Golem.h"
#include "Armor.h"
#include "Game.h"

Scoop::Scoop(Game* game, int layer, Vec2 pos, bool Is_player, Stage* stg, Player* player) : Skill(game)
, k_scoop_tex_(LoadTexture(L"Data/Image/skill/snowball_big.png"))
, k_scoop_size_(Vec2(30, 30))
,k_scoop_layer_(layer)
, k_scoop_g_(9.8)
,k_scoop_pos_init_(Vec2(pos.x_, pos.y_ + 50))
, k_scoop_deg_(60)
, k_scoop_distination_(Vec2(113 * 3 + (k_scoop_size_.x_ / 2), pos.y_))
,k_Is_player_(Is_player)
, stg_(stg)
{
	scoop_pos_ = pos;
	scoop_asc_ = new SpriteComponent(this, 250);
	scoop_asc_->SetTexture(k_scoop_tex_, k_scoop_size_, Vec2(0, 0), Vec2(1, 1));
	
	scoop_stage_num_ = player->Player_getstagenum() + 3;

	if (k_Is_player_ == false)
	{
		k_scoop_distination_ = (Vec2(113 * 3 , pos.y_));
		scoop_stage_num_ = player->Player_getstagenum() - 3;
	}

	SetPosition(k_scoop_pos_init_);
	
}

Scoop::~Scoop()
{
}

void Scoop::UpdateActor(float delta_time)
{
	Actor::UpdateActor(delta_time);
	Scoop::Scoop_parabola(delta_time);
	Scoop::Scoop_exprosion();
}

//放物線運動を作る関数
void Scoop::Scoop_parabola(float delta_time)
{
	//使い方　角度と重力加速度と着弾点を設定すると自動で放物線運動が生成されます

	float rad = k_scoop_deg_ * M_PI / 180;
	float g = k_scoop_g_ / delta_time;

	float v = sqrt(g * k_scoop_distination_.x_ / (2 * sinf(rad) * cosf(rad)));
	float t = k_scoop_distination_.x_ / (v * cosf(rad));

	scoop_pos_.x_ += (k_scoop_distination_.x_ / t) * delta_time;

	float x = scoop_pos_.x_ - k_scoop_pos_init_.x_;

	float y = scoop_pos_.y_ + 50 + -1 *
		(x * tan(rad) - (g / ((2 * v * v) * cos(rad) * cos(rad)) * x * x));

	if (k_Is_player_ )
	{		
		SetPosition(Vec2(scoop_pos_.x_, y));
	}
	else
	{
		SetPosition(Vec2(k_scoop_pos_init_.x_ - x, y));
	}
}

//着弾次第爆裂する処理
void Scoop::Scoop_exprosion()
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

//マス目に合わせて氷柱召喚
void Scoop::Scoop_summon_icepiller()
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

	auto a = new Icepillar(GetGame(), scoop_stage_num_,  k_Is_player_, stg_, k_scoop_layer_);
	auto b = new Icepillar(GetGame(), scoop_stage_num_ + i
		, k_Is_player_, stg_, k_scoop_layer_ + i);

	auto c = new Icepillar(GetGame(), scoop_stage_num_ + j
		, k_Is_player_, stg_, k_scoop_layer_ + j);
}



//
//出てくる小さな玉側
//

MiniBullet::MiniBullet(Game* game, int tex, Vec2 pos,bool up, bool is_player)
	:Actor(game)
	, snow_vel_(10)
	,k_Is_player_(is_player)
	, k_damagetime_(2)
{
	auto sc = new SpriteComponent(this, 150);
	sc->SetTexture(tex, Vec2(30, 30), Vec2(0, 0), Vec2(1, 1));
	up_ = up;

	SetPosition(pos);
	SetCollision(Rect(pos, Vec2(30, 30)));
}

MiniBullet::~MiniBullet()
{

}

void MiniBullet::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);

	if (up_)
	{
		SetPosition(Vec2(GetPosition().x_, GetPosition().y_ + snow_vel_));
		MoveCollison(Vec2(0, snow_vel_));
	}
	else
	{
		SetPosition(Vec2(GetPosition().x_, GetPosition().y_ - snow_vel_));
		MoveCollison(Vec2(0, -snow_vel_));
	}

    //アーマーとの当たり判定
    if (GetGame()->GetArmorSize() != 0)
    {
        for (int i = 0; i < GetGame()->GetArmorSize(); i++)
        {
            if (CollisionRC_NoInd(GetGame()->GetArmor(i), this) && this->GetState() == 0)
            {
                if (GetGame()->GetArmor(i)->Get_Isplayer() != k_Is_player_)
                {
                    GetGame()->GetArmor(i)->Set_Armorhit(1);
                    SetState(Dead);
                }
            }
        }
    }


    //ゴーレムとの当たり判定
    if (GetGame()->GetGolemSize() != 0)
    {
        for (int i = 0; i < GetGame()->GetGolemSize(); i++)
        {
            if (CollisionRC_NoInd(GetGame()->GetGolem(i), this) && this->GetState() == 0)
            {
                if (GetGame()->GetGolem(i)->Get_Isplayer() != k_Is_player_)
                {
                    GetGame()->GetGolem(i)->Set_Golemhit(1);
                    SetState(Dead);
                }
            }
        }
    }

    if (k_Is_player_)//プレイヤー側の弾
    {
       
        //敵にヒットしたときの処理
        if (CollisionRC_NoInd(GetGame()->GetPlayer2p(), this) && this->GetState() == 0)
        {
            GetGame()->GetPlayer2p()->Player_SetHit(k_damagetime_);

            GetGame()->GetScoreManager()->AddScore(1);

            SetState(Dead);
        }

    }
    else
    {
       
        //プレイヤー1にヒットしたときの処理
        if (CollisionRC_NoInd(GetGame()->GetPlayer(), this) && this->GetState() == 0)
        {
            GetGame()->GetPlayer()->Player_SetHit(k_damagetime_);

            GetGame()->GetScoreManager()->EnemyAddScore(1);

            SetState(Dead);

        }
    }


	if (GetPosition().y_ > WINDOW_HEIGHT || GetPosition().y_ < 0)
		SetState(Dead);
}


//---------------------------------------------------------------
//氷柱側
//---------------------------------------------------------------

Icepillar::Icepillar(Game* game, int stage_num, bool is_player, Stage* stg, int layer) : Actor(game)
, k_Is_player_(is_player)
, k_icepillar_stage_num_(stage_num)
, k_icepillar_time_(20)
, k_icepillar_tex_(LoadTexture(L"Data/Image/skill/Eff_IceArea_Sheet.png"))
, k_icepillar_size_(Vec2(140, 140))
, deadcount_(0)
, k_icepillar_pos_(Vec2(0, -20))
, hitstate_(false)
, k_icepillar_power_(1)
{
	icepillar_asc_ = new AnimSpriteComponent(this, layer + 4);
	//iceball_asc_->SetTexture(k_iceball_tex_, k_iceball_size_, Vec2(0, 0), Vec2(1, 1));

	icepillar_asc_->SetAnimTextures(k_icepillar_tex_, k_icepillar_size_, static_cast<int>(icepillar_frame_num::IDLE), 5.f);

	//SetPosition(pos);

	int i = 0;

	if (k_icepillar_stage_num_ >= 0)
		i = 0;
	if (k_icepillar_stage_num_ >= 6)
		i = 1;
	if (k_icepillar_stage_num_ >= 12)
		i = 2;

	Vec2 position = k_icepillar_pos_ + Vec2(SNOW_POS_X + (k_icepillar_stage_num_ % 6) * 113, SNOW_POS_Y + i * 75);

	SetPosition(position);
	SetCollision(Rect(position, k_icepillar_size_));

	stg_ = stg;
}

Icepillar::~Icepillar()
{

}

void Icepillar::UpdateActor(float delta_time)
{
	Actor::UpdateActor(delta_time);
	Icepillar_ColligionCheck(delta_time);
	//stg_->SetSnow(k_icepillar_stage_num_);

	deadcount_ += 5 * delta_time;
	if (deadcount_ >= static_cast<int>(icepillar_frame_num::IDLE) * 2 / 3)
	{
		//消え始めたら当たり判定消す
		hitstate_ = true;
	}

	if (deadcount_ >= static_cast<int>(icepillar_frame_num::IDLE))
	{
		SetState(Dead);
	}
}

void Icepillar::Icepillar_ColligionCheck(float delta_taime)
{
	
	//アーマーとの当たり判定
	if (GetGame()->GetArmorSize() != 0)
	{
		for (int i = 0; i < GetGame()->GetArmorSize(); i++)
		{
			if (CollisionRC_NoInd(GetGame()->GetArmor(i), this) && ! hitstate_)
			{
				if (GetGame()->GetArmor(i)->Get_Isplayer() != k_Is_player_)
				{
					GetGame()->GetArmor(i)->Set_Armorhit(k_icepillar_power_);
					hitstate_ = true;
				}
			}
		}
	}

	//ゴーレムとの当たり判定
	if (GetGame()->GetGolemSize() != 0)
	{
		for (int i = 0; i < GetGame()->GetGolemSize(); i++)
		{
			if (CollisionRC_NoInd(GetGame()->GetGolem(i), this) && !hitstate_)
			{
				if (GetGame()->GetGolem(i)->Get_Isplayer() != k_Is_player_)
				{
					GetGame()->GetGolem(i)->Set_Golemhit(k_icepillar_power_);
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

			GetGame()->GetScoreManager()->AddScore(k_icepillar_power_);

			hitstate_ = true;
		}
	}
	else
	{
		//プレイヤー1にヒットしたときの処理
		if (CollisionRC_NoInd(GetGame()->GetPlayer(), this) && !hitstate_)
		{
			GetGame()->GetPlayer()->Player_SetHit(2);

			GetGame()->GetScoreManager()->EnemyAddScore(k_icepillar_power_);

			hitstate_ = true;
		}

	}
}
