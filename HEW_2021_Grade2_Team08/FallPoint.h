#pragma once
#include "Game.h"
#include "Actor.h"
#include "AnimSpriteComponent.h"
#define FALLPOINT_SIZE	128
#define FALLPOINT_MAX	18

class FallPoint :public Actor
{
public:
	FallPoint(Game* game, const Vec2& pos, int ptexno);
	void UpdateActor(float deltatime) override;

private:
	int texno_;
	AnimSpriteComponent* FallPoint_Sprite_;
};

