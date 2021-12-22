#include "Player.h"
#include "PlayerState.h"

#include "input.h"
#include "TestBullet.h"
#include "Bullet.h"

#include "Golem.h"
#include "BigBullet.h"
#include "IceWall.h"
#include <memory>

Player::Player(Game* game, Stage* stg, Vec2 size, Vec2 center, bool Is_player)
	:Actor(game)
	, stg_(stg)
	//constメンバ変数の初期化
	, k_player_snow_max_(18), k_player_snow_min_(0)
	, k_player_pos_var_(Vec2(104, 86.5))
	, k_player_vel_(Vec2(180, 180))
	, k_player_layer_var(5)
	, k_Is_player_(Is_player)
	
{
    
	//メンバ変数の初期化
	k_player_pos_center_ = (Vec2(center));
	k_player_size_ = (Vec2(size));
	if (k_Is_player_ == false)
	{
		k_player_size_ = (Vec2(size * -1));
		k_player_pos_center_ = (Vec2(center.x_ + 310, center.y_));
	}

	this->player_pos_.x_ = k_player_pos_center_.x_;						//プレイヤーの画面上の座標
	this->player_pos_.y_ = k_player_pos_center_.y_;					//プレイヤーの画面上の座標
    this->player_pos_num_ = 4;										//プレイヤーのいるマスの番号
    this->player_snow_ = 0;											//プレイヤーの現在持っている雪
	this->idlecount_ = 0;
	this->player_layer_ = 100;
	this->player_mode_ = static_cast<int>(PlayerMotion::IDLE);
	this->idle_timeto_ = 0;

	this->bullettex_ = LoadTexture(L"Data/Image/snowball.png"); //弾のテクスチャ

	pplayer_state_context_ = new StateContext<Player>(this);
	pplayer_state_context_->SetCurrentState(new PlayerIdle(this));

	this->SetPosition(player_pos_);

	this->asc_ = new AnimSpriteComponent(this, player_layer_);
	
	snowcost_ = new SnowCost(game, k_Is_player_);
}

Player:: ~Player()
{
	this->RemoveComponent(asc_);
	this->GetGame()->RemoveSprite(asc_);
}
void Player::UpdateActor(float deltatime)
{
    Actor::UpdateActor(deltatime);
    
	Player::Player_move(deltatime);
	Player::Player_snow_collect();
	Player::Player_snow_throw(deltatime);
	Player::Player_idlecheck(deltatime);
	Player::Player_useskill();

	snowcost_->SetSnownum(player_snow_);
}

