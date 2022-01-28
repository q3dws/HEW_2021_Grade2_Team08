#include "Enemy.h"
#include "EnemyState.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"
#include "input.h"
#include "TestBullet.h"
#include "Bullet.h"
#include "Texture.h"'
#include "time.h"
#include "Stage.h"
#include "DEBUG_Comand.h"
#include "Player.h"
#include "EGolem.h"
#include "EIceWall.h"
#include "EBigBullet.h"
#include "sound.h"

#if 1
Enemy::Enemy(Game* game, Stage* stage) :
	POSSESSION_MAX_   (18                                                                        ),
	UPDATE_FRAME_     (5                                                                         ),
    ADJUST_VALUE_Y_   (37                                                                        ),
	MOV_DISTANCE_     (Vec2(113, 75)                                                             ),
	POS_CENTER_       (Vec2(SNOW_POS_X + MOV_DISTANCE_.x_ * 4, SNOW_POS_Y + MOV_DISTANCE_.y_ * 1)),
	VELOCITY_         (Vec2(MOV_DISTANCE_.x_ * 0.1f, MOV_DISTANCE_.y_ * 0.1f)                    ),

	Actor             (game                                                                      ),
	stage_            (stage                                                                     ),

	snow_num_         (                                                                          ),
	in_action_        (                                                                          ),
    in_animation_     (                                                                          ),
	current_frame_    (                                                                          ),

	direction_        (-1                                                                        ),
	destination_      (                                                                          ),
	position_info_    (PositionInfo()                                                            ),

	current_animation_(                                                                          ),
	textures_         (                                                                          ),
    texsize_          (Vec2(-64 * 2.5, -64 * 2.5)                                                ),
	layer_            (200                                                                       ),
	bullettex_        (LoadTexture(L"Data/Image/snowball.png")                                   ),
    sounds_{
        LoadSound(L"Data/SE/Player/plaer_shrow.wav"),
        LoadSound(L"Data/SE/Player/player_move.wav"),
        LoadSound(L"Data/SE/Player/player_collect.wav"),
        LoadSound(L"Data/SE/Player/player_skill.wav"),
        LoadSound(L"Data/SE/Player/player_hit.wav"),
        LoadSound(L"Data/SE/Player/snowup.wav")
    }
{
    GetGame()->SetEnemy(this);
	SetPosIndex(10);
	SetCollision2(Rect(POS_CENTER_, Vec2(-texsize_.x_ - 64, -texsize_.y_ - 82)
    ));
    SetCollision(Rect(Vec2(POS_CENTER_.x_, POS_CENTER_.y_ - 20), Vec2(-texsize_.x_ - 64, -texsize_.y_ - 82)));
	SetPosition(Vec2(GetCollision2().center_.x_, GetCollision2().center_.y_ - ADJUST_VALUE_Y_));
    current_animation_ = new AnimSpriteComponent(this, layer_);
}
Enemy::~Enemy()
{
    GetGame()->RemoveAllEArmor();
    GetGame()->RemoveAllEgolem();
    GetGame()->RemoveAllEIceWall();
}
void Enemy::SetHit()
{
    ChangeTexture(EC(ANIMATION_INDEX::HIT));

}
void Enemy::SetDestination()
{//派生クラスのChangeState()で
    switch (direction_ = Direction())
    {
    case D_LEFT:
        PlaySound(sounds_[1], 0);
        destination_ = Vec2(GetCollision2().center_.x_ - MOV_DISTANCE_.x_, GetCollision2().center_.y_);
        if (destination_.x_ <= POS_CENTER_.x_ - MOV_DISTANCE_.x_)
            destination_.x_ = POS_CENTER_.x_ - MOV_DISTANCE_.x_;
        break;
    case D_RIGHT:
        PlaySound(sounds_[1], 0);
        destination_ = Vec2(GetCollision2().center_.x_ + MOV_DISTANCE_.x_, GetCollision2().center_.y_);
        if (destination_.x_ >= POS_CENTER_.x_ + MOV_DISTANCE_.x_)
            destination_.x_ = POS_CENTER_.x_ + MOV_DISTANCE_.x_;
        break;
    case D_UP:
        PlaySound(sounds_[1], 0);
        destination_ = Vec2(GetCollision2().center_.x_, GetCollision2().center_.y_ - MOV_DISTANCE_.y_);
        if (destination_.y_ <= POS_CENTER_.y_ - MOV_DISTANCE_.y_)
            destination_.y_ = POS_CENTER_.y_ - MOV_DISTANCE_.y_;
        break;
    case D_DOWN:
        PlaySound(sounds_[1], 0);
        destination_ = Vec2(GetCollision2().center_.x_, GetCollision2().center_.y_ + MOV_DISTANCE_.y_);
        if (destination_.y_ >= POS_CENTER_.y_ + MOV_DISTANCE_.y_)
            destination_.y_ = POS_CENTER_.y_ + MOV_DISTANCE_.y_;
        break;
    default:
        break;
    }
}

