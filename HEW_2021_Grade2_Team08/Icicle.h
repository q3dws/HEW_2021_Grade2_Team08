#pragma once
#include "Game.h"
#include "Actor.h"
#include "Snow.h"
#include "FallPoint.h"
#include "IcicleOut.h"

#define ICICLE_SIZE		64
#define ICICLE_ANIMSIZE 128
#define ICICLE_MAX		18
#define ICICLE_TIME		90


class Icicle: public Actor
{
public:
	Icicle(Game* game, const Vec2& destination, int index_x, int index_y, int icicle_index);
	~Icicle() override;
	void UpdateActor(float deltatime) override;

private:
	int texno_;
	int texno2_;
	Vec2 destination_;
	float move_ = 6.0f;
	//bool Use_;
	FallPoint* fp_;
	IcicleOut* ico_;
	SpriteComponent* Icicle_Sprite_;
};

