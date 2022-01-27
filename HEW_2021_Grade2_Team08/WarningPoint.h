#pragma once
#include "Game.h"
#include "Actor.h"
#include "AnimSpriteComponent.h"
#include "FallPoint.h"

class WarningPoint : public Actor
{
public:
	WarningPoint(Game* game, Vec2 pos);
	void UpdateActor(float deltatime) override;
	Vec2 pos_;

private:
	int texno_;
	AnimSpriteComponent* WP_Sprite;
};

