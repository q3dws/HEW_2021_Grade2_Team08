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
        Idle            ,
        Active          ,
        Dead            ,
        Attacking       ,
        Moving          ,
        Moving_F        ,
        Moving_B        ,
        Moving_UD       ,
        Gathering       ,
        Gathering_In    ,
        Gathering_Loop  ,
        Gathering_Out   ,
        Hit             ,
        Golem_s         ,
        IceWall_s       ,
        BigBullet_s     ,
        Unique_s        ,
        UsingSkills     ,
        UsingSkills_In  ,
        UsingSkills_Loop,
        UsingSkills_Out
    };
    Actor(class Game* game);
    virtual ~Actor();

    void Update(float deltatime);
    void UpdateComponents(float deltatime);
    virtual void UpdateActor(float deltatime);

    const Vec2& GetPosition() const { return position_; }
    void  SetPosition(const Vec2& pos) { position_ = pos; }
    void MovePosition(const Vec2& move) { SetPosition(Vec2(GetPosition().x_ + move.x_, GetPosition().y_ + move.y_)); }
    float GetScale() const { return scale_; }
    void  SetScale(float scale) { scale_ = scale; }
    float GetRotation() const { return rotation_; }
    void  SetRotation(float rotation) { rotation_ = rotation; }
    Vec2  GetForward() const { return Vec2(cosf(rotation_), sinf(rotation_)); }
    // ★このアクターのいるマス目の配列要素番号の設定
    void  SetPosIndex(int index) { position_index_ = index; }
    // ★このアクターのいるマス目の配列要素番号
    int   GetPosIndex() const { return position_index_; }
    // ★当たり判定用の矩形の設定　中心座標とサイズを設定
    void  SetCollision(const Rect& collision) { collision_ = collision; }
    // ★当たり判定用の矩形の中心座標とサイズ
    Rect  GetCollision() const { return collision_; }
    void  MoveCollison(const Vec2 move) { collision_.center_ += move; collision_.topleft_ += move; collision_.bottomright_ += move; }

    void  SetCollision2(const Rect& collision) { collision2_ = collision; }
    // ★当たり判定用の矩形の中心座標とサイズ
    Rect  GetCollision2() const { return collision2_; }
    void  MoveCollison2(const Vec2 move) { collision2_.center_ += move; collision2_.topleft_ += move; collision2_.bottomright_ += move; }

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
    int position_index_; // ★アクターのいる配列の要素番号をいれる
    Rect collision_;        // ★当たり判定用の矩形
    Rect collision2_;
    std::list<class Component*> components_;
    class Game* game_;
};
#endif // !ACTOR_H
