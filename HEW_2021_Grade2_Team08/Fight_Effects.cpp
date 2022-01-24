#include "Fight_Effects.h"

Fight_Effects::Fight_Effects(Game* game, Vec2 pos, Vec2 size, int time, int texnum) : Actor(game)
, fight_effects_size_(size)
,fight_effects_pos_(pos)
, k_fight_effects_layer_(200)
, k_fight_effects_Deadtime_(time)
, k_fight_effects_tex_{
	LoadTexture(L"Data/Image/UI/result/clear.png")
		,LoadTexture(L"Data/Image/UI/result/lose.png")
		,LoadTexture(L"Data/Image/UI/result/win.png")
		,LoadTexture(L"Data/Image/UI/result/fight.png")
		,LoadTexture(L"Data/Image/UI/result/ready.png")
	,LoadTexture(L"Data/Image/UI/result/timeup.png")
	,LoadTexture(L"Data/Image/UI/result/waku.png")
		,LoadTexture(L"Data/Image/UI/result/clear_anime.png")
		,LoadTexture(L"Data/Image/UI/result/lose_anime.png")
		,LoadTexture(L"Data/Image/UI/result/win_anime.png")
	,LoadTexture(L"Data/Image/UI/result/fight_in.png")
		,LoadTexture(L"Data/Image/UI/result/fight_out.png")
		,LoadTexture(L"Data/Image/UI/result/ready_in.png")
		,LoadTexture(L"Data/Image/UI/result/ready_out.png")
	,LoadTexture(L"Data/Image/UI/result/timeup_in.png")
		,LoadTexture(L"Data/Image/UI/result/timeup_out.png")
	,LoadTexture(L"Data/Image/UI/result/waku_in.png")
	,LoadTexture(L"Data/Image/UI/result/waku_out.png")
		
}
{
	fight_effects_next_ = 0;
	fight_effects_time_ = 0;
	fight_effects_count_ = 0;
	fight_effects_deadcount_ = 0;

	fight_effects_asc_ = new AnimSpriteComponent(this, k_fight_effects_layer_);
	//bigsnow_asc_->SetTexture(k_bigsnow_tex_, bigsnow_size_, Vec2(0, 0), Vec2(1, 1));
	//fight_effects_asc_->SetAnimTextures(k_fight_effects_tex_[texnum], fight_effects_size_, static_cast<int>(texnum), 5.f);

	Fight_Effects::Fight_Effects_texchange(texnum);

	SetPosition(fight_effects_pos_);
}

Fight_Effects::~Fight_Effects()
{
}

void Fight_Effects::UpdateActor(float delttime)
{

	fight_effects_count_ += 5 * delttime;
	fight_effects_deadcount_ += 5 * delttime;

	if (fight_effects_count_ >= fight_effects_time_
		&& fight_effects_next_ != static_cast<int>(fight_effects_Motion::END))
	{
		Fight_Effects::Fight_Effects_texchange(fight_effects_next_);
		fight_effects_count_ = 0;
	}
	else if (fight_effects_next_ == static_cast<int>(fight_effects_Motion::END)
		&& fight_effects_deadcount_ >= k_fight_effects_Deadtime_
		&& fight_effects_count_ >= fight_effects_time_)
	{
		SetState(Dead);
	}
}


