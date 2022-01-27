#include "VSResultScene.h"
#include "ResultScene.h"
#include "ModeselectScene.h"
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
#include "sound.h"
#include "Fight_Effects.h"
/////////////////////////////////////////////////////////
//  VSResultScene                                         //
/////////////////////////////////////////////////////////
VSResultScene::VSResultScene(Game* game, int p1score, int p2score)
{
	Initialize(game);
	p1score_ = p1score;
	p2score_ = p2score;
	
	temp = new Actor(game);
	temp->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(temp, 10);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int > bgtexs = {
		game->GetTexture(L"Data/Image/Scene/chara_select/chara_select_BG3.png"),
		//game->GetTexture(L"Data/Image/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	//bg->SetScrollSpeed(-100.0f);



	Vec2 scorelogopos = Vec2(WINDOW_WIDTH / 2 - 270, WINDOW_HEIGHT / 2);
	Vec2 winlogopos = Vec2(WINDOW_WIDTH / 2 - 270, WINDOW_HEIGHT / 2 - 150);
	Vec2 winlogosize = Vec2(400, 400);
	Vec2 scorelogosize = Vec2(300, 300);

	waku1_ = new Fight_Effects(game, winlogopos
		, winlogosize, 10
		, static_cast<int>(Fight_Effects::fight_effects_Motion::WAKU_IN));

	if (p1score > p2score)
		youwinlogo_ = new Fight_Effects(game, winlogopos
			, winlogosize, 10
			, static_cast<int>(Fight_Effects::fight_effects_Motion::WIN_ANIM));
	else if(p1score == p2score)
	{
		youwinlogo_ = new Fight_Effects(game, winlogopos
			, winlogosize, 10
			, static_cast<int>(Fight_Effects::fight_effects_Motion::DRAW_IN));
	}
	else
	{
		youwinlogo_ = new Fight_Effects(game, winlogopos
			, winlogosize, 10
			, static_cast<int>(Fight_Effects::fight_effects_Motion::LOSE_ANIM));
	}

	

	scorelogo_ = new Fight_Effects(game, scorelogopos
		, scorelogosize, 10
		, static_cast<int>(Fight_Effects::fight_effects_Motion::SCORE));

	Vec2 difitsize = Vec2(150, 150);
	Vec2 difitpos = Vec2(80, 150);

	digit_ = new PlayerScore(game, Vec2(scorelogopos.x_ - difitpos.x_ + 160, scorelogopos.y_ + 100), difitsize);
	second_digit_ = new PlayerScore(game, Vec2(scorelogopos.x_ - difitpos.x_ + 80, scorelogopos.y_ + 100), difitsize);
	third_digit_ = new PlayerScore(game, Vec2(scorelogopos.x_ - difitpos.x_ + 0, scorelogopos.y_ + 100), difitsize);

	int a = (p1score_ % 10);
	digit_->AddScore(a);

	int b = p1score_ / 10;
	second_digit_->AddScore(b);

	int c = (p1score_ / 100);
	third_digit_->AddScore(c);

	//////////////////
	//p2‘¤‚Ì•\Ž¦
	/////////////////
	Vec2 p2scorelogopos = Vec2(WINDOW_WIDTH / 2 + 270, scorelogopos.y_);
	Vec2 p2winlogopos = Vec2(WINDOW_WIDTH / 2 + 270, winlogopos.y_);

	waku2_ = new Fight_Effects(game, p2winlogopos
		, winlogosize, 10
		, static_cast<int>(Fight_Effects::fight_effects_Motion::WAKU_IN));

	if (p2score > p1score)
		p2youwinlogo_ = new Fight_Effects(game, p2winlogopos
			, winlogosize, 10
			, static_cast<int>(Fight_Effects::fight_effects_Motion::WIN_ANIM));
	else if (p1score == p2score)
	{
		p2youwinlogo_ = new Fight_Effects(game, p2winlogopos
			, winlogosize, 10
			, static_cast<int>(Fight_Effects::fight_effects_Motion::DRAW_IN));
	}
	else
	{
		p2youwinlogo_ = new Fight_Effects(game, p2winlogopos
			, winlogosize, 10
			, static_cast<int>(Fight_Effects::fight_effects_Motion::LOSE_ANIM));
	}

	p2scorelogo_ = new Fight_Effects(game, p2scorelogopos
		, scorelogosize, 10
		, static_cast<int>(Fight_Effects::fight_effects_Motion::SCORE));

	p2digit_ = new PlayerScore(game, Vec2(p2scorelogopos.x_ + 80, p2scorelogopos.y_ + 100), difitsize);
	p2second_digit_ = new PlayerScore(game, Vec2(p2scorelogopos.x_ + 0, p2scorelogopos.y_ + 100), difitsize);
	p2third_digit_ = new PlayerScore(game, Vec2(p2scorelogopos.x_ - 80, p2scorelogopos.y_ + 100), difitsize);

	int p2a = (p2score_ % 10);
	p2digit_->AddScore(p2a);

	int p2b = p2score_ / 10;
	p2second_digit_->AddScore(p2b);

	int p2c = (p2score_ / 100);
	p2third_digit_->AddScore(p2c);
}
VSResultScene::~VSResultScene()
{
	temp->SetState(Actor::State::Dead);

	youwinlogo_->SetState(Actor::State::Dead);
	scorelogo_->SetState(Actor::State::Dead);
	digit_->SetState(Actor::State::Dead);
	second_digit_->SetState(Actor::State::Dead);
	third_digit_->SetState(Actor::State::Dead);
	waku1_->SetState(Actor::State::Dead);
	waku2_->SetState(Actor::State::Dead);
	p2youwinlogo_->SetState(Actor::State::Dead);
	p2scorelogo_->SetState(Actor::State::Dead);
	p2digit_->SetState(Actor::State::Dead);
	p2second_digit_->SetState(Actor::State::Dead);
	p2third_digit_->SetState(Actor::State::Dead);
}
void VSResultScene::Initialize(Game* game)
{
	iconsize_ = (Vec2(300, 300));

	charapos = Vec2(150, WINDOW_HEIGHT / 2 + 30);
	bar = 330;

	charaUIsize = Vec2(50, 50);
	charaUIpos = Vec2(WINDOW_WIDTH - charaUIsize.x_ / 2, charapos.y_);
	exitsize_ = Vec2(150, 150);
}

void VSResultScene::HandleInput(Game* game)
{
	if (GetKeyboardRelease(DIK_SPACE))
	{
		
		game->GetGSM()->ChangeState(new ModeselectScene(game));

		//game->GetGSM()->ChangeState(new BattleScene(game, 0, 0, 1));
	}

}

void VSResultScene::Update(Game* game)
{

}



