#include "CharaselectScene.h"
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
#include "ModeselectScene.h"
#include "sound.h"

/////////////////////////////////////////////////////////
//  CharaselctScene                                         //
/////////////////////////////////////////////////////////
CharaselctScene::CharaselctScene(Game* game, int mode)
{
	mode_ = mode;
	Initialize(game);
	temp = new Actor(game);
	temp->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(temp, 10);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int > bgtexs = {
		//game->GetTexture(L"Data/Image/Scene/chara_select/chara_select_BG3.png"),
		game->GetTexture(L"Data/Image/chara_select_BG1.png")
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
	logo->SetPosition(Vec2(140, 25));
	logotex = new SpriteComponent(logo, 24);
	logotex->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select/chara_selectUI2.png"), Vec2(300, 300), Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

	//exit
	exit_ = new Actor(game);
	exit_->SetPosition(Vec2(WINDOW_WIDTH + 12 - exitsize_.x_ / 2, WINDOW_HEIGHT + 53 - (exitsize_.y_ / 2)));
	exit_asc_ = new SpriteComponent(exit_, 21);
	exit_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_exit_dark.png"), exitsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

	p1select = new Actor(game);
	p1select->SetPosition(Vec2(-140, -250));
	p1selecttex = new SpriteComponent(p1select, 24);
	p1selecttex->SetTexture(game->GetTexture(L"Data/Image/UI/keyboardNumber/keyboard1_300%.png"), Vec2(80, 80), Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

	p2select = new Actor(game);
	p2select->SetPosition(Vec2(-140,- 250));
	p2selecttex = new SpriteComponent(p2select, 23);
	p2selecttex->SetTexture(game->GetTexture(L"Data/Image/UI/keyboardNumber/keyboard2_300%.png"), Vec2(80, 80), Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

}
CharaselctScene::~CharaselctScene()
{
	temp->SetState(Actor::State::Dead);
	temp1->SetState(Actor::State::Dead);
	temp2->SetState(Actor::State::Dead);
	temp3->SetState(Actor::State::Dead);
	temp4->SetState(Actor::State::Dead);
	tempUI1->SetState(Actor::State::Dead);
	logo->SetState(Actor::State::Dead);
	exit_->SetState(Actor::State::Dead);
	p1select->SetState(Actor::State::Dead);
	p2select->SetState(Actor::State::Dead);

	StopSound(BGM_);
}
void CharaselctScene::Initialize(Game* game)
{
	iconsize_ = (Vec2(600, 600));

	charapos = Vec2(100, WINDOW_HEIGHT / 2 + 20);
	bar = 150;

	charaUIsize = Vec2(400, 400);
	charaUIpos = Vec2(WINDOW_WIDTH + 20 - charaUIsize.x_ / 2, charapos.y_);
	exitsize_ = Vec2(150, 150);
	selectchara1_num = -1;
	selectchara2_num = -1;

	
	BGM_ = LoadSound(L"Data/BGM/charaselect.wav");
	PlaySound(BGM_, -1);

	SE_[0] = LoadSound(L"Data/SE/Scene/push.wav");
	SE_[1] = LoadSound(L"Data/SE/Scene/cursormove.wav");
	SE_[2] = LoadSound(L"Data/SE/Scene/exir.wav");
		
}

void CharaselctScene::HandleInput(Game* game)
{
	if (GetKeyboardRelease(DIK_SPACE) || (GetKeyboardTrigger(DIK_RCONTROL)))
	{
		if (cursor == static_cast<int>(celectCHARA::EXIT))
		{
			PlaySound(SE_[static_cast<int>(SE::EXIT)], 0);
			game->GetGSM()->ChangeState(new ModeselectScene(game));
		}
		else
		{
			PlaySound(SE_[static_cast<int>(SE::PUSH)], 0);
			if (selectchara1_num != -1 && selectchara2_num == -1)
			{
				//プレイヤーキャラ2決定
				p2select->SetPosition(Vec2(charapos.x_ + bar * cursor, charapos.y_));
				selectchara2_num = cursor;
			}

			if (selectchara1_num == -1)
			{
				//プレイヤーキャラ1決定
				p1select->SetPosition(Vec2(charapos.x_ + bar * cursor, charapos.y_));
				selectchara1_num = cursor;
			}

			if(mode_ == static_cast<int>(ModeselectScene::celectMODE::ARCADE))
			game->GetGSM()->ChangeState(new BattleScene(game,mode_, selectchara1_num, selectchara2_num, 0));

			if (mode_ == static_cast<int>(ModeselectScene::celectMODE::VERSUS)
				&& selectchara2_num != -1)
				game->GetGSM()->ChangeState(new BattleScene(game, mode_, selectchara1_num, selectchara2_num, 0));
		}
		
	}
	if (GetKeyboardTrigger(DIK_D) || GetKeyboardTrigger(DIK_RIGHT))
	{
		PlaySound(SE_[static_cast<int>(SE::CURSORMOVE)], 0);
		++cursor;
		if (cursor >= 3)
		{
			cursor = 3;
		}
	}
	if (GetKeyboardTrigger(DIK_A) || GetKeyboardTrigger(DIK_LEFT))
	{
		PlaySound(SE_[static_cast<int>(SE::CURSORMOVE)], 0);
		--cursor;
		if (cursor < 0)
		{
			cursor = 0;
		}
	}

	if (GetKeyboardTrigger(DIK_S) || GetKeyboardTrigger(DIK_DOWN))
	{
		if (cursor != static_cast<int>(celectCHARA::EXIT))
		{
			PlaySound(SE_[static_cast<int>(SE::CURSORMOVE)], 0);
			cursorbuffer_ = cursor;
		}
			

		cursor = static_cast<int>(celectCHARA::EXIT);
	}

	if ((GetKeyboardTrigger(DIK_W) || GetKeyboardTrigger(DIK_UP)) && cursor == static_cast<int>(celectCHARA::EXIT))
	{
		PlaySound(SE_[static_cast<int>(SE::CURSORMOVE)], 0);
		cursor = cursorbuffer_;
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
		exit_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_exit_dark.png"), exitsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		break;
	case 1:
		//キャラ2選択
		chara1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIgirl2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara2->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UImecha1.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara3->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIRED2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara4->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIwitch2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		charaUI1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_skill3.png"), charaUIsize, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		exit_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_exit_dark.png"), exitsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		break;
	case 2:
		//キャラ3選択
		chara1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIgirl2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara2->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UImecha2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara3->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIRED1.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara4->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIwitch2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		charaUI1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_skill1.png"), charaUIsize, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		exit_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_exit_dark.png"), exitsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		break;
	case 3:
		//キャラ4選択
		chara1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIgirl2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara2->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UImecha2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara3->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIRED2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara4->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIwitch1.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		charaUI1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_skill2.png"), charaUIsize, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		exit_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_exit_dark.png"), exitsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		break;

	case static_cast<int>(celectCHARA::EXIT):
		//キャラ4選択
		chara1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIgirl2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara2->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UImecha2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara3->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIRED2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		chara4->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIwitch2.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		charaUI1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_skill2.png"), charaUIsize, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		exit_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_exit.png"), exitsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		break;
	default:
		break;
	}
}

