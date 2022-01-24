#include "Timer.h"
#include "Game.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"
#include "Fight_Effects.h"

Timer::Timer(Game* game, int inittime) : Actor(game)
, remaining_time_(inittime)
, time_MAX_(599)
, count_time_(0)
, time_vel_(3)
{
	second_ = new PlayerScore(game, Vec2(WINDOW_WIDTH / 2 + 31, 50));
	second_ten_ = new PlayerScore(game, Vec2(WINDOW_WIDTH / 2 + 11, 50));
	minute_ = new PlayerScore(game, Vec2(WINDOW_WIDTH / 2 - 20, 50));

	if (remaining_time_ >= time_MAX_)
		remaining_time_ = time_MAX_;
}

Timer::~Timer()
{
	auto a = new Fight_Effects(GetGame(), Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), Vec2(700, 700), 20, static_cast<int>(Fight_Effects::fight_effects_Motion::TIMEUP_IN));
}

void Timer::UpdateActor(float delttime)
{
	Actor::UpdateActor(delttime);
	Timer::SetTime(delttime);

	count_time_ += delttime;
	if (count_time_ >= time_vel_)
	{
		count_time_ = 0;
		remaining_time_ -= 1;
	}
	
	if (remaining_time_ <= -0.25)
	{
		remaining_time_ = 0;
		SetState(Dead);
	}
		
}

//ŽžŠÔ‚Ì•`‰æ
void Timer::SetTime(float deltatime)
{
	int a = remaining_time_ / 60;
	minute_->AddScore(a);

	int b =(remaining_time_  - (a * 60)) / 10;
	second_ten_->AddScore(b);

	int c = (int)(remaining_time_ - (a * 60)) % 10;
	second_->AddScore(c);
}

float Timer::GetTime()
{
	return remaining_time_;
}
