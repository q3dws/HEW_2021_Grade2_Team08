#pragma once
#include "Game.h"
#include "Actor.h"
#include "Snow.h"

#define ICICLE_SIZE		64
#define ICICLE_MAX		18
#define ICICLE_TIME		140


class Icicle: public Actor
{
public:
	Icicle(Game* game, int icicle_index);
	void UpdateActor(float deltatime) override;

private:
	int texno_;
	float move_ = 4.0f;
	//bool Use_;
	Actor* Icicle_Actor_;
	SpriteComponent* Icicle_Sprite_;
};

