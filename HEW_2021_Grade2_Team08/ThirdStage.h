#pragma once
#include "Stage.h"
#include "BlackHole.h"
#include "WarningPoint.h"
#include "ThirdStageBg.h"
#include <vector>
#define BHTIMER			600
#define WARNING_MAX		18
#define KEIKOKU_TIME	120

class ThirdStage : public Stage
{
public:
	ThirdStage(Game* game);
	~ThirdStage();
	void UpdateActor(float deltatime) override;
	void SetSnow(int index, int timer = 0) override { snows_[index]->SetTimer(timer); }
	bool GetUseSnow(int index)override { return snows_[index]->GetIsSnow(); }
	void AllSnowDelete();

private:
	int timer_ = 0;
	int icicletimer_ = 0;
	int usetimer_ = 600;
	int icicle_index = -1;
	class WarningPoint* pWarning[WARNING_MAX];
	class BlackHoleIn* pBHI;
	class BlackHole* pBH;
	class ThirdStageBg* tsb;
    std::vector<int> icicle_indexs_;
};

