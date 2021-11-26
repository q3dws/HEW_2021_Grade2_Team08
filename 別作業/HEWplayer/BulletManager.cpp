#include "BulletManager.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"
#include "input.h"
#include "Window.h"


BulletManager::BulletManager() :bullets_(100)
{
	this->bullettex_ = LoadTexture(L"Data/Image/13558.png"); //弾のテクスチャ

}

BulletManager::~BulletManager()
{
}

void BulletManager::Initialize()
{
}

void BulletManager::Update()
{
  
}

void BulletManager::Draw()
{
    
}

void BulletManager::Finalize()
{
}

void BulletManager::Shot()
{
	/*bullets_[bulletscount_] = new Bullet(GetGame(), bullettex_);
			bullets_[bulletscount_]->SetPosition(this->GetPosition());

			bulletscount_++;*/

	/*bullets_.push_back(new Bullet(GetGame(), bullettex_));
	bullets_.back()->SetPosition(this->GetPosition());*/

}

void BulletManager::DeleteBullet()
{
}
