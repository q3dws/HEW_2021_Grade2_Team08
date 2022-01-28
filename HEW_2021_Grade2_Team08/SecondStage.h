#pragma once
#include "Stage.h"
#include "Icicle.h"
#include "IcicleOut.h"
#include "SecondStageBg.h"

class SecondStage : public Stage
{
public:
	SecondStage(Game* game);
	~SecondStage();
	void UpdateActor(float deltatime) override;
	void SetSnow(int index, int timer = 0) override { snows_[index]->SetTimer(timer); }
	bool GetUseSnow(int index)override { return snows_[index]->GetIsSnow(); }

private:
	int timer_ = 0;
	int icicle_index = -1;
	class Stage* pStage;
	class SecondStageBg* ssb;

};

