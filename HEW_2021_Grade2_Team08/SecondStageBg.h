#pragma once
#include "Game.h"
#include "Actor.h"
#include "StageBg.h"

class SecondStageBg : public StageBg
{
public:
	SecondStageBg(Game* game);
    ~SecondStageBg();
	void UpdateActor(float deltatime) override {};

private:
    class Actor* bgactor_;
};

