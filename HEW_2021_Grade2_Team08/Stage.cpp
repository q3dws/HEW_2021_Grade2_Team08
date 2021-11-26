#include "Stage.h"
#include "SpriteComponent.h"

Stage::Stage(Game* game)
	:Actor(game), snows_()
{
	for (int i = 0; i < STAGE_Y; ++i)
		for (int j = 0; j < STAGE_X; ++j)
		{
			int tmp = (i * STAGE_X) + j;

			snows_[tmp] = new Snow(game);
			snows_[tmp]->SetPosition(Vec2(SNOW_POS_X + j * 104, SNOW_POS_Y + i * 86.5));
			snows_[tmp]->index_ = (i * STAGE_X) + j;

		}
}

void Stage::UpdateActor(float deltatime)
{


}