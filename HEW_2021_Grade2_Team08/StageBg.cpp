#include "StageBg.h"
#include "Window.h"
#include "BGSpriteComponent.h"

StageBg::StageBg(Game* game)
	:Actor(game)
{
	auto temp = new Actor(game);
	temp->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	BGSpriteComponent* bg = new BGSpriteComponent(temp, 10);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int > bgtexs = {
		game->GetTexture(L"Data/Image/BackGround_002.png")
	};
	bg->SetBGTextures(bgtexs);

	auto bgsta = new Actor(game);
	bgsta->SetPosition(Vec2(WINDOW_WIDTH * 0.5, STAGE_HEIGHT));
	BGSpriteComponent* sbg = new BGSpriteComponent(temp, 11);
	sbg = new BGSpriteComponent(bgsta, 15);
	sbg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int> sbgtexs = {
		game->GetTexture(L"Data/Image/stage_2.png")
	};

	sbg->SetBGTextures(sbgtexs);
}