void Enemy::Move(/*int direction*/)
{
	switch (direction_)
	{
	case D_LEFT:
        MoveCollison(Vec2(-VELOCITY_.x_, 0));
		MoveCollison2(Vec2(-VELOCITY_.x_, 0));
		MovePosition(Vec2(-VELOCITY_.x_, 0));
		if (GetCollision2().center_.x_ <= destination_.x_ + MOV_DISTANCE_.x_ * 0.5f &&
            GetCollision2().center_.x_ > destination_.x_ + MOV_DISTANCE_.x_ * 0.5f - VELOCITY_.x_)
		{
			SetPosIndex(GetPosIndex() - 1);
		}
        ChangeTexture(EC(ANIMATION_INDEX::MOVE_FRONT));
		if (GetCollision2().center_.x_ <= destination_.x_)
		{

            SetCollision2(Rect(destination_, GetCollision2().size_));
            SetCollision(Rect(Vec2(destination_.x_, destination_.y_ - 20), GetCollision2().size_));
            SetPosition(Vec2(destination_.x_, destination_.y_ - ADJUST_VALUE_Y_));
			in_action_ = false;
			SetState(Idle);
			direction_ = -1;
            ChangeTexture(EC(ANIMATION_INDEX::MOVE_UPANDDOWN));
		}
		break;
	case D_RIGHT:
		MoveCollison2(Vec2(VELOCITY_.x_, 0));
        MoveCollison(Vec2(VELOCITY_.x_, 0));
		MovePosition(Vec2(VELOCITY_.x_, 0));
		if (GetCollision2().center_.x_ >= destination_.x_ - MOV_DISTANCE_.x_ * 0.5f &&
            GetCollision2().center_.x_ < destination_.x_ - MOV_DISTANCE_.x_ * 0.5f + VELOCITY_.x_)
		{
			SetPosIndex(GetPosIndex() + 1);
		}
        ChangeTexture(EC(ANIMATION_INDEX::MOVE_BACK));
		if (GetCollision2().center_.x_ >= destination_.x_)
		{
            SetCollision2(Rect(destination_, GetCollision2().size_));
            SetCollision(Rect(Vec2(destination_.x_, destination_.y_ - 20), GetCollision2().size_));
            SetPosition(Vec2(destination_.x_, destination_.y_ - ADJUST_VALUE_Y_));
			in_action_ = false;
			SetState(Idle);
			direction_ = -1;
            ChangeTexture(EC(ANIMATION_INDEX::MOVE_UPANDDOWN));
		}
		break;
	case D_UP:
		MoveCollison2(Vec2(0, -VELOCITY_.y_));
        MoveCollison(Vec2(0, -VELOCITY_.y_));
		MovePosition(Vec2(0, -VELOCITY_.y_));
		if (GetCollision2().center_.y_ <= destination_.y_ + MOV_DISTANCE_.y_ * 0.5f &&
			GetCollision2().center_.y_ > destination_.y_ + MOV_DISTANCE_.y_ * 0.5f - VELOCITY_.y_)
		{
			SetPosIndex(GetPosIndex() - 6);
		}
        ChangeTexture(EC(ANIMATION_INDEX::MOVE_UPANDDOWN));
		if (GetCollision2().center_.y_ <= destination_.y_)
		{
            SetCollision2(Rect(destination_, GetCollision2().size_));
            SetCollision(Rect(Vec2(destination_.x_, destination_.y_ - 20), GetCollision2().size_));
            SetPosition(Vec2(destination_.x_, destination_.y_ - ADJUST_VALUE_Y_));
			in_action_ = false;
			SetState(Idle);
			direction_ = -1;
            ChangeTexture(EC(ANIMATION_INDEX::MOVE_UPANDDOWN));
		}
		break;
	case D_DOWN:
		MoveCollison2(Vec2(0, VELOCITY_.y_));
        MoveCollison(Vec2(0, VELOCITY_.y_));
		MovePosition(Vec2(0, VELOCITY_.y_));
		if (GetCollision2().center_.y_ >= destination_.y_ - MOV_DISTANCE_.y_ * 0.5f &&
            GetCollision2().center_.y_ < destination_.y_ - MOV_DISTANCE_.y_ * 0.5f + VELOCITY_.y_)
		{
			SetPosIndex(GetPosIndex() + 6);
		}
        ChangeTexture(EC(ANIMATION_INDEX::MOVE_UPANDDOWN));
		if (GetCollision2().center_.y_ >= destination_.y_)
		{
            SetCollision2(Rect(destination_, GetCollision2().size_));
            SetCollision(Rect(Vec2(destination_.x_, destination_.y_ - 20), GetCollision2().size_));
            SetPosition(Vec2(destination_.x_, destination_.y_ - ADJUST_VALUE_Y_));
			in_action_ = false;
			SetState(Idle);
			direction_ = -1;
            ChangeTexture(EC(ANIMATION_INDEX::MOVE_UPANDDOWN));
		}
		break;
	default:
		break;
	}
}

