#pragma once
#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H
#include "Actor.h"
#include "Game.h"
#include<list>
#include<iostream>
#include "Bullet.h"
#include <vector>
/*
    作成者　君島朝日
    作成日 2021/11/17
*/

class BulletManager 
{
private:
    int bullettex_;                              //弾のテクスチャ
    //std::list<Bullet*>bullets_;
    std::vector<class Bullet*> bullets_; //弾のオブジェクトを作る動的配列
public:
    BulletManager();
    ~BulletManager();

    void Initialize();

    void Update();

    void Draw();

    void Finalize();

    void Shot();

private:

    void DeleteBullet();//画面外に出た弾を削除する
};
#endif // !BULLETMANAGER_H



