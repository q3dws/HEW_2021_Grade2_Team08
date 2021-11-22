#include "Snow.h"
#include "SpriteComponent.h"
//#include "AnimSpriteComponent.h"
#include "input.h"
#include "Math.h"
#include "Texture.h"

Snow::Snow(Game* game)
	:Actor(game), is_snow_(), timer_(),index_(),sprite_actor_()
{
		/*auto set_snow = new SpriteComponent(this, 90);
		set_snow->SetTexture(game->GetTexture(L"Data/Image/Snow.png"), Vec2(SNOW_SIZE_X, SNOW_SIZE_Y), Vec2(0, 0), Vec2(1, 1));
		*/
	tex_no_ = LoadTexture(L"Data/Image/Snow.png");

	//アニメーション

	//auto SetAnimSnow = new AnimSpriteComponent(this, 90);
	//SetAnimSnow->SetAnimTextures(game->GetTexture(L"Data/Image/Snow.png"), Vec2(SNOW_SIZE_X, SNOW_SIZE_Y), 10, 5.f);
	
}



void Snow::UpdateActor(float deltatime)
{
	if (timer_ < TIMER_MAX)
	{
		/*if (sprite_actor_)
		{
			delete sprite_actor_;
		}*/
			
		++timer_;

	}
	else
	{
		if (!sprite_actor_)
		{
			sprite_actor_ = new Actor(GetGame());
			sprite_actor_->SetPosition(this->GetPosition());
			auto sprite_ = new SpriteComponent(sprite_actor_, 90);
			sprite_->SetTexture(tex_no_, Vec2(SNOW_SIZE_X, SNOW_SIZE_Y), Vec2(0, 0), Vec2(1, 1));
			
			is_snow_ = true;
		}
	}
}