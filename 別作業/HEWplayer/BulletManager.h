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
    �쐬�ҁ@�N������
    �쐬�� 2021/11/17
*/

class BulletManager 
{
private:
    int bullettex_;                              //�e�̃e�N�X�`��
    //std::list<Bullet*>bullets_;
    std::vector<class Bullet*> bullets_; //�e�̃I�u�W�F�N�g����铮�I�z��
public:
    BulletManager();
    ~BulletManager();

    void Initialize();

    void Update();

    void Draw();

    void Finalize();

    void Shot();

private:

    void DeleteBullet();//��ʊO�ɏo���e���폜����
};
#endif // !BULLETMANAGER_H



