#include "Stage.h"
#include "SpriteComponent.h"

Stage::Stage(Game* game)
	:Actor(game), snows_()
{
	//Snow
	for (int i = 0; i < STAGE_Y; ++i)
		for (int j = 0; j < STAGE_X; ++j)
		{
			int tmp = (i * STAGE_X) + j;

			snows_[tmp] = new Snow(game);
			snows_[tmp]->SetPosition(Vec2(SNOW_POS_X + j * 113, SNOW_POS_Y + i * 75));
			snows_[tmp]->index_ = (i * STAGE_X) + j;

		}

	//Icicle
	/*pIcicles_ = new Icicle(game);
	pIcicles_->SetPosition(Vec2(pIcicles_->pos_x_, pIcicles_->pos_y_));*/



}

void Stage::UpdateActor(float deltatime)
{
	/*timer_++;

	if (timer_ < ICICLE_TIME)
	{
		pIcicles_->pos_y_ += pIcicles_->move_;
		pIcicles_->SetPosition(Vec2(pIcicles_->pos_x_, pIcicles_->pos_y_));
	}

	else
	{
		pIcicles_->pos_x_ = 200.f;
		pIcicles_->pos_y_ = 100.f;
		timer_ = 0;
	
	}*/

	
	

}