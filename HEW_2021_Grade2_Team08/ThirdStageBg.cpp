#include "ThirdStageBg.h"
#include "Window.h"
#include "BGSpriteComponent.h"

ThirdStageBg::ThirdStageBg(Game* game)
	:StageBg(game)
{
	auto temp = new Actor(game);
	temp->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	BGSpriteComponent* bg = new BGSpriteComponent(temp, 10);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int > bgtexs = {
		game->GetTexture(L"Data/Image/BackGround_3.png")
	};
	bg->SetBGTextures(bgtexs);
}
