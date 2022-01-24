#include "Charaselect.h"
#include "GameScene.h"
#include "Math.h"
#include "Actor.h"
#include "SpriteComponent.h"
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
#include "Stage.h"
#include "Score.h"
#include "ScoreManager.h"
/////////////////////////////////////////////////////////
//  CharaselctScene                                         //
/////////////////////////////////////////////////////////
CharaselctScene::CharaselctScene(Game* game)
{
	Initialize(game);
	temp = new Actor(game);
	temp->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(temp, 10);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int > bgtexs = {
		game->GetTexture(L"Data/Image/chara_select_BG1.png"),
		//game->GetTexture(L"Data/Image/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	//bg->SetScrollSpeed(-100.0f);

	//キャラ1
	temp1 = new Actor(game);
	temp1->SetPosition(Vec2(charapos.x_, charapos.y_));
	chara1 = new SpriteComponent(temp1, 21);

	chara1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIgirl1.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

	//UI表示
	tempUI1 = new Actor(game);
	tempUI1->SetPosition(charaUIpos);
	charaUI1 = new SpriteComponent(tempUI1, 21);
	charaUI1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_skill1.png"), charaUIsize, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

	//キャラ2
	temp2 = new Actor(game);
	temp2->SetPosition(Vec2(charapos.x_ + bar, charapos.y_));
	chara2 = new SpriteComponent(temp2, 21);
	chara2->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UImecha1.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

	//キャラ3
	temp3 = new Actor(game);
	temp3->SetPosition(Vec2(charapos.x_ + bar * 2, charapos.y_));
	chara3 = new SpriteComponent(temp3, 21);
	chara3->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIRED1.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));


	//キャラ4
	temp4 = new Actor(game);
	temp4->SetPosition(Vec2(charapos.x_ + bar * 3, charapos.y_));
	chara4 = new SpriteComponent(temp4, 21);
	chara4->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIwitch1.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
	
	
	logo = new Actor(game);
	logo->SetPosition(Vec2(WINDOW_WIDTH / 2, 30));
	logotex = new SpriteComponent(logo, 24);
	logotex->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_selectUI.png"), Vec2(450, 450), Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
	
}
CharaselctScene::~CharaselctScene()
{
	delete temp;
	delete temp1;
	delete temp2;
	delete temp3;
	delete temp4;
	delete tempUI1;
	delete logo;
}
void CharaselctScene::Initialize(Game* game)
{
	iconsize_ = (Vec2(600, 600));

	charapos = Vec2(100, WINDOW_HEIGHT / 2 + 20);
	bar = 150;

	charaUIsize = Vec2(400, 400);
	charaUIpos = Vec2(WINDOW_WIDTH - charaUIsize.x_ / 2, WINDOW_HEIGHT / 2 + 20);

}

void CharaselctScene::HandleInput(Game* game)
{
	if (GetKeyboardRelease(DIK_SPACE))
	{
		game->GetGSM()->ChangeState(new BattleScene(game));
	}
	if (GetKeyboardTrigger(DIK_D))
	{
		++cursor;
		if (cursor >= 3)
		{
			cursor = 3;
		}
	}
	if (GetKeyboardTrigger(DIK_A))
	{
		--cursor;
		if (cursor < 0)
		{
			cursor = 0;
		}
	}
}

void CharaselctScene::Update(Game* game)
{
	switch (cursor)
	{
	case 0:
		//キャラ1選択
		chara1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIgirl1.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara2->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UImecha2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara3->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIRED2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara4->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIwitch2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		charaUI1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_skill4.png"), charaUIsize, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		break;
	case 1:
		//キャラ2選択
		chara1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIgirl2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara2->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UImecha1.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara3->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIRED2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara4->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIwitch2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		charaUI1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_skill3.png"), charaUIsize, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		break;
	case 2:
		//キャラ3選択
		chara1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIgirl2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara2->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UImecha2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara3->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIRED1.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara4->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIwitch2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		charaUI1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_skill1.png"), charaUIsize, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		break;
	case 3:
		//キャラ4選択
		chara1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIgirl2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara2->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UImecha2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara3->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIRED2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara4->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIwitch1.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		charaUI1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_skill2.png"), charaUIsize, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		break;
	default:
		break;
	}
}