//プレイヤーの移動をする処理
void Player::Player_move(float deltatime)
{
	//ボタンを押すとプレイヤーのいるマスの番号を変更させる
	if (player_mode_ == static_cast<int>(PlayerMotion::IDLE)
		|| player_mode_ == static_cast<int>(PlayerMotion::MOVE_FRONT)
		|| player_mode_ == static_cast<int>(PlayerMotion::MOVE_BACK)
		|| player_mode_ == static_cast<int>(PlayerMotion::MOVE_UPANDDOWN)
		)
	{

		if ((GetKeyboardTrigger(DIK_A) && k_Is_player_)
			|| (GetKeyboardTrigger(DIK_LEFT) && !k_Is_player_))
		{
			if (player_pos_num_ % 3 > 0)
				this->player_pos_num_--;
		}
		if ((GetKeyboardTrigger(DIK_D) && k_Is_player_)
			|| (GetKeyboardTrigger(DIK_RIGHT) && !k_Is_player_))
		{
			if (player_pos_num_ % 3 < 2)
				this->player_pos_num_++;
		}
		if ((GetKeyboardTrigger(DIK_W) && k_Is_player_)
			|| (GetKeyboardTrigger(DIK_UP) && !k_Is_player_))
		{
			if (player_pos_num_ > 2)
				this->player_pos_num_ -= 3;

		}
		if ((GetKeyboardTrigger(DIK_S) && k_Is_player_)
			|| (GetKeyboardTrigger(DIK_DOWN) && !k_Is_player_))
		{
			if (player_pos_num_ < 6)
				this->player_pos_num_ += 3;
		}


		//描画の優先度変更
		player_layer_ = 100 + k_player_layer_var * (player_pos_num_ / 3);
	}


	//自分のマスに位置を設定して移動
	/*
	瞬間移動する場合
	this->player_pos_.x_ = player_pos_center.x_ + (player_pos_num_ % 3 - 1) * player_pos_var.x_;
	this->player_pos_.y_ = player_pos_center.y_ + (floor(player_pos_num_  / 3) - 1)* player_pos_var.y_;
	*/

	float x_distination = k_player_pos_center_.x_ + (player_pos_num_ % 3 - 1) * k_player_pos_var_.x_;
	float y_distination = k_player_pos_center_.y_ + (floor(player_pos_num_ / 3) - 1) * k_player_pos_var_.y_;

	if (this->player_pos_.x_ < x_distination)
	{
		this->player_pos_.x_ += k_player_vel_.x_ * deltatime;

		Player_texchange(static_cast<int>(PlayerMotion::MOVE_FRONT));

		if (this->player_pos_.x_ >= x_distination)
		{
			this->player_pos_.x_ = x_distination;
			Player_texchange(static_cast<int>(PlayerMotion::IDLE));
		}

	}
	if (this->player_pos_.x_ > x_distination)
	{
		this->player_pos_.x_ -= k_player_vel_.x_ * deltatime;
		Player_texchange(static_cast<int>(PlayerMotion::MOVE_BACK));

		if (this->player_pos_.x_ <= x_distination)
		{
			this->player_pos_.x_ = x_distination;
			Player_texchange(static_cast<int>(PlayerMotion::IDLE));

		}

	}

	if (this->player_pos_.y_ < y_distination)
	{
		this->player_pos_.y_ += k_player_vel_.y_ * deltatime;
		Player_texchange(static_cast<int>(PlayerMotion::MOVE_UPANDDOWN));

		if (this->player_pos_.y_ >= y_distination)
		{
			this->player_pos_.y_ = y_distination;
			Player_texchange(static_cast<int>(PlayerMotion::IDLE));
		}
	}

	if (this->player_pos_.y_ > y_distination)
	{
		this->player_pos_.y_ -= k_player_vel_.y_ * deltatime;
		Player_texchange(static_cast<int>(PlayerMotion::MOVE_UPANDDOWN));

		if (this->player_pos_.y_ <= y_distination)
		{
			this->player_pos_.y_ = y_distination;
			Player_texchange(static_cast<int>(PlayerMotion::IDLE));
		}
	}

	//位置を設定する
	this->SetPosition(player_pos_);

}

//床の雪を拾う処理
void Player::Player_snow_collect()
{
	if (player_mode_ == static_cast<int>(PlayerMotion::IDLE)
		&& player_snow_ < k_player_snow_max_)
	{
		if ((GetKeyboardTrigger(DIK_E) && k_Is_player_) ||
			(GetKeyboardTrigger(DIK_RSHIFT) && k_Is_player_ == false))
		{
			int player_stage_num = Player_getstagenum();

			//床のステートをしらべる
			if (stg_->GetUseSnow(player_stage_num))
			{
				stg_->SetSnow(player_stage_num);

				//手持ちの雪を増やす処理
				if (player_snow_ < k_player_snow_max_)
				{
					player_snow_ += 2;
					if (player_snow_ > k_player_snow_max_)
						player_snow_ = k_player_snow_max_;

				}
				Player_texchange(static_cast<int>(PlayerMotion::COLLECT_IN));
			}
		}
		
		
	}	
}

//雪を投げる処理
void Player::Player_snow_throw(float deltatime)
{
	if (player_mode_ == static_cast<int>(PlayerMotion::IDLE)
		|| player_mode_ == static_cast<int>(PlayerMotion::ATTACK))
	{
		if ((GetKeyboardTrigger(DIK_SPACE) && k_Is_player_)
			|| (GetKeyboardTrigger(DIK_RCONTROL) && !k_Is_player_))
		{
			if (player_snow_ > k_player_snow_min_)
			{
				//弾を生成
				bullets_.emplace_back(new Bullet(GetGame(), bullettex_, k_Is_player_));
				bullets_.back()->SetPosition(this->GetPosition());

				Player_texchange(static_cast<int>(PlayerMotion::ATTACK));

				//手持ちの雪を減らす処理
				player_snow_--;
			}
		}



	}
}

