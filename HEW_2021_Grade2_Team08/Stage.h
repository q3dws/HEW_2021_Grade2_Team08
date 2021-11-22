#ifndef STAGE_H_
#define STAGE_H_

#include "Actor.h"
#include "Game.h"
#include "Snow.h"

#define STAGE_X  6
#define STAGE_Y  3


class Stage : public Actor
{
public:
	Stage(class Game* game);
	void UpdateActor(float deltatime) override;
	void SetSnow(int index, int timer = 0) { snows_[index]->SetTimer(timer); }
	
private:
	Snow* snows_[SNOW_MAX];
	
};

#endif // !STAGE_H_
