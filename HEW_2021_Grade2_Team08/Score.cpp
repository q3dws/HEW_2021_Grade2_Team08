#include "score.h"
#include "AnimSpriteComponent.h"
#include "BGSpriteComponent.h"
#include "SpriteComponent.h"
#include "input.h"


#define TEXTURE_WIDTH				(50)
#define TEXTURE_HEIGHT				(50)	



PlayerScore::PlayerScore(Game* game, Vec2(pos))
	:Actor(game)
{
	g_score = 0;	
	g_w = TEXTURE_WIDTH;
	g_h = TEXTURE_HEIGHT;
	a = 0;


	int number = g_score;

	
	auto temp1 = new Actor(game);
	temp1->SetPosition(Vec2(400, 50));
	BGSpriteComponent* scorebg1 = new BGSpriteComponent(temp1, 45);
	scorebg1->SetScreenSize(Vec2(120, 120));
	std::vector<int > bgtexs1 = {
		game->GetTexture(L"Data/Image/ScorebordPlayer.png")
	};
	scorebg1->SetBGTextures(bgtexs1);

	
	auto temp2 = new Actor(game);
	temp2->SetPosition(Vec2(600, 50));
	BGSpriteComponent* scorebg2 = new BGSpriteComponent(temp2, 45);
	scorebg2->SetScreenSize(Vec2(120, 120));
	std::vector<int > bgtexs2 = {
		game->GetTexture(L"Data/Image/ScorebordEnemy.png")
	};
	scorebg2->SetBGTextures(bgtexs2);

	SetPosition(pos);
}

void PlayerScore::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);

	delete score;
	this->RemoveComponent(score);
	score = new SpriteComponent(this, 50);
	score->SetTexture(GetGame()->GetTexture(L"Data/Image/number.png"), Vec2(g_w, g_h), Vec2(a, 1.0f), Vec2(0.1f, 1));
}

void PlayerScore::AddScore(int number)
{
	a = number * 0.1f;
	if (number < 1.0f)
	{
		a = 0;
	}
}


