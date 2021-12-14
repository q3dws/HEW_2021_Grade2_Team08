#pragma once
#include "Game.h"
#include "Actor.h"

#define FALLPOINT_SIZE	128
#define FALLPOINT_MAX	18

class FallPoint :public Actor
{
public:
	FallPoint(Game* game, int ptexno);
	void UpdateActor(float deltatime) override;

private:
	int texno_;

};

