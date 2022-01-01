#include "Skillicon.h"


Skillicon::Skillicon(Game* game, bool Is_player,int who, int skillcost0, int skillcost1, int skillcost2, int skillcost3) : Actor(game)
,k_Is_player_(Is_player)
,k_Skillicon_num_(4)
,k_Skillicon_pos_(Vec2(150,470)) //ゲージ上 150 470
,k_Skillicon_size_(Vec2(40,40))	//ゲージ上 40 40
,k_Skillicon_var_(30)					//ゲージ上 30
,k_snowcost_{skillcost0,skillcost1,skillcost2,skillcost3}
,k_who_player_(who)
,k_Skillicon_tex_
{
	LoadTexture(L"Data/Image/UI/skill/UI_golem.png")
	,LoadTexture(L"Data/Image/UI/skill/UI_golem_dark.png")
	,LoadTexture(L"Data/Image/UI/skill/UI_icewall.png")
	,LoadTexture(L"Data/Image/UI/skill/UI_icewall_dark.png")
	,LoadTexture(L"Data/Image/UI/skill/UI_snowbig.png")
	,LoadTexture(L"Data/Image/UI/skill/UI_snowbig_dark.png")
	//charaA
	,LoadTexture(L"Data/Image/UI/skill/UI_snow.png")
	,LoadTexture(L"Data/Image/UI/skill/UI_snow_dark.png")
	//charaB
	,LoadTexture(L"Data/Image/UI/skill/amor.png")
	,LoadTexture(L"Data/Image/UI/skill/amor_dark.png")
	//charaC
	,LoadTexture(L"Data/Image/UI/skill/UI_fire.png")
	,LoadTexture(L"Data/Image/UI/skill/UI_fire_dark.png")
	//charaD
	,LoadTexture(L"Data/Image/UI/skill/UI_snowbig.png")
	,LoadTexture(L"Data/Image/UI/skill/UI_snowbig_dark.png")
}
{

	//k_Skillicon_num_の分だけメモリスプライトを生成する
	if(k_Is_player_)
		for (int i = 0; i < k_Skillicon_num_ * 2; i += 2)
		{
			if (i == k_Skillicon_num_ * 2 - 2)
			{
				icons_.emplace_back(new Icon(GetGame(), Vec2(k_Skillicon_pos_.x_ + i * k_Skillicon_var_, k_Skillicon_pos_.y_)
					, k_Skillicon_size_, 150, k_Skillicon_tex_[i + k_who_player_ * 2], k_Skillicon_tex_[i + 1 + k_who_player_ * 2]));
			}
			else
				icons_.emplace_back(new Icon(GetGame(), Vec2(k_Skillicon_pos_.x_ + i * k_Skillicon_var_, k_Skillicon_pos_.y_)
					, k_Skillicon_size_, 150, k_Skillicon_tex_[i], k_Skillicon_tex_[i + 1]));

		}
	else
		for (int i = 0; i < k_Skillicon_num_ * 2; i += 2)
		{
			if (i == k_Skillicon_num_ * 2 - 2)
			{
				icons_.emplace_back(new Icon(GetGame()
					,Vec2(WINDOW_WIDTH - k_Skillicon_pos_.x_ - i * k_Skillicon_var_, k_Skillicon_pos_.y_)
					, k_Skillicon_size_, 150, k_Skillicon_tex_[i + k_who_player_ * 2], k_Skillicon_tex_[i + 1 + k_who_player_ * 2]));
			}
			else
				icons_.emplace_back(new Icon(GetGame()
					, Vec2(WINDOW_WIDTH - k_Skillicon_pos_.x_ - i * k_Skillicon_var_, k_Skillicon_pos_.y_)
					, k_Skillicon_size_, 150, k_Skillicon_tex_[i], k_Skillicon_tex_[i + 1]));

		}
}

Skillicon::~Skillicon()
{
}

void Skillicon::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);
}

void Skillicon::SetSnownum(int snownum)
{
	if (icons_.empty() == false)
	{
		for (int i = 0; i <  k_Skillicon_num_; i++)
		{
			if (snownum >= k_snowcost_[i])
			{
				icons_[i]->Icon_inset();
			}
			else
			{
				icons_[i]->Icon_outset();
			}
		}
	}
}


//
//アイコン側
//
Icon::Icon(Game* game, Vec2 pos, Vec2 size, int layer, int lighttex, int darktex) : Actor(game)
,k_Icon_layer_(layer)
,k_Icon_pos_(pos)
,k_Icon_size_(size)
, k_Icon_tex_{
	lighttex
	,darktex
}
{
	Icon_asc_ = new SpriteComponent(this, k_Icon_layer_);
	Icon_asc_->SetTexture(darktex, k_Icon_size_, Vec2(0, 0), Vec2(1,1));

	SetPosition(pos);
}

Icon::~Icon()
{
}

void Icon::UpdateActor(float delta_time)
{
	Actor::UpdateActor(delta_time);
}

void Icon::Icon_inset()
{
	this->RemoveComponent(Icon_asc_);
	this->GetGame()->RemoveSprite(Icon_asc_);
	Icon_asc_ = new SpriteComponent(this, k_Icon_layer_);
	Icon_asc_->SetTexture(k_Icon_tex_[static_cast<int>(Icon_Motion::light)], k_Icon_size_, Vec2(0, 0), Vec2(1, 1));
}

void Icon::Icon_outset()
{
	this->RemoveComponent(Icon_asc_);
	this->GetGame()->RemoveSprite(Icon_asc_);
	Icon_asc_ = new SpriteComponent(this, k_Icon_layer_);
	Icon_asc_->SetTexture(k_Icon_tex_[static_cast<int>(Icon_Motion::dark)], k_Icon_size_, Vec2(0, 0), Vec2(1, 1));
}
