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

		//auto icicle = new Icicle(GetGame(), snows_[icicle_index]->GetPosition(), index_x, index_y, icicle_index);
		timer_ = 0;
	}
}