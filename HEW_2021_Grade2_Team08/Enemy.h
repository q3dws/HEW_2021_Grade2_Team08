#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "Actor.h"
#include "Game.h"
#include <vector>

class  Enemy : public Actor
{
private:
    D3DXVECTOR2 enemy_pos_;          //画面上の座標
    int     enemy_snow_;                     //現在持っている雪
    int     enemy_pos_num_;   

    //プレイヤーのいるマスの番号
    /*
    012
    345 それぞれの数字がマスの番号に対応
    678
    */
    int     enemy_direction_;   //方向
    int     enemy_hp_;
    //class Stage* pstage;

    int bullettex_;                              //弾のテクスチャ
    std::vector<class Bullet*> bullets_; //弾のオブジェクトを作る動的配列

    const int enemy_snow_max_;     //持てる雪の上限
    const int enemy_snow_min_;     //持てる雪の下限

    const D3DXVECTOR2 enemy_pos_center_;      //9マスの真ん中の座標
    const D3DXVECTOR2 enemy_pos_var_;          //移動量　
    const D3DXVECTOR2 enemy_vel_;          //移動速度

    StateContext<Enemy>* penemy_state_context_;

public:
    Enemy(class Game* game);


    void UpdateActor(float deltatime) override;
    bool UpdateTimer(int ms);

    void enemy_move();
    void enemy_snow_collect();
    //void enemy_snow_throw();

    //enemy() : enemy_snow_max_(16){}
};
#endif // enemy_H