#pragma once
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"
#include "Player.h"

class SnowCost_tate :
    public Actor
{
private:
    class SpriteComponent* frame_asc_;
    std::vector<class SnowPoint_tate*> snowpoints_; //メモリオブジェクトを作る動的配列

    const int k_snowframe_tex_;                       //枠のテクスチャ

    const Vec2 k_frame_size_;                           //フレームの大きさ
    Vec2 k_frame_pos_;                            //フレームの位置

    const int k_point_num_;                              //ポイントメモリの数
    Vec2 k_point_pos_;                            //一番左のメモリの位置
    const Vec2 k_point_size_;                           //メモリの大きさ
    const Vec2 k_point_var_;                            //メモリ間の幅

    const bool k_Is_player_;
public:
    SnowCost_tate(Game* game, bool Is_player);
    ~SnowCost_tate();
    void UpdateActor(float deltatime) override;
    void SetSnownum(int snownum);

};

//一つ一つのメモリのクラス
class SnowPoint_tate :
    public Actor
{
public:
    SnowPoint_tate(class Game* game, Vec2 pos, Vec2 size, int layer);
    ~SnowPoint_tate();
    void UpdateActor(float delta_time) override;
    void pointUVWHset(Vec2 uvwh);
    void point_texchange(int texnum);
    void point_inset();
    void point_outset();
private:
    class AnimSpriteComponent* point_asc_;
    Vec2  UVWH;                 //UVWHを操作してメモリを透明・可視化する

    const Vec2 k_point_size_;
    const Vec2 k_point_pos_;
    const int k_point_layer_;

    int point_state_;
    float motioncount_;
    int point_tex_[3];                       //ポイントのテクスチャ

    enum class point_frame_num : int
    {
        ADVENT = 7,
        IDLE = 1,
        LEAVE = 5,
    };

    enum class point_Motion :int
    {
        ADVENT,     //登場
        IDLE,     //通常
        LEAVE,      //退場
    };

};