//一定時間後に待機状態に戻す処理
void Player::Player_idlecheck(float deltatime)
{
	if (idle_timeto_ > 0)
	{
		idlecount_ += 5 * deltatime;
		if (idlecount_ >= idle_timeto_)
		{
			if (player_mode_ == static_cast<int>(PlayerMotion::COLLECT_IN))
			{
				Player_texchange(static_cast<int>(PlayerMotion::COLLECT_LOOP));
				idlecount_ = 0;
			}
			else if (player_mode_ == static_cast<int>(PlayerMotion::COLLECT_LOOP))
			{
				Player_texchange(static_cast<int>(PlayerMotion::COLLECT_OUT));
				idlecount_ = 0;
			}
			else
			{
				Player_texchange(static_cast<int>(PlayerMotion::IDLE));
				idlecount_ = 0;
				idle_timeto_ = 0;
			}
			
		}
	
	}
	
}

//スキルを使う処理
void Player::Player_useskill(void)
{
	if (player_mode_ == static_cast<int>(PlayerMotion::IDLE))
	{

		if ((GetKeyboardTrigger(DIK_1) && k_Is_player_)
			|| (GetKeyboardTrigger(DIK_RBRACKET) && !k_Is_player_))
		{
			if (player_snow_ >= k_player_skillcost_[0])
			{
				Player_texchange(static_cast<int>(PlayerMotion::USE_SKILL));
				//ゴーレムを生成
				golems_.emplace_back(new Golem(GetGame(), player_pos_, bullettex_, player_layer_, k_Is_player_));
				golems_.back()->SetPosition(this->GetPosition());

				player_snow_ -= k_player_skillcost_[0];
			}
		}

		if ((GetKeyboardTrigger(DIK_2) && k_Is_player_)
			|| (GetKeyboardTrigger(DIK_COLON) && !k_Is_player_))
		{
			if (player_snow_ >= k_player_skillcost_[1])
			{
				Player_texchange(static_cast<int>(PlayerMotion::USE_SKILL));
				//壁を生成
				auto a = new IceWall(GetGame(), player_pos_, player_layer_, k_Is_player_);
				player_snow_ -= k_player_skillcost_[1];
			}
			
		}

		if ((GetKeyboardTrigger(DIK_3) && k_Is_player_)
			|| (GetKeyboardTrigger(DIK_SEMICOLON) && !k_Is_player_))
		{
			if (player_snow_ >= k_player_skillcost_[2])
			{
				Player_texchange(static_cast<int>(PlayerMotion::USE_SKILL));
				//大玉を生成
				auto a = new BigBullet(GetGame(), k_Is_player_, player_layer_);
				a->SetPosition(this->GetPosition());

				player_snow_ -= k_player_skillcost_[2];
			}
		}

		if ((GetKeyboardTrigger(DIK_4) && k_Is_player_)
			|| (GetKeyboardTrigger(DIK_L) && !k_Is_player_))
		{
			//固有スキル発動
			Player_UniqueSkill();
		}


	}
}

//プレイヤーの現在のマス目番号からステージに渡せるマス目番号に変換する関数
int Player::Player_getstagenum(void)
{
	int player_stage_num = player_pos_num_;
			// 0  1  2  3  4  5
			// 6  7  8  9 10 11
			//12 13 14 15 16 17
			//boolのfalsetrueで返される

	if (player_pos_num_ > 2 && player_pos_num_ < 6) {
		player_stage_num += 3;
	}
	if (player_pos_num_ >= 6)
		player_stage_num += 6;

	if (k_Is_player_)
	{
		return player_stage_num;
	}
	return player_stage_num + 3;
}

//持っている雪の数を返すゲッター
int Player::Player_getsnow(void)
{
	return player_snow_;
}