void Enemy::Attack()
{
	if (snow_num_ > 0)
	{
        PlaySound(sounds_[0], 0);
		auto bullet{ new Bullet(GetGame(), bullettex_, false, GetPosition()) };
		--snow_num_;
        ChangeTexture(EC(ANIMATION_INDEX::ATTACK));
	}
	SetState(Idle);
	in_action_ = false;
}

void Enemy::Gather()
{
    auto gs = GetState();
    if (in_animation_)
    {
        if (current_animation_->IsAnimEnd() && gs == Gathering_In)
        {
            SetState(Gathering_Loop);
            ChangeTexture(EC(ANIMATION_INDEX::COLLECT_LOOP));
        }
        else if (current_animation_->IsAnimEnd() && gs == Gathering_Loop)
        {
            SetState(Gathering_Out);
            ChangeTexture(EC(ANIMATION_INDEX::COLLECT_OUT));
        }
        else if (current_animation_->IsAnimEnd() && gs == Gathering_Out)
        {
            in_action_ = false;
            in_animation_ = false;
            SetState(Idle);
            ChangeTexture(EC(ANIMATION_INDEX::IDLE));
        }
    }
    else
    {
        if (stage_->GetUseSnow(GetPosIndex()))
        {
            PlaySound(sounds_[2], 0);
            stage_->SetSnow(GetPosIndex());
            if (snow_num_ < POSSESSION_MAX_)
            {
                snow_num_ += 2;
                if (snow_num_ > POSSESSION_MAX_) snow_num_ = POSSESSION_MAX_;
            }
            ChangeTexture(EC(ANIMATION_INDEX::COLLECT_IN));
            in_animation_ = true;
            in_action_ = true;
        }
        else
        {
            in_action_ = false;
            SetState(Idle);
        }
    }
}

void Enemy::Golem()
{
    if (in_animation_)
    {
        if (current_animation_->IsAnimEnd() && GetState() == Golem_s)
        {
            in_action_ = false;
            in_animation_ = false;
            SetState(Idle);
            ChangeTexture(EC(ANIMATION_INDEX::IDLE));
        }
    }
    else
    {
        if (snow_num_ >= EC(Costs::GOLEM) && !position_info_.is_golem)
        {
            if (GetGame()->AddEGolem(new EGolem(GetGame(), GetPosition(), bullettex_, layer_, GetPosIndex())))
            {
                PlaySound(sounds_[3], 0);
                snow_num_ -= EC(Costs::GOLEM);
                ChangeTexture(EC(ANIMATION_INDEX::USE_SKILL));
                in_animation_ = true;
            }
        }
        else
        {
            in_action_ = false;
            SetState(Idle);
        }
    }
}

void Enemy::Wall()
{
    if (in_animation_)
    {
        if (current_animation_->IsAnimEnd() && GetState() == IceWall_s)
        {
            in_action_ = false;
            in_animation_ = false;
            SetState(Idle);
            ChangeTexture(EC(ANIMATION_INDEX::IDLE));
        }
    }
    else
    {
        if (snow_num_ >= EC(Costs::ICEWALL) && !position_info_.is_wall)
        {
            if (GetGame()->AddEIceWall(new EIceWall(GetGame(), GetPosition(), layer_, GetPosIndex())))
            {
                PlaySound(sounds_[3], 0);
                snow_num_ -= EC(Costs::ICEWALL);
                ChangeTexture(EC(ANIMATION_INDEX::USE_SKILL));
                in_animation_ = true;
            }
            else
            {
                in_action_ = false;
                SetState(Idle);
            }
        }
        else
        {
            in_action_ = false;
            SetState(Idle);
        }
    }
}

