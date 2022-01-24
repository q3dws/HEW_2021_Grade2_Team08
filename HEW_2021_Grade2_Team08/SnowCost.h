#pragma once
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"
#include "Player.h"

//��̃R�X�g�g��\���A�y�у��������Ǘ�����N���X
//�쐬�ҁ@�N������
// �쐬���@2021/12/08
//

class SnowCost :
    public Actor
{
private:
    class SpriteComponent* frame_asc_;
    std::vector<class SnowPoint*> snowpoints_; //�������I�u�W�F�N�g����铮�I�z��

    int snowframe_tex_;                       //�g�̃e�N�X�`��

    const Vec2 k_frame_size_;                           //�t���[���̑傫��
    Vec2 k_frame_pos_;                            //�t���[���̈ʒu
   
    const int k_point_num_;                              //�|�C���g�������̐�
    Vec2 k_point_pos_;                            //��ԍ��̃������̈ʒu
    const Vec2 k_point_size_;                           //�������̑傫��
    const float k_point_var_;                            //�������Ԃ̕�

    const bool k_Is_player_;
public:
    SnowCost(Game* game, bool Is_player);
    ~SnowCost();
    void UpdateActor(float deltatime) override;
    void SetSnownum(int snownum);
    
};

//���̃������̃N���X
class SnowPoint :
    public Actor
{
public:
    SnowPoint(class Game* game, Vec2 pos, Vec2 size, int layer);
    ~SnowPoint();
    void UpdateActor(float delta_time) override;
    void pointUVWHset(Vec2 uvwh);
    void point_texchange(int texnum);
    void point_inset();
    void point_outset();
private:
    class AnimSpriteComponent* point_asc_;
    Vec2  UVWH;                 //UVWH�𑀍삵�ă������𓧖��E��������

    const Vec2 k_point_size_;
    const Vec2 k_point_pos_;
    const int k_point_layer_;

    int point_state_;
    float motioncount_;
    int point_tex_[3];                       //�|�C���g�̃e�N�X�`��
    const int k_point_SE_;
    enum class point_frame_num : int
    {
        ADVENT = 7,
        IDLE = 1,
        LEAVE = 4,
    };

    enum class point_Motion :int
    {
        ADVENT,     //�o��
        IDLE,     //�ʏ�
        LEAVE,      //�ޏ�
    };

};
