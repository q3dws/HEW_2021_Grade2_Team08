#pragma once
#ifndef SCORE_H_
#define SCORE_H_

#include "Actor.h"
#include "Game.h"

class PlayerScore : public Actor
{
public:
	PlayerScore(class Game* game, Vec2(pos));
	void UpdateActor(float deltatime) override;
	void AddScore(int number);
private:
	class SpriteComponent* score;
	//class Actor* temp2;

	int						g_score;
	float					g_w, g_h;


	float a;
};


#endif // SCORE_H_