#include "ThirdStage.h"
#include "Stage.h"
#include "BlackHole.h"
#include "BlackHoleIn.h"
#include "BlackHoleOut.h"
#include "Icicle.h"
#include <random>
#include <vector>

#define ICICLE_TIME3 40
ThirdStage::ThirdStage(Game* game)
	:Stage(game)
{
    icicle_indexs_.emplace_back(0);
    icicle_indexs_.emplace_back(1);
    icicle_indexs_.emplace_back(2);
	tsb = new ThirdStageBg(game);
}

ThirdStage::~ThirdStage()
{
    icicle_indexs_.clear();
    delete tsb;
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
        std::random_device seed_gen;
        std::mt19937 engine(seed_gen());
        std::shuffle(icicle_indexs_.begin(), icicle_indexs_.end(), engine);
		auto index_x = icicle_indexs_[0];
		auto index_y = icicle_indexs_[2];
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
	snows_[0]->DeleteSnow();
    snows_[1]->DeleteSnow();
    snows_[2]->DeleteSnow();
    snows_[6]->DeleteSnow();
    snows_[7]->DeleteSnow();
    snows_[8]->DeleteSnow();
    snows_[12]->DeleteSnow();
    snows_[13]->DeleteSnow();
    snows_[14]->DeleteSnow();
}
