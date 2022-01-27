#pragma once
#include "Game.h"
#include "Actor.h"
#include "AnimSpriteComponent.h"

#define ANIM_FRAME	12

class IcicleOut : public Actor
{
public:
	IcicleOut(Game* game, const Vec2& pos);
	void UpdateActor(float deltatime) override;
private:
	int texno_;
	int timer_ = 0;
	AnimSpriteComponent* IcicleOut_Sprite_;
};

