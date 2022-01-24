#include <Windows.h>
#include "Game.h"
#include "Window.h"
#include "input.h"
#include "renderer.h"
#include "sprite.h"
#include "Texture.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Math.h"
#include "AnimationTestObj.h"	
#include "BGSpriteComponent.h"
#include "GameScene.h"
#include "sound.h"

#ifdef _DEBUG
INT g_debug_count_fps;
wchar_t			g_DebugStr[4096]{ WIN_APP_NAME };
#endif

Game::Game()
	:is_running_(true)
{
	ZeroMemory(this, sizeof(Window));
	ZeroMemory(&msg_, sizeof(msg_));

}

Game::~Game()
{

	//delete pgame_state_context_;
	timeEndPeriod(1);	// 分解能を戻す
}
static int	g_TextureNo = 0;
bool Game::Initialize(HINSTANCE hinstance)
{
	p_window_ = std::make_unique<Window>();
	if (p_window_)
	{
		if (FAILED(p_window_->InitWindow(hinstance_, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, WIN_CLASS_NAME, WIN_APP_NAME)))
			return false;

		hwnd_ = p_window_->hwnd_;

		ShowWindow(hwnd_, SW_SHOW);
		UpdateWindow(hwnd_);

		//    初期化処理                     //
		InitRenderer(hinstance, hwnd_);
		InitInput(hinstance, hwnd_);

		InitSound(hwnd_);

		InitSprite();

		///////////////////////////////////////
		LoadData();

		ticks_count_ = timeGetTime();
		return true;
	}
	else
	{
		return false;
	}
}

void Game::Application()
{
	while (msg_.message != WM_QUIT)
	{
		if (PeekMessage(&msg_, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg_);
			DispatchMessage(&msg_);
		}
		else //アプリケーションの処理はここから飛ぶ。
		{
			if (FpsTimer()) // 60FPSで起動
				RunLoop(); // ゲームループ
		}
	}
}

void Game::RunLoop()
{
	Input();
	Update();
	Draw();
}

bool Game::FpsTimer()
{
	dw_current_time_ = timeGetTime();					// システム時刻を取得

	if ((dw_current_time_ - dw_fpw_last_time_) >= 1000)	// 1秒ごとに実行
	{
#ifdef _DEBUG
		g_debug_count_fps = dw_frame_count_;
#endif
		dw_fpw_last_time_ = dw_current_time_;				// FPSを測定した時刻を保存
		dw_frame_count_ = 0;							// カウントをクリア
	}

	if ((dw_current_time_ - dw_exec_last_time_) >= (1000.0f / 60))	// 1/60秒ごとに実行
	{
		dw_exec_last_time_ = dw_current_time_;	// 処理した時刻を保存

#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する
		wsprintf(g_DebugStr, WIN_APP_NAME);
		wsprintf(&g_DebugStr[wcslen(g_DebugStr)], L" FPS:%d", g_debug_count_fps);
		SetWindowText(p_window_->hwnd_, g_DebugStr);
#endif
		++dw_frame_count_;		// 処理回数のカウントを加算
		return true;
	}
	return false;
}

void Game::Input()
{
	pgame_state_context_->HandleInput();
}

void Game::Update()
{

	deltatime_ = 0.05f;//(timeGetTime() - ticks_count_) / 1000.f;
	if (deltatime_ > 0.05f) deltatime_ = 0.05f;
	ticks_count_ = (float)timeGetTime();

	UpdateInput();

	updating_actors_ = true;
	for (auto actor : actors_)
		actor->Update(deltatime_);
	updating_actors_ = false;

	for (auto pending : pending_actors_)
	{
		actors_.emplace_back(pending);
	}
	pending_actors_.clear();

	std::vector<Actor*> dead_actors;
	for (auto actor : actors_)
		if (actor->GetState() == Actor::Dead)
			dead_actors.emplace_back(actor);

	for (auto actor : dead_actors)
		delete actor;

	pgame_state_context_->Update();

}

void Game::Draw()
{
	Clear();
	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換
	// 2D描画なので深度無効
	SetDepthEnable(false);

	for (auto sprite : sprites_)
	{
		sprite->Draw();
	}
	// シーンの描画処理
	//DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);


	// バックバッファ、フロントバッファ入れ替え
	Present();
}

void Game::LoadData()
{
	pgame_state_context_ = new StateContext<Game>(this);
	pgame_state_context_->SetCurrentState(new StartScene(this));
}

void Game::UnloadData()
{

	while (!actors_.empty())
		delete actors_.back();
}

void Game::Shutdown()
{
	UnloadData();
	UninitRenderer();
	UninitSprite();
}

void Game::AddActor(Actor* actor)
{
	if (updating_actors_)
		pending_actors_.emplace_back(actor);
	else
		actors_.emplace_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(pending_actors_.begin(), pending_actors_.end(), actor);
	if (iter != pending_actors_.end())
	{
		//pending_actors_.erase(iter);
		std::iter_swap(iter, pending_actors_.end() - 1);
		pending_actors_.pop_back();
	}

	iter = std::find(actors_.begin(), actors_.end(), actor);
	if (iter != actors_.end())
	{
		//actors_.erase(iter);
		std::iter_swap(iter, actors_.end() - 1);
		actors_.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	int my_draw_order = sprite->GetDrawOrder();
	auto iter = sprites_.begin();
	for (; iter != sprites_.end(); ++iter)
		if (my_draw_order < (*iter)->GetDrawOrder())
			break;
	sprites_.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(sprites_.begin(), sprites_.end(), sprite);
	sprites_.erase(iter);
}

int Game::GetTexture(wchar_t const* file_name)
{
	return LoadTexture(file_name);
}




void Game::RemoveIceWall(IceWall* iceWall)
{
	auto iter = std::find(icewall_.begin(), icewall_.end(), iceWall);
	if (iter != icewall_.end())
	{
		//pending_actors_.erase(iter);
		std::iter_swap(iter, icewall_.end() - 1);
		icewall_.pop_back();
	}

}

void Game::RemoveArmor(Armor* armor)
{
	auto iter = std::find(armor_.begin(), armor_.end(), armor);
	if (iter != armor_.end())
	{
		//pending_actors_.erase(iter);
		std::iter_swap(iter, armor_.end() - 1);
		armor_.pop_back();
	}

}

void Game::RemoveGolem(Golem* golem)
{
	auto iter = std::find(golem_.begin(), golem_.end(), golem);
	if (iter != golem_.end())
	{
		//pending_actors_.erase(iter);
		std::iter_swap(iter, golem_.end() - 1);
		golem_.pop_back();
	}
}
