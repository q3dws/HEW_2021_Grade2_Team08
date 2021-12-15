#include "ScoreManager.h"
#include "Game.h"
#include "Texture.h"
#include "SpriteComponent.h"

ScoreManager::ScoreManager(Game* game)
	:Actor(game)
	,SCORE_MAX(99)
{
	score1 = new PlayerScore(game, Vec2(410, 50));
	score2 = new PlayerScore(game, Vec2(380, 50));
	enemyscore1 = new PlayerScore(game, Vec2(620, 50));
	enemyscore2 = new PlayerScore(game, Vec2(590, 50));
	number = 0;
	enemynumber = 0;
}

void ScoreManager::UpdateActor(float delttime)
{

}

void ScoreManager::AddScore(int add)
{

	number += add;

	if (number > SCORE_MAX)
	{
		number = SCORE_MAX;
	}

	score1->AddScore(number);

	int a;

	a = number / 10;
	score2->AddScore(a);

	
}

void ScoreManager::EnemyAddScore(int add)
{
	enemynumber += add;

	if (enemynumber > SCORE_MAX)
	{
		enemynumber = SCORE_MAX;
	}

	enemyscore1->AddScore(enemynumber);

	int a;

	a = enemynumber / 10;
	enemyscore2->AddScore(a);
}
