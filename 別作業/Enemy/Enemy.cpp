#include "Enemy.h"
#include "EnemyState.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"
#include "input.h"
#include "TestBullet.h"
#include "Bullet.h"
#include "Texture.h"'
#include "time.h"

Enemy::Enemy(Game* game)
	:Actor(game)
	//constメンバ変数の初期化
	, enemy_snow_max_(16), enemy_snow_min_(0)
	, enemy_pos_var_(D3DXVECTOR2(120, 120)), enemy_pos_center_(D3DXVECTOR2(660, 300))
	, enemy_vel_(D3DXVECTOR2(20, 20))
{
	auto asc = new AnimSpriteComponent(this, 100);
	asc->SetAnimTextures(game->GetTexture(L"Data/Image/running.png"), Vec2(70, 160), 10, 5.f);


	//メンバ変数の初期化
	srand((unsigned int)time(NULL));
	this->enemy_pos_.x = enemy_pos_center_.x;						//画面上の座標
	this->enemy_pos_.y = enemy_pos_center_.y;					    //画面上の座標
	this->enemy_pos_num_ =5;										//いるマスの番号

	this->enemy_snow_ = 0;											//現在持っている雪
	this->enemy_direction_ = rand() % 4;//0,1,2,3,

	this->bullettex_ = LoadTexture(L"Data/Image/13558.png"); //弾のテクスチャ

	penemy_state_context_ = new StateContext<Enemy>(this);
	penemy_state_context_->SetCurrentState(new EnemyIdle(this));

}

void Enemy::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);

	Enemy::enemy_move();
	Enemy::enemy_snow_collect();
	//enemy::enemy_snow_throw();
}

bool Enemy::UpdateTimer(int ms)
{
	return false;
}

//プレイヤーの移動と描画をする処理
void Enemy::enemy_move()  ////敌人自动移动
{
	static int count = 0;
	count++;
	if (count >= 60) 
	{
		count = 0;
		switch (rand() % 4)
		{
		case 0:
			if(enemy_pos_num_ % 3 > 0)
			this->enemy_pos_num_--;

			this->enemy_direction_ = 0;
			break;
		case 1:
			if(enemy_pos_num_ % 3 < 2)
			this->enemy_pos_num_++;
			this->enemy_direction_ = 1;
			break;
		case 2:
			if(enemy_pos_num_ > 2)
			this->enemy_pos_num_ -= 3;
			this->enemy_direction_ = 2;
			break;
		case 3:
			if(enemy_pos_num_ < 6)
			this->enemy_pos_num_ += 3;
			this->enemy_direction_ = 3;
			break;
		}
	}
	//位置を設定して移動
	if (this->enemy_pos_.x < enemy_pos_center_.x + (enemy_pos_num_ % 3 - 1) * enemy_pos_var_.x)
		this->enemy_pos_.x += enemy_vel_.x;

	if (this->enemy_pos_.x > enemy_pos_center_.x + (enemy_pos_num_ % 3 - 1) * enemy_pos_var_.x)
		this->enemy_pos_.x -= enemy_vel_.x;

	if (this->enemy_pos_.y < enemy_pos_center_.y + (floor(enemy_pos_num_ / 3) - 1) * enemy_pos_var_.y)
		this->enemy_pos_.y += enemy_vel_.y;

	if (this->enemy_pos_.y > enemy_pos_center_.y + (floor(enemy_pos_num_ / 3) - 1) * enemy_pos_var_.y)
		this->enemy_pos_.y -= enemy_vel_.y;

	this->SetPosition(Vec2(this->enemy_pos_.x, this->enemy_pos_.y));
}

	
	/*
	瞬間移動する場合
	this->enemy_pos_.x = enemy_pos_center.x + (enemy_pos_num_ % 3 - 1) * enemy_pos_var.x;
	this->enemy_pos_.y = enemy_pos_center.y + (floor(enemy_pos_num_  / 3) - 1)* enemy_pos_var.y;
	*/


//床の雪を拾う処理
void Enemy::enemy_snow_collect()
{

	if (GetKeyboardTrigger(DIK_E))
	{
		int enemy_stage_num = enemy_pos_num_;	//ステージに渡すプレイヤーのマスの番号

		if (enemy_pos_num_ > 2) {
			enemy_stage_num += 3;
			if (enemy_pos_num_ > 5)
				enemy_stage_num += 3;
		}

		//ここに床のステートをしらべる処理が入る

		//手持ちの雪を増やす処理
		if (enemy_snow_ < enemy_snow_max_)
			enemy_snow_++;
	}
}
//
////雪を投げる処理
//void Enemy::enemy_snow_throw()
//{
//
//	if (GetKeyboardTrigger(DIK_SPACE))
//	{
//		if (enemy_snow_ > enemy_snow_min_)
//		{
//			//雪を投げる処理
//			/*auto bullet = new Bullet(GetGame(), bullettex_);
//			bullet->SetPosition(this->GetPosition());*/
//
//			bullets_.push_back(new Bullet(GetGame(), bullettex_));
//			bullets_.back()->SetPosition(this->GetPosition());
//
//			//手持ちの雪を減らす処理
//			enemy_snow_--;
//		}
//	}
//}