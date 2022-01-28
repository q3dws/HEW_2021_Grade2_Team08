#pragma once
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"
#include "Player.h"

//雪のコスト枠を表示、及びメモリを管理するクラス
//作成者　君島朝日
// 作成日　2021/12/08
//

class SnowCost :
    public Actor
{
private:
    class SpriteComponent* frame_asc_;
    std::vector<class SnowPoint*> snowpoints_; //メモリオブジェクトを作る動的配列

    int snowframe_tex_;                       //枠のテクスチャ

    const Vec2 k_frame_size_;                           //フレームの大きさ
    Vec2 k_frame_pos_;                            //フレームの位置
   
    const int k_point_num_;                              //ポイントメモリの数
    Vec2 k_point_pos_;                            //一番左のメモリの位置
    const Vec2 k_point_size_;                           //メモリの大きさ
    const float k_point_var_;                            //メモリ間の幅

    const bool k_Is_player_;
public:
    SnowCost(Game* game, bool Is_player);
    ~SnowCost();
    void UpdateActor(float deltatime) override;
    void SetSnownum(int snownum);
    
};

//一つ一つのメモリのクラス
class SnowPoint :
    public Actor
{
public:
    SnowPoint(class Game* game, Vec2 pos, Vec2 size, int layer);
    ~SnowPoint();
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
    const int k_point_SE_;
    enum class point_frame_num : int
    {
        ADVENT = 7,
        IDLE = 1,
        LEAVE = 4,
    };

    enum class point_Motion :int
    {
        ADVENT,     //登場
        IDLE,     //通常
        LEAVE,      //退場
    };

};
