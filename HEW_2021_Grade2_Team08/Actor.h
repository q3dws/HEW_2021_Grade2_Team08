#pragma once
#ifndef ACTOR_H
#define ACTOR_H
#include <vector>
#include <list>
#include "Math.h"
class Actor
{
public:
    enum State
    {
        Active,
        Dead
    };
    Actor(class Game* game);
    virtual ~Actor();

    void Update(float deltatime);
    void UpdateComponents(float deltatime);
    virtual void UpdateActor(float deltatime);

    const Vec2& GetPosition() const { return position_; }
    void  SetPosition(const Vec2& pos) { position_ = pos; }
    float GetScale() const { return scale_; }
    void  SetScale(float scale) { scale_ = scale; }
    float GetRotation() const { return rotation_; }
    void  SetRotation(float rotation) { rotation_ = rotation; }
    Vec2  GetForward() const { return Vec2(cosf(rotation_), sinf(rotation_)); }
    // �����̃A�N�^�[�̂���}�X�ڂ̔z��v�f�ԍ��̐ݒ�
    void  SetPosIndex(int index) { position_index_ = index; }
    // �����̃A�N�^�[�̂���}�X�ڂ̔z��v�f�ԍ�
    int   GetPosIndex() const { return position_index_; }
    // �������蔻��p�̋�`�̐ݒ�@���S���W�ƃT�C�Y��ݒ�
    void  SetCollision(const Rect& collision) { collision_ = collision; }
    // �������蔻��p�̋�`�̒��S���W�ƃT�C�Y
    Rect  GetCollision() const { return collision_; }
    void  MoveCollison(const Vec2 move) { collision_.center_ += move; collision_.topleft_ += move; collision_.bottomright_ += move; }

    State GetState() const { return state_; }
    void  SetState(State state) { state_ = state; }
    class Game* GetGame() const { return game_; }

    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);
private:
    State state_;
    Vec2 position_;
    float scale_;
    float rotation_;
    int position_index_; // ���A�N�^�[�̂���z��̗v�f�ԍ��������
    Rect collision_;        // �������蔻��p�̋�`
    std::list<class Component*> components_;
    class Game* game_;
};
#endif // !ACTOR_H
