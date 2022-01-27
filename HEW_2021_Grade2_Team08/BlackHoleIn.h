#pragma once
#include "Game.h"
#include "Actor.h"
#include "AnimSpriteComponent.h"
#include "BlackHole.h"

class BlackHoleIn : public Actor
{
public:
	BlackHoleIn(Game* game);
	void UpdateActor(float deltatime) override;

private:
	int texno_;
	AnimSpriteComponent* BHIn_Sprite_;
};

