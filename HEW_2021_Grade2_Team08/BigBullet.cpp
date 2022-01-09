#include "BigBullet.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Player.h"

BigBullet::BigBullet(Game* game, bool Is_player, int layer, Vec2 pos) : Skill(game)
, k_bigsnow_vel_(10)
, k_bigsnow_tex_(LoadTexture(L"Data/Image/skill/snowball_big.png"))
, k_bigsnow_Grow(Vec2(40,40))
,k_bigsnow_Growrot_(180)
,k_Is_player_(Is_player)
,k_bigsnow_layer_(layer + 1)
, bigsnow_pos_(pos)
{
	bigsnow_size_ = Vec2(20, 20);

	bigsnow_asc_ = new SpriteComponent(this, k_bigsnow_layer_);
	bigsnow_asc_->SetTexture(k_bigsnow_tex_, bigsnow_size_, Vec2(0, 0), Vec2(1, 1));

	SetPosition(bigsnow_pos_);

	SetCollision(Rect(bigsnow_pos_, bigsnow_size_));
	bigsnow_rot_ = 0;
	bigsnow_power_ = 1;
	bigsnow_distance_count_ = 0;
}

BigBullet::~BigBullet()
{
}

void BigBullet::UpdateActor(float delta_time)
{
	Actor::UpdateActor(delta_time);
	BigBullet::BigBullet_move(delta_time);

	//移動距離に応じて威力アップ
	bigsnow_distance_count_ += k_bigsnow_Growrot_ * delta_time;
	if (bigsnow_distance_count_ >= 100)
	{
		bigsnow_power_++;
		bigsnow_distance_count_ = 0;
	}

	if (k_Is_player_)//プレイヤー側の弾
	{
		//敵にヒットしたときの処理
		if (CollisionRC_NoInd(GetGame()->GetPlayer2p(), this))
		{
			GetGame()->GetPlayer2p()->Player_SetHit();

			GetGame()->GetScoreManager()->AddScore(bigsnow_power_);

			SetState(Dead);
		}
	}
	else
	{
		//プレイヤー1にヒットしたときの処理
		if (CollisionRC_NoInd(GetGame()->GetPlayer() , this))
		{
			GetGame()->GetPlayer()->Player_SetHit();

			GetGame()->GetScoreManager()->EnemyAddScore(bigsnow_power_);

			SetState(Dead);
		}

	}

	if (GetPosition().x_ > WINDOW_WIDTH + bigsnow_size_.x_)
		SetState(Dead);

	if (GetPosition().x_ < 0 - bigsnow_size_.x_)
		SetState(Dead);

}

void BigBullet::BigBullet_move(float delta_time)
{
	bigsnow_size_ += k_bigsnow_Grow * delta_time;

	bigsnow_asc_->SetSize(bigsnow_size_);
	
	if (k_Is_player_)
	{
		SetPosition(Vec2(GetPosition().x_ + k_bigsnow_vel_, GetPosition().y_));
		bigsnow_rot_ += k_bigsnow_Growrot_ * delta_time;

		//当たり判定移動
		MoveCollison(Vec2(k_bigsnow_vel_, 0));
	}
	else
	{
		SetPosition(Vec2(GetPosition().x_ - k_bigsnow_vel_, GetPosition().y_));
		bigsnow_rot_ -= k_bigsnow_Growrot_ * delta_time;
		
		//当たり判定移動
		MoveCollison(Vec2(-k_bigsnow_vel_, 0));
	}
	bigsnow_asc_->SetRot(bigsnow_rot_ * M_PI / 180);

	
}
