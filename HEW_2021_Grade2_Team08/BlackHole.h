#pragma once
#ifndef BLACKHOLE_H_
#define BLACKHOLE_H_

#include "Actor.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include "ThirdStage.h"

#define BLACKHOLE_SIZE  200
#define BASEUSETIME		120
#define BH_POS_X		700
#define BH_POS_Y		100

class BlackHole : public Actor
{
public:
	BlackHole(class Game* game , class ThirdStage* psta);
	void UpdateActor(float deltatime) override;
	
private:
	int texno_ = 0;
	int timer_ = 0;
	class SpriteComponent* BH_Sprite;
	class AnimSpriteComponent* BH_AnimSprite;
	class ThirdStage* pStage_;
	class BlackHoleOut* pBHO;
};

#endif // !BLACKHOLE_H_



