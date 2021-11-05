#pragma once
#ifndef ACTOR_H
#define ACTOR_H
#include <vector>
#include "Math.h"
class Actor
{
public:
    Actor(class Game* game);
    virtual ~Actor();

    void Update(float deltatime);
    void UpdateComponents(float deltatime);
    virtual void UpdateActor(float deltatime);

    const Vec2& GetPosition(               ) const { return position_; }
          void  SetPosition(const Vec2& pos)       { position_ = pos; }
          float GetScale   (               ) const { return scale_; }
          void  SetScale   (float scale    )       { scale_ = scale; }
          float GetRotation(               ) const { return rotation_; }
          void  SetRotation(float rotation )       { rotation_ = rotation; }
          Vec2  GetForward (               ) const { return Vec2(cosf(rotation_), sinf(rotation_)); }
    class Game* GetGame() { return game_; }

    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);
private:
    Vec2 position_;
    float scale_; 
    float rotation_;

    std::vector<class Component*> components_;
    class Game* game_;
};
#endif // !ACTOR_H
