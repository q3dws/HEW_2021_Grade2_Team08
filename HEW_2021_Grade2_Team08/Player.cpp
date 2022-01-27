#include "Player.h"
#include "PlayerState.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"
#include "input.h"
#include "TestBullet.h"
#include "Bullet.h"

#include <memory>

Player::Player(Game* game, Stage* stg)
    :Actor(game)
	,stg_(stg)
	//constメンバ変数の初期化
	, k_player_snow_max_(16), k_player_snow_min_(0)
	,k_player_pos_var_(D3DXVECTOR2(104, 86.5)), k_player_pos_center_(D3DXVECTOR2(325, 246 + 33))
	, k_player_vel_(D3DXVECTOR2(360,360))
	,k_player_size_(Vec2(64 * 2.5, 64 * 2.5))
	, k_charaA_{LoadTexture(L"Data/Image/chara_A_taiki_Sheet.png"), LoadTexture(L"Data/Image/chara_A_attack_Sheet.png") }
{
	this->texbuffer_ = 0;
    asc_[texbuffer_] = new AnimSpriteComponent(this, 100);
    asc_[texbuffer_]->SetAnimTextures(k_charaA_[static_cast<int>(PlayerMotion::IDLE)], k_player_size_, 8, 5.f);

	//メンバ変数の初期化
	this->player_pos_.x = k_player_pos_center_.x;						//プレイヤーの画面上の座標
	this->player_pos_.y = k_player_pos_center_.y;					//プレイヤーの画面上の座標
    this->player_pos_num_ = 4;										//プレイヤーのいるマスの番号
    this->player_snow_ = 0;											//プレイヤーの現在持っている雪
	this->idlecount_ = 0;

	this->bullettex_ = LoadTexture(L"Data/Image/13558.png"); //弾のテクスチャ

	pplayer_state_context_ = new StateContext<Player>(this);
	pplayer_state_context_->SetCurrentState(new PlayerIdle(this));

	this->SetPosition(Vec2(this->player_pos_.x, this->player_pos_.y));
}

void Player::UpdateActor(float deltatime)
{
    Actor::UpdateActor(deltatime);
    
	Player::Player_move(deltatime);
	Player::Player_snow_collect();
	Player::Player_snow_throw(deltatime);
	Player::Player_idlecheck(deltatime);
}

//プレイヤーの移動と描画をする処理
void Player::Player_move(float deltatime)
{
	//ボタンを押すとプレイヤーのいるマスの番号を変更させる
	if (GetKeyboardTrigger(DIK_LEFT))
	{
		if(player_pos_num_ % 3 > 0)
		this->player_pos_num_--;
	}
	if (GetKeyboardTrigger(DIK_RIGHT))
	{
		if (player_pos_num_ % 3 < 2)
			this->player_pos_num_++;
	}
	if (GetKeyboardTrigger(DIK_UP))
	{
		if (player_pos_num_  > 2)
			this->player_pos_num_ -= 3;

	}
	if (GetKeyboardTrigger(DIK_DOWN))
	{
		if (player_pos_num_  < 6)
			this->player_pos_num_ += 3 ;

	}

	//自分のマスに位置を設定して移動
	/*
	瞬間移動する場合
	this->player_pos_.x = player_pos_center.x + (player_pos_num_ % 3 - 1) * player_pos_var.x;
	this->player_pos_.y = player_pos_center.y + (floor(player_pos_num_  / 3) - 1)* player_pos_var.y;
	*/

	float x_distination = k_player_pos_center_.x + (player_pos_num_ % 3 - 1) * k_player_pos_var_.x;
	float y_distination = k_player_pos_center_.y + (floor(player_pos_num_ / 3) - 1) * k_player_pos_var_.y;

	if (this->player_pos_.x < x_distination)
	{
		this->player_pos_.x += k_player_vel_.x * deltatime;

		if (this->player_pos_.x > x_distination)
			this->player_pos_.x = x_distination;
	}
	if (this->player_pos_.x > x_distination)
	{
		this->player_pos_.x -= k_player_vel_.x * deltatime;

		if (this->player_pos_.x < x_distination)
			this->player_pos_.x = x_distination;
	}
		
	if (this->player_pos_.y < y_distination)
	{
		this->player_pos_.y += k_player_vel_.y * deltatime;

		if (this->player_pos_.y > y_distination)
			this->player_pos_.y = y_distination;
	}
		
	if (this->player_pos_.y > y_distination)
	{
		this->player_pos_.y -= k_player_vel_.y * deltatime;

		if (this->player_pos_.y < y_distination)
			this->player_pos_.y = y_distination;
	}

	//描画する
	this->SetPosition(Vec2(this->player_pos_.x, this->player_pos_.y));

}

