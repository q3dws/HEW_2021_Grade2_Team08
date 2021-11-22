#include "Stage.h"
#include "SpriteComponent.h"

Stage::Stage(Game* game)
:Actor(game),snows_()
{
	for (int i = 0; i < STAGE_Y; ++i)
		for (int j = 0; j < STAGE_X; ++j)
		{
				snows_[(i * i * STAGE_X) + j] = new Snow(game);
				snows_[(i * i * STAGE_X) + j]->SetPosition(Vec2(SNOW_POS_X + j * 120.0f, SNOW_POS_Y + i * 120.0f));
				snows_[(i * i * STAGE_X) + j]->index_ = (i * STAGE_X) + j;

		}
}

void Stage::UpdateActor(float deltatime)
{
	

}

