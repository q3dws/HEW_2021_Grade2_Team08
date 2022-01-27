#pragma once
#include "Stage.h"
#include "StageBg.h"

class FirstStage : public Stage
{
public:
	FirstStage(Game* game);
	~FirstStage();
	void UpdateActor(float deltatime) override;
	void SetSnow(int index, int timer = 0) override { snows_[index]->SetTimer(timer); }
	bool GetUseSnow(int index)override { return snows_[index]->GetIsSnow(); }

private:
	class StageBg* sbg;

};

