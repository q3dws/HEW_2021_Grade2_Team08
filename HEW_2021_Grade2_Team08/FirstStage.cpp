#include "FirstStage.h"
#include "Snow.h"

FirstStage::FirstStage(Game* game)
	:Stage(game)
{
	sbg = new StageBg(game);
}

FirstStage::~FirstStage()
{
    delete sbg;
	for (int i = 0; i < SNOW_MAX; ++i)
	{
		snows_[i]->SetState(Dead);
		snows_[i] = nullptr;
	}
}

void FirstStage::UpdateActor(float deltatime)
{
	for (int i = 0; i < STAGE_Y; ++i)
		for (int j = 0; j < STAGE_X; ++j)
		{
			int tmp= (i * STAGE_X) + j;
			if (snows_[tmp]->index_ < 0)
				snows_[tmp] = new Snow(GetGame(), tmp, Vec2(SNOW_POS_X + j * 113, SNOW_POS_Y + i * 75));

		}
}
