#include "GameScene.h"
#include "Math.h"
#include "Actor.h"
#include "BGSpriteComponent.h"
#include "main.h"
#include "Game.h"
#include "Texture.h"
#include "sprite.h"
#include "input.h"
#include "AnimationTestObj.h"
#include "TestBullet.h"
#include "Player.h"
#include "Snow.h"
#include "FirstStage.h"
#include "SecondStage.h"
#include "ThirdStage.h"
#include "Score.h"
#include "Icicle.h"

/////////////////////////////////////////////////////////
//  StartScene                                         //
/////////////////////////////////////////////////////////
StartScene::StartScene(Game* game)
{
	Initialize(game);
	temp = new Actor(game);
	temp->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(temp, 10);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int > bgtexs = {
		game->GetTexture(L"Data/Image/Farback01.png"),
		game->GetTexture(L"Data/Image/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-100.0f);

	bg = new BGSpriteComponent(temp, 20);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	bgtexs = {
		game->GetTexture(L"Data/Image/titledoon.png")
	};
	bg->SetBGTextures(bgtexs);
}
StartScene::~StartScene()
{
	delete temp;
}
void StartScene::Initialize(Game* game)
{
	
}

void StartScene::HandleInput(Game* game)
{
	if (GetKeyboardRelease(DIK_SPACE))
	{
		game->GetGSM()->ChangeState(new BattleScene(game));
	}
}

void StartScene::Update(Game* game)
{
}

/////////////////////////////////////////////////////////
//  BattleScene                                        //
/////////////////////////////////////////////////////////
BattleScene::BattleScene(Game* game)
{
	Initialize(game);
	
	p_score = new Score(game);
	p_score2 = new Score2(game);
	stg = new FirstStage(game);
	player = new Player(game, stg);

}

BattleScene::~BattleScene()
{
	delete p_score;
	delete p_score2;
	delete stg; 
	delete player;
}

void BattleScene::Initialize(Game* game)
{	
}

void BattleScene::HandleInput(Game* game)
{
	if (GetKeyboardRelease(DIK_SPACE))
	{
		game->GetGSM()->ChangeState(new SecondBattleScene(game));
	}
}

void BattleScene::Update(Game* game)
{
}

/////////////////////////////////////////////////////////////
// Stage2												   //
/////////////////////////////////////////////////////////////
SecondBattleScene::SecondBattleScene(Game* game)
{
	Initialize(game);

	p_score = new Score(game);
	p_score2 = new Score2(game);
	stg2 = new SecondStage(game);
	player = new Player(game, stg2);

}

SecondBattleScene::~SecondBattleScene()
{
	delete p_score;
	delete p_score2;
	delete stg2;
	delete player;
}

void SecondBattleScene::Initialize(Game* game)
{
}

void SecondBattleScene::HandleInput(Game* game)
{
	if (GetKeyboardRelease(DIK_SPACE))
	{
		game->GetGSM()->ChangeState(new ThirdBattleScene(game));
	}
}

void SecondBattleScene::Update(Game* game)
{
}

/////////////////////////////////////////////////////////////
// Stage3												   //
/////////////////////////////////////////////////////////////
ThirdBattleScene::ThirdBattleScene(Game* game)
{
	Initialize(game);

	p_score = new Score(game);
	p_score2 = new Score2(game);
	stg3 = new ThirdStage(game);
	player = new Player(game, stg3);
}

ThirdBattleScene::~ThirdBattleScene()
{
	delete p_score;
	delete p_score2;
	delete stg3;
	delete player;
}

void ThirdBattleScene::Initialize(Game* game)
{
}

void ThirdBattleScene::HandleInput(Game* game)
{
	if (GetKeyboardRelease(DIK_SPACE))
	{
		game->GetGSM()->ChangeState(new BattleScene(game));
	}
}

void ThirdBattleScene::Update(Game* game)
{
}
