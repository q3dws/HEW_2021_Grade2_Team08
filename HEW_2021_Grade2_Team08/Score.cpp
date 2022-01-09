#include "score.h"
#include "AnimSpriteComponent.h"
#include "BGSpriteComponent.h"
#include "SpriteComponent.h"
#include "input.h"
#include "Texture.h"

#define TEXTURE_WIDTH				(35)
#define TEXTURE_HEIGHT				(35)	



PlayerScore::PlayerScore(Game* game, Vec2(pos))
	:Actor(game)
{
	g_score = 0;	// スコアの初期化
	g_w = TEXTURE_WIDTH;
	g_h = TEXTURE_HEIGHT;
	a = 0;


	int number = g_score;

	////スコアボード表示
	//auto temp1 = new Actor(game);
	//temp1->SetPosition(Vec2(WINDOW_WIDTH / 2 - 70 - 44, 50));
	//BGSpriteComponent* scorebg1 = new BGSpriteComponent(temp1, 45);
	//scorebg1->SetScreenSize(Vec2(140, 140));
	//std::vector<int > bgtexs1 = {
	//	game->GetTexture(L"Data/Image/UI/scorbord/scorbord_bule1.png")
	//};
	//scorebg1->SetBGTextures(bgtexs1);

	////スコアボード表示
	//auto temp2 = new Actor(game);
	//temp2->SetPosition(Vec2(WINDOW_WIDTH / 2 + 70 + 42, 50));
	//BGSpriteComponent* scorebg2 = new BGSpriteComponent(temp2, 45);
	//scorebg2->SetScreenSize(Vec2(140, 140));
	//std::vector<int > bgtexs2 = {
	//	game->GetTexture(L"Data/Image/UI/scorbord/scorbord_red1.png")
	//};
	//scorebg2->SetBGTextures(bgtexs2);

	////タイマーが入る所表示
	//auto temp3 = new Actor(game);
	//temp3->SetPosition(Vec2(WINDOW_WIDTH / 2, 50));
	//auto temp3_asc = new SpriteComponent(temp3, 150);
	//temp3_asc->SetTexture(LoadTexture(L"Data/Image/UI/scorbord/time.png")
	//	, Vec2(64 * 2, 64 * 2), Vec2(0, 0), Vec2(1, 1));
	//

	SetPosition(pos);
}

void PlayerScore::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);

	delete score;
	this->RemoveComponent(score);
	score = new SpriteComponent(this, 50);
	score->SetTexture(GetGame()->GetTexture(L"Data/Image/UI/scorbord/scornumber_32x32.png"), Vec2(g_w, g_h), Vec2(a, 1.0f), Vec2(0.1f, 1));
}

void PlayerScore::AddScore(int number)
{
	a = number * 0.1f;
	if (number < 1.0f)
	{
		a = 0;
	}
}


