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

    int GetTexture(wchar_t const* file_name);
    StateContext<Game>* GetGSM() const { return pgame_state_context_; }

    // ���Q�[�����L
    void SetPlayer(class Player* player) { player_ = player; } // ���Q�[���Ƀv���C���[�̃A�h���X��m�点��i�R���X�g���N�^�ł���������~�X�����Ȃ����E�E�E�j
    class Player* GetPlayer() const { return player_; }

    void SetPlayer2p(class Player* player) { player_2p_ = player; } // ���Q�[���Ƀv���C���[�̃A�h���X��m�点��i�R���X�g���N�^�ł���������~�X�����Ȃ����E�E�E�j
    class Player* GetPlayer2p() const { return player_2p_; }

    void SetScoreManager(class ScoreManager* scoremanager) { scoremanager_ = scoremanager; } // ���Q�[���ɃX�R�A�̃A�h���X��m�点��i�R���X�g���N�^�ł���������~�X�����Ȃ����E�E�E�j
    class ScoreManager* GetScoreManager() const { return scoremanager_; }

    void SetIceWall(class IceWall* icewall) { icewall_.emplace_back(icewall); }
    int  GetIceWallSize() const { return icewall_.size(); }
    class IceWall* GetIceWall(int num) const { return icewall_[num]; }

    void SetArmor(class Armor* armor) { armor_.emplace_back(armor); }
    int  GetArmorSize() const { return armor_.size(); }
    class Armor* GetArmor(int num) const { return armor_[num]; }

    void SetGolem(class Golem* golem) { golem_.emplace_back(golem); }
    int  GetGolemSize() const { return golem_.size(); }
    class Golem* GetGolem(int num) const { return golem_[num]; }

private:
    void RunLoop();
    bool FpsTimer();
    void Input();
    void Update();
    void Draw();
    void LoadData();
    void UnloadData();

private:
    // �E�C���h�E�֘A�ϐ�
    std::unique_ptr<Window> p_window_;
    HINSTANCE hinstance_;
    HWND hwnd_;
    MSG msg_;

    // FPS�p�ϐ�
    DWORD ticks_count_;
    float deltatime_;
    DWORD dw_exec_last_time_;
    DWORD dw_fpw_last_time_;
    DWORD dw_current_time_;
    DWORD dw_frame_count_;

    //�Q�[���p�ϐ�
    //std::unordered_map<>
    bool is_running_;
    bool updating_actors_;
    std::vector<class Actor*> actors_;
    std::vector<class Actor*> pending_actors_;
    std::list<class SpriteComponent*> sprites_;
    StateContext<Game>* pgame_state_context_;

    // ���Q�[���ŗL
    class Player* player_; //���ǂ̃A�N�^�[����ł��v���C���[�ƒʐM���邽�߂̂���
    class Player* player_2p_; //���ǂ̃A�N�^�[����ł��v���C���[�ƒʐM���邽�߂̂���

    class ScoreManager* scoremanager_;
   
    std::vector<class IceWall*> icewall_; 
    std::vector<class Armor*>armor_;
    std::vector<class Golem*>golem_;
};

#endif // !GAME_H