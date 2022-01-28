#pragma once
#ifndef GAME_H
#define GAME_H
#include <memory>
#include <vector>
#include <list>
#include <array>
#include <unordered_map>
#include "Math.h"
#include "StateContext.h"
#include "CharaselectScene.h"

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

    int GetTexture(wchar_t const* file_name);
    StateContext<Game>* GetGSM() const { return pgame_state_context_; }

    // ★ゲーム特有
    std::vector<int>& RetEnemyStack();
    void SetThreeEnemy(int pnum);
    
    void SetPlayer(class Player* player) { player_ = player; } // ★ゲームにプレイヤーのアドレスを知らせる（コンストラクタでやった方がミスが少ないが・・・）
    class Player* GetPlayer() const { return player_; }

    void SetPlayer2p(class Player* player) { player_2p_ = player; } // ★ゲームにプレイヤーのアドレスを知らせる（コンストラクタでやった方がミスが少ないが・・・）
    class Player* GetPlayer2p() const { return player_2p_; }

    void SetEnemy(class Enemy* enemy) { enemy_ = enemy; }
    class Enemy* GetEnemy() const { return enemy_; }

    void SetScoreManager(class ScoreManager* scoremanager) { scoremanager_ = scoremanager; } // ★ゲームにスコアのアドレスを知らせる（コンストラクタでやった方がミスが少ないが・・・）
    class ScoreManager* GetScoreManager() const { return scoremanager_; }

    void SetIceWall(class IceWall* icewall) { icewall_.emplace_back(icewall); }
    int  GetIceWallSize() const { return icewall_.size(); }
    class IceWall* GetIceWall(int num) const { return icewall_[num]; }
    void RemoveIceWall(class IceWall* iceWall);

    void SetArmor(class Armor* armor) { armor_.emplace_back(armor); }
    int  GetArmorSize() const { return armor_.size(); }
    class Armor* GetArmor(int num) const { return armor_[num]; }
    void RemoveArmor(class Armor* armor);

    void SetGolem(class Golem* golem) { golem_.emplace_back(golem); }
    int  GetGolemSize() const { return golem_.size(); }
    class Golem* GetGolem(int num) const { return golem_[num]; }
    void RemoveGolem(class Golem* golem);


    bool AddEGolem(class EGolem* egolem);
    void RemoveEGolem(class EGolem* egolem);
    void RemoveAllEgolem();
    std::array<EGolem*, 3>& GetEGolems() { return egolems_; };

    bool AddEIceWall(class EIceWall* eicewall);
    void RemoveEIceWall(class EIceWall* eicewall);
    void RemoveAllEIceWall();
    std::array<EIceWall*, 3>& GetEIceWalls() { return eicewalls_; };

    bool AddEArmor(class EArmor* earmor);
    void RemoveEArmor(class EArmor* earmor);
    void RemoveAllEArmor();
    std::array<EArmor*, 3>& GetEArmor() { return earmors_; }

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
    StateContext<Game>* pgame_state_context_;

    // ★ゲーム固有
    class Player* player_; //★どのアクターからでもプレイヤーと通信するためのもの
    class Player* player_2p_; //★どのアクターからでもプレイヤーと通信するためのもの
    class Enemy* enemy_;

    class ScoreManager* scoremanager_;
   
    std::vector<class IceWall*> icewall_; 
    std::vector<class Armor*>armor_;
    std::vector<class Golem*>golem_;

    std::array<class EGolem*  , 3>   egolems_;
    std::array<class EIceWall*, 3> eicewalls_;
    std::array<class EArmor*  , 3>   earmors_;
    std::vector<int> enemystack_;
};

#endif // !GAME_H