#include "Icicle.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "FallPoint.h"
#include "Player.h" //  
#include "Enemy.h"

#if 0 
Icicle::Icicle(Game* game, const Vec2& destination, int index_x, int index_y, int icicle_index)
	:Actor(game)
	, fp_(new FallPoint(GetGame(), destination, icicle_index))
	, destination_(destination)
	, texno_(icicle_index)
{
	SetPosIndex(icicle_index);
	texno_ = LoadTexture(L"Data/Image/13558.png");
	SetPosition(Vec2(SNOW_POS_X + index_x * 113, 200 - SNOW_POS_Y + index_y * 75));
	Icicle_Sprite_ = new SpriteComponent(this, 120);
	Icicle_Sprite_->SetTexture(texno_, Vec2(ICICLE_SIZE, ICICLE_SIZE), Vec2(0, 0), Vec2(1, 1));

	// ★当たり判定用の矩形の設定　中心座標とサイズを設定
	SetCollision(Rect(Vec2(SNOW_POS_X + index_x * 113, 200 - SNOW_POS_Y + index_y * 75), Vec2(ICICLE_SIZE, ICICLE_SIZE)));
	// ★このアクターのいるマス目の配列要素番号の設定
	SetPosIndex(icicle_index);
}

Icicle::~Icicle()
{
	fp_->SetState(Dead);
}

void Icicle::UpdateActor(float deltatime)
{

	SetPosition(Vec2(GetPosition().x_, GetPosition().y_ + move_));
	MoveCollison(Vec2(0, move_)); //コリジョン矩形をmove_分移動
	// ★個人的にはキャラ以外の弾などは中心で当たり判定を取った方が見栄え良いような気がしてる。
	if (CollisionRC(GetGame()->GetPlayer(), this)) // ★プレイヤーとこのつららが当たっていたら消える
	{
		GetGame()->GetScoreManager()->AddScore(1);
		SetState(Dead);
	}
		
	if (GetPosition().y_ > destination_.y_)
		SetState(Dead);
}

#else
Icicle::Icicle(Game* game, const Vec2& destination, int index_x, int index_y, int icicle_index)
    :Actor(game)
    , fp_(new FallPoint(GetGame(), destination, icicle_index))
    , destination_(destination)
    , texno_(icicle_index)
{
    texno_ = LoadTexture(L"Data/Image/turara.png");

    SetPosition(Vec2(SNOW_POS_X + index_x * 113, 200 - SNOW_POS_Y + index_y * 75));
    SetPosIndex(icicle_index);
    SetCollision(Rect(GetPosition(), Vec2(ICICLE_SIZE, ICICLE_SIZE)));

    Icicle_Sprite_ = new SpriteComponent(this, 120);
    Icicle_Sprite_->SetTexture(texno_, Vec2(ICICLE_SIZE, ICICLE_SIZE), Vec2(0, 0), Vec2(1, 1));

}

Icicle::~Icicle()
{
    fp_->SetState(Dead);
}

void Icicle::UpdateActor(float deltatime)
{
    SetPosition(Vec2(GetPosition().x_, GetPosition().y_ + move_));
    MoveCollison(Vec2(0, move_));
    if (GetGame()->GetPlayer())
    {
        if (CollisionRC(GetGame()->GetPlayer(), this)) // ★プレイヤーとこのつららが当たっていたら消える
        {
            GetGame()->GetScoreManager()->EnemyAddScore(1);
            SetState(Dead);
        }
    }
    if (GetGame()->GetPlayer2p())
    {
        if (CollisionRC(GetGame()->GetPlayer2p(), this)) // ★プレイヤーとこのつららが当たっていたら消える
        {
            GetGame()->GetScoreManager()->EnemyAddScore(1);
            SetState(Dead);
        }
    }
    if (GetGame()->GetEnemy())
    {
        if (CollisionRC(GetGame()->GetEnemy(), this)) // ★enemyとこのつららが当たっていたら消える
        {
            GetGame()->GetScoreManager()->AddScore(1);
            SetState(Dead);
        }
    }
    
    if (GetPosition().y_ > destination_.y_)
    {
        ico_ = new IcicleOut(GetGame(), destination_);
        SetState(Dead);
    }
}
#endif
