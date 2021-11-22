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
	auto temp = new Actor(game);
	temp->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	BGSpriteComponent* bg = new BGSpriteComponent(temp, 10);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int > bgtexs = {
		game->GetTexture(L"Data/Image/BackGround_2.png")
	};
	bg->SetBGTextures(bgtexs);

	auto bgsta = new Actor(game);
	bgsta->SetPosition(Vec2(WINDOW_WIDTH * 0.5, STAGE_HEIGHT));
	BGSpriteComponent* sbg = new BGSpriteComponent(temp, 11);
	sbg = new BGSpriteComponent(bgsta, 15);
	sbg->SetScreenSize(Vec2(STAGESCREEN_X, STAGESCREEN_Y));
	std::vector<int> sbgtexs = {
		game->GetTexture(L"Data/Image/Stage_normal_edited.png")
	};
	
	sbg->SetBGTextures(sbgtexs);

	obj = new AnimationTestObj(game);
	obj->SetPosition(Vec2(320, WINDOW_HEIGHT - 280));
	
	stg = new Stage(game);
}

BattleScene::~BattleScene()
{
}

void BattleScene::Initialize(Game* game)
{
}

void BattleScene::HandleInput(Game* game)
{
	if (GetKeyboardRelease(DIK_RETURN))
	{
		auto bullet = new TestBullet(game);
		bullet->SetPosition(obj->GetPosition());
	}
	if (GetKeyboardRelease(DIK_W))
	{
		obj->SetPosition(Vec2(obj->GetPosition().x_, obj->GetPosition().y_ - 100));
	}
	if (GetKeyboardRelease(DIK_S))
	{
		obj->SetPosition(Vec2(obj->GetPosition().x_, obj->GetPosition().y_ + 100));
	}
	if (GetKeyboardRelease(DIK_A))
	{
		obj->SetPosition(Vec2(obj->GetPosition().x_ - 100, obj->GetPosition().y_));
	}
	if (GetKeyboardRelease(DIK_D))
	{
		obj->SetPosition(Vec2(obj->GetPosition().x_ + 100, obj->GetPosition().y_));
	}
	if (GetKeyboardRelease(DIK_E))
	{
		stg->SetSnow(0);
	}

	
}

void BattleScene::Update(Game* game)
{
	 
}