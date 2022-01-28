#pragma once
#include "Game.h"
#include "Actor.h"

#define STAGE_HEIGHT 337

class StageBg : public Actor
{
public:
	StageBg(Game* game);
    ~StageBg();
	void UpdateActor(float deltatime) override {};

private:
    class Actor* stgactor_;
    class Actor* bgactor_;

};