//床の雪を拾う処理
void Player::Player_snow_collect()
{
	
	if (GetKeyboardTrigger(DIK_E))
	{
		int player_stage_num = player_pos_num_;	//ステージに渡すプレイヤーのマスの番号

		// 0  1  2  3  4  5
		// 6  7  8  9 10 11
		//12 13 14 15 16 17
		//boolのfalsetrueで返される

		if (player_pos_num_ > 2 && player_pos_num_ < 6) {
			player_stage_num += 3;
		}
		if(player_pos_num_ >= 6)
			player_stage_num += 6;

		//ここに床のステートをしらべる処理が入る
		stg_->SetSnow(player_stage_num);

		//手持ちの雪を増やす処理
		if(player_snow_ < k_player_snow_max_)
		player_snow_++;
	}
}

//雪を投げる処理
void Player::Player_snow_throw(float deltatime)
{

	if (GetKeyboardTrigger(DIK_SPACE))
	{	
		if (player_snow_ > k_player_snow_min_)
		{
			//弾を生成
			bullets_.emplace_back(new Bullet(GetGame(), bullettex_));
			bullets_.back()->SetPosition(this->GetPosition());

			//弾が消えるときの判定処理
			if (bullets_.empty() == false)
			{
				for (int i = 0; i < bullets_.size(); i++)
					if (bullets_[i]->GetPosition().x_ > WINDOW_WIDTH)
					{
						//delete bullets_[i];
						bullets_.erase(bullets_.begin() + i);
						bullets_.shrink_to_fit();
					}
			}
			/*auto itr = bullets_.begin(); //イテレータを使う場合
			if (bullets_.empty() == false)
			{
				for (; itr != bullets_.end(); ++itr)
					if ((*itr)->GetPosition().x_ > WINDOW_WIDTH)
					{
						bullets_.erase(itr);
					}
			}*/
			
			Player_texchange(static_cast<int>(PlayerMotion::ATTACK));
			idlecount_ = 0.001;

			//手持ちの雪を減らす処理
			player_snow_--;
		}
	}
}

void Player::Player_idlecheck(float deltatime)
{
	if (idlecount_ > 0)
	{
		idlecount_ += 5 * deltatime;
		if (idlecount_ > 8)
		{
			Player_texchange(static_cast<int>(PlayerMotion::IDLE));
			idlecount_ = 0;
		}
	
	}
	
}

//プレイヤーのテクスチャを変える処理
void Player::Player_texchange(int texnum)
{
	switch (texbuffer_)
	{
	case 0:
		//delete asc_;
		asc_[texbuffer_ + 1] = new AnimSpriteComponent(this, 100);
		asc_[texbuffer_ + 1]->SetAnimTextures(k_charaA_[texnum], k_player_size_, 8, 5.f);

		this->RemoveComponent(asc_[texbuffer_]);
		this->GetGame()->RemoveSprite(asc_[texbuffer_]);
		
		texbuffer_ = 1;
		break;
	case 1:
		asc_[texbuffer_ - 1] = new AnimSpriteComponent(this, 100);
		asc_[texbuffer_ - 1]->SetAnimTextures(k_charaA_[texnum], k_player_size_, 8, 5.f);

		this->RemoveComponent(asc_[texbuffer_]);
		this->GetGame()->RemoveSprite(asc_[texbuffer_]);
		
		texbuffer_ = 0;
		break;
	default:
		break;
	}
	
	//this->RemoveComponent(asc_);
	//this->GetGame()->RemoveSprite(asc_);
	////delete asc_;
	//asc_ = new AnimSpriteComponent(this, 100);
	//asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, 8, 5.f);
	
}