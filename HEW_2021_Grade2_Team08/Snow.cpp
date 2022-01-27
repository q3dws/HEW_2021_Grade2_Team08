#include "Snow.h"
#include "SpriteComponent.h"
#include "input.h"
#include "Math.h"
#include "Texture.h"

Snow::Snow(Game* game, int index, Vec2 pos)
	:Actor(game), is_snow_(), timer_(), index_(index), sprite_actor_()
{
	SetPosition(pos);
	tex_no_ = LoadTexture(L"Data/Image/snow00.png");

	sprite_actor_ = new Actor(game);
	sprite_actor_->SetScale(0.0f);

	sprite_ = new SpriteComponent(sprite_actor_, 90);
	sprite_->SetTexture(tex_no_, Vec2(SNOW_SIZE_X, SNOW_SIZE_Y), Vec2(0, 0), Vec2(1, 1));

}

Snow::~Snow()
{
	sprite_actor_->SetScale(0.0f);
}



void Snow::UpdateActor(float deltatime)
{
	sprite_actor_->SetPosition(GetPosition());

	if (timer_ < TIMER_MAX)
	{
		if (timer_ == 0)
		{
			is_snow_ = false;
			sprite_actor_->SetScale(0.0f);
		}
		
		if (timer_ == TIMER_MAX * 0.4)
		{
			sprite_actor_->SetScale(0.3f);
		}

		if (timer_ == TIMER_MAX * 0.7)
		{
			sprite_actor_->SetScale(0.6f);

		}

		if (timer_ == TIMER_MAX - 1 )
		{
			sprite_actor_->SetScale(1.0f);

			is_snow_ = true;
		}

		++timer_;
	}
}