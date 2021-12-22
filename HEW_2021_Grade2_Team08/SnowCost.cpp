#include "SnowCost.h"

SnowCost::SnowCost(Game* game, bool Is_player) : Actor(game)
, k_snowframe_tex_ (LoadTexture(L"Data/Image/UI/yukicosttest/snowcostwaku1.png") )
, k_snowpoint_tex_ (LoadTexture(L"Data/Image/UI/yukicosttest/snowmemori1.png"))
,k_frame_size_(Vec2(400,400))
, k_frame_pos_(Vec2(250, 500))
,k_point_pos_(Vec2(k_frame_pos_.x_ - 190, k_frame_pos_.y_ + 8))
,k_point_size_(Vec2(k_frame_size_.x_ / 7, k_frame_size_.y_ / 7))
,k_point_var_(22)
,k_point_num_(18)
,k_Is_player_(Is_player)
{
    frame_asc_ = new SpriteComponent(this, 151);
    frame_asc_->SetTexture(k_snowframe_tex_, k_frame_size_, Vec2(0, 0), Vec2(1, 1));

    if (k_Is_player_ == false)
    {
        k_frame_pos_ = (Vec2(WINDOW_WIDTH - k_frame_pos_.x_, k_frame_pos_.y_ ));
        k_point_pos_ = (Vec2(k_frame_pos_.x_ - 190, k_frame_pos_.y_ + 8));
    }

    SetPosition(k_frame_pos_);
    //k_point_num_の分だけメモリスプライトを生成する
    for (int i = 0; i <= k_point_num_ - 1; i++)
    {
        snowpoints_.emplace_back(new SnowPoint(GetGame(), k_snowpoint_tex_, k_point_pos_, k_point_size_));
        snowpoints_.back()->SetPosition(Vec2(k_point_pos_.x_ + i * k_point_var_, k_point_pos_.y_));
    }
    
}

SnowCost::~SnowCost()
{
}

void SnowCost::UpdateActor(float deltatime)
{
    Actor::UpdateActor(deltatime);
}

//プレイヤーの持っている雪の数を渡すとその分メモリを可視化する関数
void SnowCost::SetSnownum(int num)
{
    if (snowpoints_.empty() == false)
    {
        for (int i = 1; i <= k_point_num_; i++)
        {
            if (i <= num)
            {
                snowpoints_[i-1]->pointUVWHset(Vec2(1, 1));
            }
            else
            {
                snowpoints_[i-1]->pointUVWHset(Vec2(0, 0));
            }
        }
    }

    //敵用
    if (k_Is_player_ == false)
    {
        if (snowpoints_.empty() == false)
        {
            for (int i = 1; i <= k_point_num_; i++)
            {
                if (i <= num)
                {
                    snowpoints_[k_point_num_ - i]->pointUVWHset(Vec2(1, 1));
                }
                else
                {
                    snowpoints_[k_point_num_ - i]->pointUVWHset(Vec2(0, 0));
                }
            }
        }
    }
   
}

//-------------------------------------------------------
//メモリ側
//-------------------------------------------------------
SnowPoint::SnowPoint(Game* game, int tex, Vec2 pos, Vec2 size)
    :Actor(game)
    ,k_point_size(size)
{
    point_asc_ = new SpriteComponent(this, 150);
   
    UVWH = Vec2(0, 0);
    point_asc_->SetTexture(tex, k_point_size, Vec2(0, 0), UVWH);

    SetPosition(pos);
}

SnowPoint::~SnowPoint()
{

}

void SnowPoint::UpdateActor(float deltatime)
{
    Actor::UpdateActor(deltatime);

    point_asc_->SetUV(Vec2(0,0), UVWH);
}

//メモリの描画の薄さを変える関数
void SnowPoint::pointUVWHset(Vec2 uvwh)
{
    UVWH = uvwh;
}
