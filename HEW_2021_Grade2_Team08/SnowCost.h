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

    const int k_snowframe_tex_;                       //枠のテクスチャ
    const int k_snowpoint_tex_;                         //ポイントのテクスチャ

    const Vec2 k_frame_size_;                           //フレームの大きさ
    const Vec2 k_frame_pos_;                            //フレームの位置
   
    const int k_point_num_;                              //ポイントメモリの数
    const Vec2 k_point_pos_;                            //一番左のメモリの位置
    const Vec2 k_point_size_;                           //メモリの大きさ
    const float k_point_var_;                            //メモリ間の幅

   
public:
    SnowCost(Game* game);
    ~SnowCost();
    void UpdateActor(float deltatime) override;
    void SetSnownum(int snownum);
    
};

//一つ一つのメモリのクラス
class SnowPoint :
    public Actor
{
public:
    SnowPoint(class Game* game, int tex, Vec2 pos, Vec2 size);
    ~SnowPoint();
    void UpdateActor(float delta_time) override;
    void pointUVWHset(Vec2 uvwh);
private:
    class SpriteComponent* point_asc_;
    Vec2  UVWH;                 //UVWHを操作してメモリを透明・可視化する

    const Vec2 k_point_size;
};
