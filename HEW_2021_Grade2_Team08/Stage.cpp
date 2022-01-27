#include "Stage.h"
#include "SpriteComponent.h"
#include "Snow.h"

Stage::Stage(Game* game)
	:Actor(game), snows_()
{
	for (int i = 0; i < STAGE_Y; ++i)
		for (int j = 0; j < STAGE_X; ++j)
		{
			int tmp = (i * STAGE_X) + j;
			snows_[tmp] = new Snow(game, (i * STAGE_X) + j, Vec2(SNOW_POS_X + j * 113, SNOW_POS_Y + i * 75));
		}
}

Stage::~Stage()
{
}

void Stage::UpdateActor(float deltatime)
{
}
