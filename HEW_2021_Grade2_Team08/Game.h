#pragma once
#ifndef GAME_H
#define GAME_H
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include "Math.h"
#include "StateContext.h"


class Window;

class Game
{
public:
    Game();
    ~Game();
    bool Initialize(HINSTANCE hinstance);
    void Application();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);

    void DeleteActor(class Actor* act);

    int GetTexture(wchar_t const * file_name);
    StateContext<Game>* GetGSM() const { return pgame_state_context_; }
private:
    void RunLoop();
    bool FpsTimer();
    void Input();
    void Update();
    void Draw();
    void LoadData();
    void UnloadData();

private:
    // ウインドウ関連変数
    std::unique_ptr<Window> p_window_;
    HINSTANCE hinstance_;
    HWND hwnd_;
    MSG msg_;

    // FPS用変数
    DWORD ticks_count_;
    float deltatime_;
    DWORD dw_exec_last_time_;
    DWORD dw_fpw_last_time_;
    DWORD dw_current_time_;
    DWORD dw_frame_count_;

    //ゲーム用変数
    //std::unordered_map<>
    bool is_running_;
    bool updating_actors_;
    std::vector<class Actor*> actors_;
    std::vector<class Actor*> pending_actors_;
    std::list<class SpriteComponent*> sprites_;
    StateContext<Game> * pgame_state_context_;
};

#endif // !GAME_H