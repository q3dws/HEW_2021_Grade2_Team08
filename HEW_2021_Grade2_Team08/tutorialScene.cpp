#include "tutorialScene.h"
#include "Math.h"

#include "BGSpriteComponent.h"

#include "Game.h"
#include "Texture.h"
#include "sprite.h"
#include "input.h"
#include "ModeselectScene.h"
#include "sound.h"
#include <algorithm>

tutorialScene::tutorialScene(Game* game)

{
	Initialize(game);
	temp = new Actor(game);
	temp->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(temp, 10);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int > bgtexs = {
		game->GetTexture(L"Data/Image/sousa/sousa.png"),
		//game->GetTexture(L"Data/Image/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	//bg->SetScrollSpeed(-100.0f);


	/*temp2 = new Actor(game);
	temp2->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f - 100));
	bg = new BGSpriteComponent(temp2, 20);
	bg->SetScreenSize(Vec2(512 * 2, 128 * 2));
	bgtexs = {
		game->GetTexture(L"Data/Image/titlelogo_2.png")
	};
	bg->SetBGTextures(bgtexs);

	temp1 = new Actor(game);
	temp1->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f + 150));
	asc = new SpriteComponent(temp1, 21);
	asc->SetTexture(game->GetTexture(L"Data/Image/title_start2.png")
		, Vec2(256 * 2, 64 * 2), Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));*/
	fadecheck_ = true;


}
tutorialScene::~tutorialScene()
{
	StopSound(BGM_);
	delete temp;
	//delete temp1;
	//delete temp2;

}
void tutorialScene::Initialize(Game* game)
{
	texsize_ = (Vec2(600, 600));

	texpos = Vec2(100, WINDOW_HEIGHT / 2 + 20);
	texbar = 150;

	startalfa_ = 1.0f;
	BGM_ = LoadSound(L"Data/BGM/title.wav");
	SetVolume(BGM_, 0.15);
	SE_ = LoadSound(L"Data/SE/Scene/push.wav");
	SetVolume(SE_, 0.6);
	PlaySound(BGM_, -1);
}

void tutorialScene::HandleInput(Game* game)
{

	if (GetKeyboardRelease(DIK_SPACE))
	{
		PlaySound(SE_, 0);
		game->GetGSM()->ChangeState(new ModeselectScene(game));
		//game->GetGSM()->ChangeState(new BattleScene(game, 6, 0, 1, 0));
		//game->GetGSM()->ChangeState(new ResultScene(game, 24,24 , 5, 0,0));
		//game->GetGSM()->ChangeState(new VSResultScene(game, 24, 24));
	}


}

void tutorialScene::Update(Game* game)
{

	if (startalfa_ <= 0.0f)
	{
		fadecheck_ = false;
	}
	if (startalfa_ >= 1.0f)
	{
		fadecheck_ = true;
	}

	if (fadecheck_)
	{
		startalfa_ -= 0.3 * 0.05;
	}
	else
	{
		startalfa_ += 0.3 * 0.05;
	}
	//asc->SetAlfa(startalfa_);


}
