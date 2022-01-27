#include "ThirdStage.h"
#include "Stage.h"
#include "BlackHole.h"
#include "BlackHoleIn.h"
#include "BlackHoleOut.h"
#include "Icicle.h"
#include <random>



ThirdStage::ThirdStage(Game* game)
	:Stage(game)
{
	tsb = new ThirdStageBg(game);
}

ThirdStage::~ThirdStage()
{
	for (int i{}; i < WARNING_MAX; ++i)
		if(pWarning[i] )
			delete pWarning[i];
	if(pBHI)
		delete pBHI;
	delete pBH;

	for (int i = 0; i < SNOW_MAX; ++i)
	{
		snows_[i]->SetState(Dead);
		snows_[i] = nullptr;
	}
	
}

void ThirdStage::UpdateActor(float deltatime)
{
	timer_++;
	icicletimer_++;

	std::random_device rnd;
	std::mt19937 mt(rnd());

	if (icicletimer_ > ICICLE_TIME)
	{
		auto index_x = rand() % 6;
		auto index_y = rand() % 3;
		icicle_index = index_y * STAGE_X + index_x;

		auto icicle = new Icicle(GetGame(), snows_[icicle_index]->GetPosition(), index_x, index_y, icicle_index);
		icicletimer_ = 0;
	}

	if (timer_ == usetimer_ - KEIKOKU_TIME)
	{
		for (int i = 0; i < WARNING_MAX; ++i)
		{
			pWarning[i] = new WarningPoint(GetGame(), snows_[i]->GetPosition());
		}		
	}

	if (timer_ == usetimer_ - 60)
	{
		pBHI = new BlackHoleIn(GetGame());
	}

	if (timer_ == usetimer_)
	{
		for (int num = 0; num < WARNING_MAX; ++num)
		{
			pWarning[num]->SetState(Dead);
			pWarning[num] = nullptr;
		}
		
		pBHI->SetState(Dead);
		pBHI = nullptr;
		usetimer_ = BHTIMER + mt() % 100;
		
		pBH = new BlackHole(GetGame(), this);
		timer_ = 0;
	}

}

void ThirdStage::AllSnowDelete()
{
	for (int i = 0; i < SNOW_MAX; i++)
	{
		snows_[i]->DeleteSnow();
	}
}
