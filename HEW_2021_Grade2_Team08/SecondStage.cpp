#include "SecondStage.h"

SecondStage::SecondStage(Game* game)
	:Stage(game)
{
	ssb = new SecondStageBg(game);
}

SecondStage::~SecondStage()
{
    ssb->SetState(Dead);
	for (int i = 0; i < SNOW_MAX; ++i)
	{
		snows_[i]->SetState(Dead);
		snows_[i] = nullptr;
	}
}

void SecondStage::UpdateActor(float deltatime)
{
	timer_++;

	if (timer_ > ICICLE_TIME)
	{
		auto index_x = rand() % 6;
		auto index_y = rand() % 3;
		icicle_index = index_y * STAGE_X + index_x;

		auto icicle = new Icicle(GetGame(), snows_[icicle_index]->GetPosition(), index_x, index_y, icicle_index);
		timer_ = 0;
	}

}