//なんか正気とは思えないソースコードになったのでリファクタリング予定
void Fight_Effects::Fight_Effects_texchange(int texnum)
{
	
	if (texnum <= static_cast<int>(fight_effects_Motion::WAKU))
	{
		fight_effects_asc_->SetAnimTextures(k_fight_effects_tex_[texnum]
			, fight_effects_size_
			,1, 5.f);

		switch (texnum)
		{
		case static_cast<int>(fight_effects_Motion::READY):
			fight_effects_time_ = k_fight_effects_Deadtime_ - 5 * static_cast<int>(fight_effects_frame_num::READY);
			fight_effects_next_ = static_cast<int>(fight_effects_Motion::READY_OUT);
			break;
		case static_cast<int>(fight_effects_Motion::TIMEUP):
			fight_effects_time_ = k_fight_effects_Deadtime_ - 5 *  static_cast<int>(fight_effects_frame_num::TIMEUP);
			fight_effects_next_ = static_cast<int>(fight_effects_Motion::TIMEUP_OUT);
			break;
		case static_cast<int>(fight_effects_Motion::FIGHT):
			fight_effects_time_ = k_fight_effects_Deadtime_ - 5 *  static_cast<int>(fight_effects_frame_num::FIGHT);
			fight_effects_next_ = static_cast<int>(fight_effects_Motion::FIGHT_OUT);
			break;
		case static_cast<int>(fight_effects_Motion::WAKU):
			fight_effects_time_ = k_fight_effects_Deadtime_ - 5 *  static_cast<int>(fight_effects_frame_num::WAKU);
			fight_effects_next_ = static_cast<int>(fight_effects_Motion::WAKU_OUT);
			break;
		default:
			fight_effects_next_ = static_cast<int>(fight_effects_Motion::END);
			break;
		}
		return;
	}

	switch (texnum)
	{
	case static_cast<int>(fight_effects_Motion::CLEAR_ANIM):
		fight_effects_asc_->SetAnimTextures(k_fight_effects_tex_[texnum]
			, fight_effects_size_
			, static_cast<int>(fight_effects_frame_num::CLEAR_ANIM), 5.f);

		fight_effects_time_ = static_cast<int>(fight_effects_frame_num::CLEAR_ANIM);
		fight_effects_next_ = static_cast<int>(fight_effects_Motion::CLEAR);
		break;
	case static_cast<int>(fight_effects_Motion::LOSE_ANIM):
		fight_effects_asc_->SetAnimTextures(k_fight_effects_tex_[texnum]
			, fight_effects_size_
			, static_cast<int>(fight_effects_frame_num::LOSE_ANIM), 5.f);

		fight_effects_time_ = static_cast<int>(fight_effects_frame_num::LOSE_ANIM);
		fight_effects_next_ = static_cast<int>(fight_effects_Motion::LOSE);
		break;
	case static_cast<int>(fight_effects_Motion::WIN_ANIM):
		fight_effects_asc_->SetAnimTextures(k_fight_effects_tex_[texnum]
			, fight_effects_size_
			, static_cast<int>(fight_effects_frame_num::WIN_ANIM), 5.f);

		fight_effects_time_ = static_cast<int>(fight_effects_frame_num::WIN_ANIM);
		fight_effects_next_ = static_cast<int>(fight_effects_Motion::WIN);
		break;
	case static_cast<int>(fight_effects_Motion::FIGHT_IN):
		fight_effects_asc_->SetAnimTextures(k_fight_effects_tex_[texnum]
			, fight_effects_size_
			, static_cast<int>(fight_effects_frame_num::FIGHT_IN), 5.f);

		fight_effects_time_ = static_cast<int>(fight_effects_frame_num::FIGHT_IN);
		fight_effects_next_ = static_cast<int>(fight_effects_Motion::FIGHT);
		break;
	case static_cast<int>(fight_effects_Motion::FIGHT_OUT):
		fight_effects_asc_->SetAnimTextures(k_fight_effects_tex_[texnum]
			, fight_effects_size_
			, static_cast<int>(fight_effects_frame_num::FIGHT_OUT), 5.f);

		fight_effects_time_ = static_cast<int>(fight_effects_frame_num::FIGHT_OUT);
		fight_effects_next_ = static_cast<int>(fight_effects_Motion::END);
		break;
	case static_cast<int>(fight_effects_Motion::READY_IN):
		fight_effects_asc_->SetAnimTextures(k_fight_effects_tex_[texnum]
			, fight_effects_size_
			, static_cast<int>(fight_effects_frame_num::READY_IN), 5.f);

		fight_effects_time_ = static_cast<int>(fight_effects_frame_num::READY_IN);
		fight_effects_next_ = static_cast<int>(fight_effects_Motion::READY);
		break;
	case static_cast<int>(fight_effects_Motion::READY_OUT):
		fight_effects_asc_->SetAnimTextures(k_fight_effects_tex_[texnum]
			, fight_effects_size_
			, static_cast<int>(fight_effects_frame_num::READY_OUT), 5.f);

		fight_effects_time_ = static_cast<int>(fight_effects_frame_num::READY_OUT);
		fight_effects_next_ = static_cast<int>(fight_effects_Motion::FIGHT_IN);
		break;
	case static_cast<int>(fight_effects_Motion::TIMEUP_IN):
		fight_effects_asc_->SetAnimTextures(k_fight_effects_tex_[texnum]
			, fight_effects_size_
			, static_cast<int>(fight_effects_frame_num::TIMEUP_IN), 5.f);

		fight_effects_time_ = static_cast<int>(fight_effects_frame_num::TIMEUP_IN);
		fight_effects_next_ = static_cast<int>(fight_effects_Motion::TIMEUP);
		break;
	case static_cast<int>(fight_effects_Motion::TIMEUP_OUT):
		fight_effects_asc_->SetAnimTextures(k_fight_effects_tex_[texnum]
			, fight_effects_size_
			, static_cast<int>(fight_effects_frame_num::TIMEUP_OUT), 5.f);

		fight_effects_time_ = static_cast<int>(fight_effects_frame_num::TIMEUP_OUT);
		fight_effects_next_ = static_cast<int>(fight_effects_Motion::END);
		break;
	case static_cast<int>(fight_effects_Motion::WAKU_IN):
		fight_effects_asc_->SetAnimTextures(k_fight_effects_tex_[texnum]
			, fight_effects_size_
			, static_cast<int>(fight_effects_frame_num::WAKU_IN), 5.f);

		fight_effects_time_ = static_cast<int>(fight_effects_frame_num::WAKU_IN);
		fight_effects_next_ = static_cast<int>(fight_effects_Motion::WAKU);
		break;
	case static_cast<int>(fight_effects_Motion::WAKU_OUT):
		fight_effects_asc_->SetAnimTextures(k_fight_effects_tex_[texnum]
			, fight_effects_size_
			, static_cast<int>(fight_effects_frame_num::WAKU_OUT), 5.f);

		fight_effects_time_ = static_cast<int>(fight_effects_frame_num::WAKU_OUT);
		fight_effects_next_ = static_cast<int>(fight_effects_Motion::END);
		break;
	default:
		break;
	}
}
