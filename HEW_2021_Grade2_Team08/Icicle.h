#pragma once
#include "Game.h"
#include "Actor.h"
#include "Snow.h"

#define ICICLE_SIZE		64
#define ICICLE_MAX		18
#define ICICLE_TIME		50


class Icicle : public Actor
{
public:
	Icicle(Game* game, const Vec2& destination, int index_x, int index_y, int icicle_index);
	~Icicle() override;
	void UpdateActor(float deltatime) override;

private:
	int texno_;
	Vec2 destination_;
	float move_ = 4.0f;
	class FallPoint* fp_;
	SpriteComponent* Icicle_Sprite_;
};