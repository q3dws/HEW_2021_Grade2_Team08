#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "Actor.h"
#include "Game.h"
#include "Math.h"
#include "Texture.h"
#include "AnimSpriteComponent.h"
#include <vector>
#include <array>

#define EC       static_cast<int>          // Enum Cast
#define EnumCast static_cast<int>          // Enum Cast
#define RP() GetGame()->GetPlayer()          // Refer Player : GetGame()->GetPlayer()の短縮
#define ReferPlayer() GetGame()->GetPlayer() // Refer Player : GetGame()->GetPlayer()の短縮
enum class Costs {
    GOLEM       = 2,
    ICEWALL     = 1,
    BIGBULLET   = 4,
    ARMOR       = 2,
    FIREBALL    = 2,
    MACHINEGUN  = 1,
    SCOOP       = 2
};
struct Probabilities
{
    Probabilities() :
        move_     (38.0),
        up_       (25.0),
        down_     (25.0),
        left_     (25.0),
        right_    (25.0),
        gather_   (45.0),
        attack_   (10.0),
        golem_    (40.0),
        icewall_  (45.0),
        bigbullet_(25.0),
        unique_   (35.0)
    {}
    Probabilities(double move, double up , double down, double left, double right, double gather, double attack, double golem, double icewall,double bigbullet, double unique):
        move_     (move     ),
        up_       (up       ),
        down_     (down     ),
        left_     (left     ),
        right_    (right    ),
        gather_   (gather   ),
        attack_   (attack   ),
        golem_    (golem    ),
        icewall_  (icewall  ),
        bigbullet_(bigbullet),
        unique_   (unique   )
    {}
#if 1
    Probabilities  operator+ (const Probabilities& r)
    {
        return {
            move_       + r.move_     ,
            up_         + r.up_       ,
            down_       + r.down_     ,
            left_       + r.left_     ,
            right_      + r.right_    ,
            gather_     + r.gather_   ,
            attack_     + r.attack_   ,
            golem_      + r.golem_    ,
            icewall_    + r.icewall_  ,
            bigbullet_  + r.bigbullet_,
            unique_     + r.unique_
        };
    }
    Probabilities  operator+ (const double r)
    {
        return {
            move_       + r,
            up_         + r,
            down_       + r,
            left_       + r,
            right_      + r,
            gather_     + r,
            attack_     + r,
            golem_      + r,
            icewall_    + r,
            bigbullet_  + r,
            unique_     + r
        };
    }
    Probabilities  operator- (const Probabilities& r)
    {
        return {
            move_       - r.move_     ,
            up_         - r.up_       ,
            down_       - r.down_     ,
            left_       - r.left_     ,
            right_      - r.right_    ,
            gather_     - r.gather_   ,
            attack_     - r.attack_   ,
            golem_      - r.golem_    ,
            icewall_    - r.icewall_  ,
            bigbullet_  - r.bigbullet_,
            unique_     - r.unique_
        };
    }
    Probabilities  operator- (const double r)
    {
        return {
            move_       - r,
            up_         - r,
            down_       - r,
            left_       - r,
            right_      - r,
            gather_     - r,
            attack_     - r,
            golem_      - r,
            icewall_    - r,
            bigbullet_  - r,
            unique_     - r
        };
    }
    Probabilities  operator* (const Probabilities& r)
    {
        return {
            move_       * r.move_     ,
            up_         * r.up_       ,
            down_       * r.down_     ,
            left_       * r.left_     ,
            right_      * r.right_    ,
            gather_     * r.gather_   ,
            attack_     * r.attack_   ,
            golem_      * r.golem_    ,
            icewall_    * r.icewall_  ,
            bigbullet_  * r.bigbullet_,
            unique_     * r.unique_
        };
    }
    Probabilities  operator* (const double r)
    {
        return {
            move_       * r,
            up_         * r,
            down_       * r,
            left_       * r,
            right_      * r,
            gather_     * r,
            attack_     * r,
            golem_      * r,
            icewall_    * r,
            bigbullet_  * r,
            unique_     * r
        };
    }
    Probabilities& operator+=(const Probabilities& r)
    {
        move_       += r.move_     ;
        up_         += r.up_       ;
        down_       += r.down_     ;
        left_       += r.left_     ;
        right_      += r.right_    ;
        gather_     += r.gather_   ;
        attack_     += r.attack_   ;
        golem_      += r.golem_    ;
        icewall_    += r.icewall_  ;
        bigbullet_  += r.bigbullet_;
        unique_     += r.unique_   ;
        return *this;
    }
    Probabilities& operator+=(const double r)
    {
        move_       += r;
        up_         += r;
        down_       += r;
        left_       += r;
        right_      += r;
        gather_     += r;
        attack_     += r;
        golem_      += r;
        icewall_    += r;
        bigbullet_  += r;
        unique_     += r;
        return *this;
    }
    Probabilities& operator-=(const Probabilities& r)
    {
        move_       -= r.move_     ;
        up_         -= r.up_       ;
        down_       -= r.down_     ;
        left_       -= r.left_     ;
        right_      -= r.right_    ;
        gather_     -= r.gather_   ;
        attack_     -= r.attack_   ;
        golem_      -= r.golem_    ;
        icewall_    -= r.icewall_  ;
        bigbullet_  -= r.bigbullet_;
        unique_     -= r.unique_   ;
        return *this;
    }
    Probabilities& operator-=(const double r)
    {
        move_       -= r;
        up_         -= r;
        down_       -= r;
        left_       -= r;
        right_      -= r;
        gather_     -= r;
        attack_     -= r;
        golem_      -= r;
        icewall_    -= r;
        bigbullet_  -= r;
        unique_     -= r;
        return *this;
    }
    Probabilities& operator*=(const Probabilities& r)
    {
        move_       *= r.move_     ;
        up_         *= r.up_       ;
        down_       *= r.down_     ;
        left_       *= r.left_     ;
        right_      *= r.right_    ;
        gather_     *= r.gather_   ;
        attack_     *= r.attack_   ;
        golem_      *= r.golem_    ;
        icewall_    *= r.icewall_  ;
        bigbullet_  *= r.bigbullet_;
        unique_     *= r.unique_   ;
        return *this;
    }
    Probabilities& operator*=(const double r)
    {
        move_       *= r;
        up_         *= r;
        down_       *= r;
        left_       *= r;
        right_      *= r;
        gather_     *= r;
        attack_     *= r;
        golem_      *= r;
        icewall_    *= r;
        bigbullet_  *= r;
        unique_     *= r;
        return *this;
    }
#endif
    double move_     ;
    double up_       ;
    double down_     ;
    double left_     ;
    double right_    ;
    double gather_   ;
    double attack_   ;
    double golem_    ;
    double icewall_  ;
    double bigbullet_;
    double unique_   ;
};
struct AIPattern
{

};

