#pragma once
#include "Game.h"
#include "Actor.h"
#include "StageBg.h"

class ThirdStageBg : StageBg
{
public:
	ThirdStageBg(Game* game);
    ~ThirdStageBg();
	void UpdateActor(float deltatime) override {};

private:
    class Actor* bgactor_;
};

