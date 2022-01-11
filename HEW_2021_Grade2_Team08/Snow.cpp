#include "Snow.h"
#include "Snow.h"
#include "SpriteComponent.h"
//#include "AnimSpriteComponent.h"
#include "input.h"
#include "Math.h"
#include "Texture.h"

Snow::Snow(Game* game)
	:Actor(game), is_snow_(), timer_(TIMER_MAX - 1), index_(), sprite_actor_()
{
	//tex_no_ = LoadTexture(L"Data/Image/snow00.png");

	sprite_actor_ = new Actor(game);
	sprite_actor_->SetScale(0.0f);

	sprite_ = new SpriteComponent(sprite_actor_, 90);
	sprite_->SetTexture(game->GetTexture(L"Data/Image/snow00.png"), Vec2(SNOW_SIZE_X, SNOW_SIZE_Y), Vec2(0, 0), Vec2(1, 1));

	//auto SetAnimSnow = new AnimSpriteComponent(this, 90);
	//SetAnimSnow->SetAnimTextures(game->GetTexture(L"Data/Image/Snow.png"), Vec2(SNOW_SIZE_X, SNOW_SIZE_Y), 10, 5.f);

}



void Snow::UpdateActor(float deltatime)
{
	sprite_actor_->SetPosition(GetPosition());

	if (timer_ < TIMER_MAX)
	{
		if (timer_ == 0)
		{
			is_snow_ = false;
		}

		if (timer_ == TIMER_MAX * 0.4)
		{
			sprite_actor_->SetScale(0.3f);
		}

		if (timer_ == TIMER_MAX * 0.7)
		{
			sprite_actor_->SetScale(0.6f);

		}

		if (timer_ == TIMER_MAX - 1)
		{
			sprite_actor_->SetScale(1.0f);

			is_snow_ = true;
		}

		++timer_;

	}
}