struct PositionInfo
{
    PositionInfo():
        v_distance     (0),
        h_distance     (0),
        v_center_part  (1),
        h_center_part  (1),
        upper_part     (0),
        lower_part     (0),
        left_part      (0),
        right_part     (0),
        is_snow        (0),
        h_dist_is_three(0),
        same_row       (0),
        is_behind_wall (0),
        is_wall        (0),
        is_golem       (0)
    {}

    int  v_distance     ;
    int  h_distance     ;
    bool v_center_part  ;
    bool h_center_part  ;
    bool upper_part     ;
    bool lower_part     ;
    bool left_part      ;
    bool right_part     ;
    bool is_snow        ;
    bool h_dist_is_three;
    bool same_row       ;
    bool is_behind_wall ;
    bool is_wall        ;
    bool is_golem       ;
};
class Enemy 
    : public Actor
{
public: // メンバ関数
    Enemy(class Game* game, class Stage* stage);
    ~Enemy();
    //bool UpdateTimer(int ms);

protected:
    virtual void ChangeState  (       ) = 0;
    virtual void ChangeTexture(int tex) = 0;
    virtual void Unique       (       ) = 0;
 
    void SetHit            (                 );
    void SetDestination    (                 );
    void Move              (/*int direction*/);
    void Attack            (                 );
    void Gather            (                 );
    void Golem             (                 );
    void Wall              (                 );
    void BigSnow           (                 );

    void UpdateLayer       (                 );
    void UpdatePositionInfo(                 );
    void UpdateDirection   (                 );
    void UpdateNextAction  (                 );

    int  Direction         (                 );


public: // 定数
    const int   POSSESSION_MAX_;
    const int   UPDATE_FRAME_  ;
    const float ADJUST_VALUE_Y_;
    const Vec2  MOV_DISTANCE_  ;
    const Vec2  POS_CENTER_    ;
    const Vec2  VELOCITY_      ;
    enum Direction {
        D_LEFT ,
        D_RIGHT,
        D_UP   ,
        D_DOWN
    };
    enum class ANIMATION_INDEX {
        IDLE          ,
        ATTACK        ,
        MOVE_FRONT    ,
        MOVE_BACK     ,
        MOVE_UPANDDOWN,
        COLLECT_IN    ,
        COLLECT_LOOP  ,
        COLLECT_OUT   ,
        HIT           ,
        USE_SKILL     ,// スキル使用
        USE_SKILL_IN  ,// ロボ専用
        USE_SKILL_LOOP,// ロボ専用
        USE_SKILL_OUT  // ロボ専用
    };
    const int                  sounds_[6];
protected: // メンバ変数
    //StateContext<Enemy>* penemy_state_context_;
    class Stage *              stage_               ;
    int                        snow_num_            ;
    bool                       in_action_           ;
    bool                       in_animation_        ;
    int                        current_frame_       ;

    unsigned                   direction_           ;
    Vec2                       destination_         ;
    PositionInfo               position_info_       ;
    Probabilities              prob_info_           ;
    Probabilities              pi_subtrahend_       ;

    class AnimSpriteComponent* current_animation_   ;
    std::array<int, 13>        textures_            ;
    Vec2                       texsize_             ;
    int                        layer_               ;
    int                        bullettex_           ;
};
#endif // enemy_H