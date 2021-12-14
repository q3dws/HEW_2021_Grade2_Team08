#include "Stage.h"
#include "SpriteComponent.h"

Stage::Stage(Game* game)
	:Actor(game), snows_()
{
	for (int i = 0; i < STAGE_Y; ++i)
		for (int j = 0; j < STAGE_X; ++j)
		{
			int tmp = (i * STAGE_X) + j;

			//Snow
			snows_[tmp] = new Snow(game);
			snows_[tmp]->SetPosition(Vec2(SNOW_POS_X + j * 113, SNOW_POS_Y + i * 75));
			snows_[tmp]->index_ = (i * STAGE_X) + j;

		}
}

void Stage::UpdateActor(float deltatime)
{
	timer_++;

	if (timer_ > ICICLE_TIME)
	{
		auto index_x = rand() % 6;
		auto index_y = rand() % 3;
		icicle_index = index_y * STAGE_X + index_x;

		pIcicles_[icicle_index] = new Icicle(GetGame(), icicle_index);
		pFallPoint_[icicle_index] = new FallPoint(GetGame(), icicle_index);
		
		pIcicles_[icicle_index]->SetPosition(Vec2(SNOW_POS_X + index_x * 113, 200 - SNOW_POS_Y + index_y * 75));
		pFallPoint_[icicle_index]->SetPosition(Vec2(SNOW_POS_X + index_x * 113, SNOW_POS_Y + index_y * 75));
		timer_ = 0;
	}

	for (int i{}; i < ICICLE_MAX; ++i)
	{
		int snoy = snows_[i]->GetPosition().y_;
		if (pIcicles_[i] && pIcicles_[i]->GetPosition().y_ > snoy)
		{
			pIcicles_[i]->SetState(Dead);
			pFallPoint_[i]->SetState(Dead);
		}
			
	}
}