#pragma once
#include "Game.h"
#include "Actor.h"
#include "AnimSpriteComponent.h"
#include "BlackHole.h"

class BlackHoleOut : public Actor
{
public:
	BlackHoleOut(Game* game);
	void UpdateActor(float deltatime) override;

private:
	int texno_;
	int timer_;
	AnimSpriteComponent* BHOut_Sprite_;
};

