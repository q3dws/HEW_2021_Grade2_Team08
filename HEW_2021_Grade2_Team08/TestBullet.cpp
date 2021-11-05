#include "TestBullet.h"
#include "SpriteComponent.h"
#include "Window.h"
TestBullet::TestBullet(Game* game)
    :Actor(game)
    ,death_timer(0.2f)
{
    auto sc = new SpriteComponent(this, 150);
    sc->SetTexture(game->GetTexture(L"Data/Image/13558.png"), Vec2(30, 30), Vec2(0, 0), Vec2(1, 1));
}

void TestBullet::UpdateActor(float deltatime)
{
    Actor::UpdateActor(deltatime);

    SetPosition(Vec2(GetPosition().x_ + 10, GetPosition().y_));
    if (GetPosition().x_ > WINDOW_WIDTH)
        delete this;
}