void Enemy::BigSnow()
{
    if (in_animation_)
    {
        if (current_animation_->IsAnimEnd() && GetState() == BigBullet_s)
        {
            in_action_ = false;
            in_animation_ = false;
            SetState(Idle);
            ChangeTexture(EC(ANIMATION_INDEX::IDLE));
        }
    }
    else
    {
        if (snow_num_ >= EC(Costs::BIGBULLET))
        {
            PlaySound(sounds_[3], 0);
            auto skill = new EBigBullet(GetGame(), GetPosition(), layer_);
            snow_num_ -= EC(Costs::BIGBULLET);
            ChangeTexture(EC(ANIMATION_INDEX::USE_SKILL));
            in_animation_ = true;
        }
        else
        {
            in_action_ = false;
            SetState(Idle);
        }
    }
}

void Enemy::UpdateLayer()
{
	if (GetPosIndex() >= 3 && GetPosIndex() <= 5)
		layer_ = 110;
	else if (GetPosIndex() >= 9 && GetPosIndex() <= 11)
		layer_ = 120;
	else
		layer_ = 130;
}

void Enemy::UpdatePositionInfo()
{
    int hor = static_cast<int>(Distance(this, RP()) * 0.01);
    int ver = RP()->GetPosition().y_ - GetPosition().y_;
    position_info_.h_distance = hor;
    position_info_.v_distance = ver;
	auto CheckPosInfo = [this](int a, int b, int c)->bool
	{
        auto pos = GetPosIndex();
		return pos == a || pos == b || pos == c;
	};
    //=========================================================//// □□□｜■■■
    position_info_.upper_part       = CheckPosInfo(3, 4, 5);     // □□□｜□□□
                                                                 // □□□｜□□□
  
    //=========================================================//// □□□｜□□□
    position_info_.h_center_part    = CheckPosInfo(9, 10, 11);   // □□□｜■■■
                                                                 // □□□｜□□□

    //=========================================================//// □□□｜□□□
    position_info_.lower_part       = CheckPosInfo(15, 16, 17);  // □□□｜□□□
                                                                 // □□□｜■■■

    //=========================================================//// □□□｜■□□
    position_info_.left_part        = CheckPosInfo(3, 9, 15);    // □□□｜■□□
                                                                 // □□□｜■□□

    //=========================================================//// □□□｜□■□
    position_info_.v_center_part    = CheckPosInfo(4, 10, 16);   // □□□｜□■□
                                                                 // □□□｜□■□

    //=========================================================//// □□□｜□□■
    position_info_.right_part       = CheckPosInfo(5, 11, 17);   // □□□｜□□■
                                                                 // □□□｜□□■
                                                                 // 

	////=========================================================//// □□□｜□□□
	//if (stage_->GetUseSnow(GetPosIndex() - 3))                   // □■□｜□Ｅ□
	//	position_info_.is_snow         = true       ;            // □□□｜□□□
	//else
	//	position_info_.is_snow         = false      ;

	//=========================================================//// □■□｜□□□
	if (RP()->GetPosIndex() == GetPosIndex() - 3 ||              // □■□｜□Ｅ□
		RP()->GetPosIndex() == GetPosIndex() + 3 ||              // □■□｜□□□
		RP()->GetPosIndex() == GetPosIndex() - 9)
		position_info_.h_dist_is_three = true       ;
	else
		position_info_.h_dist_is_three = false      ;

    //=========================================================//// □□□｜□□□
    if (GetPosIndex() - RP()->GetPosIndex() > 0 &&               // □Ｐ□｜□Ｅ□
        GetPosIndex() - RP()->GetPosIndex() < 6)                 // □□□｜□□□
        position_info_.same_row        = true       ;
    else
        position_info_.same_row        = false      ;

    //=========================================================//
    for (const auto& iw : GetGame()->GetEIceWalls())
    {
        if (iw)
        {
            if (iw->GetPosIndex() - GetPosIndex() <= 0 && iw->GetPosIndex() - GetPosIndex() >= -2)
            {
                position_info_.is_behind_wall = true   ;
                break                                  ;
            }
            else
                position_info_.is_behind_wall = false  ;
        }
    }

    //=========================================================//
    for (const auto& iw : GetGame()->GetEIceWalls())
    {
        if (iw)
        {
            if (iw->GetPosIndex() == GetPosIndex())
            {
                position_info_.is_wall = true;
                break;
            }
            else
                position_info_.is_wall = false;
        }
        else
        {
            position_info_.is_wall = false;
        }
    }

    //=========================================================//
    for (const auto& go : GetGame()->GetEGolems())
    {
        if (go)
        {
            if (go->GetPosIndex() == GetPosIndex())
            {
                position_info_.is_golem = true;
                break;
            }
            else
                position_info_.is_golem = false;
        }
        else
        {
            position_info_.is_golem = false;
        }
    }
    //=========================================================//
    //for(const auto& ps : GetGame()->GetA)
}

