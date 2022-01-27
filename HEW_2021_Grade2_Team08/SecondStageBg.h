#pragma once
#include "Game.h"
#include "Actor.h"
#include "StageBg.h"

class SecondStageBg : public StageBg
{
public:
	SecondStageBg(Game* game);
	void UpdateActor(float deltatime) override {};

private:

};