void Enemy::UpdateDirection()
{
    prob_info_ = Probabilities(); // デフォルト
    if (position_info_.upper_part) // 上に行く確率
    {
        prob_info_.up_ = 0;
    }
    else
    {
        prob_info_.up_ = 30.0;
        if (position_info_.h_distance > 1 && position_info_.same_row)
        {
            prob_info_.up_ += 20;
        }
    }

    if (position_info_.lower_part) // 下に行く確率
    {
        prob_info_.down_ = 0;
    }
    else
    {
        prob_info_.down_ = 30.0;
        if (position_info_.h_distance > 1 && position_info_.same_row)
        {
            prob_info_.down_ += 20;
        }
    }

    if (position_info_.left_part) // 左に行く確率
    {
        prob_info_.left_ = 0;
    }
    else
    {
        prob_info_.left_ = 20.0;
    }

    if (position_info_.right_part) // 右に行く確率
    {
        prob_info_.right_ = 0;
    }
    else
    {
        prob_info_.right_ = 20.0;
        if (position_info_.h_distance < 3)
        {
            prob_info_.right_ += 15;
        }
    }
    
    
}

void Enemy::UpdateNextAction()
{

    if (position_info_.same_row)
    {
        prob_info_.attack_ += 70;
        prob_info_.unique_ += 10;
    }
    if (position_info_.same_row && position_info_.h_distance <= 3)
        prob_info_.attack_ = 85;

    if (position_info_.left_part)
    {
        prob_info_.icewall_ = 55;
        prob_info_.gather_  = 20;
    }
    else if (position_info_.v_center_part)
    {
        prob_info_.golem_  += 10;
    }
    else
    {
        prob_info_.icewall_ = 15;
        prob_info_.gather_  += 5;
        prob_info_.golem_  -= 10;
    }

    

    if (position_info_.is_behind_wall)
    {
        prob_info_.gather_ += 35;
        prob_info_.attack_ += 5;
    }

    if (snow_num_ < 6)
    {
        prob_info_.gather_ += 15;
    }
    else if (snow_num_ > 12)
    {
        prob_info_.gather_ -= 15;
    }
}

int Enemy::Direction()
{
    std::random_device              rnd;
    std::mt19937                    mt(rnd());
    std::uniform_int_distribution<> uid(1, prob_info_.up_ + prob_info_.down_ + prob_info_.left_ + prob_info_.right_);
    auto                            p   { uid(mt) };
    double                          sum { 0.0     };
    if (sum < p && p <= prob_info_.up_)
        return D_UP;

    sum += prob_info_.up_;
    if (sum < p && p <= sum + prob_info_.down_)
        return D_DOWN;

    sum += prob_info_.down_;
    if (sum < p && p <= sum + prob_info_.left_)
        return D_LEFT;

    sum += prob_info_.left_;
    if (sum < p && p <= sum + prob_info_.right_)
        return D_RIGHT;
}
#else
/// <summary>
/// /////////////////
/// </summary>
/// <param name="game"></param>
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
	this->enemy_pos_num_ = 5;										//いるマスの番号

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
			if (enemy_pos_num_ % 3 > 0)
				this->enemy_pos_num_--;

			this->enemy_direction_ = 0;
			break;
		case 1:
			if (enemy_pos_num_ % 3 < 2)
				this->enemy_pos_num_++;
			this->enemy_direction_ = 1;
			break;
		case 2:
			if (enemy_pos_num_ > 2)
				this->enemy_pos_num_ -= 3;
			this->enemy_direction_ = 2;
			break;
		case 3:
			if (enemy_pos_num_ < 6)
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
#endif