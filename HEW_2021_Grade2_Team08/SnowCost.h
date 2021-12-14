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

    const int k_snowframe_tex_;                       //�g�̃e�N�X�`��
    const int k_snowpoint_tex_;                         //�|�C���g�̃e�N�X�`��

    const Vec2 k_frame_size_;                           //�t���[���̑傫��
    const Vec2 k_frame_pos_;                            //�t���[���̈ʒu
   
    const int k_point_num_;                              //�|�C���g�������̐�
    const Vec2 k_point_pos_;                            //��ԍ��̃������̈ʒu
    const Vec2 k_point_size_;                           //�������̑傫��
    const float k_point_var_;                            //�������Ԃ̕�

   
public:
    SnowCost(Game* game);
    ~SnowCost();
    void UpdateActor(float deltatime) override;
    void SetSnownum(int snownum);
    
};

//���̃������̃N���X
class SnowPoint :
    public Actor
{
public:
    SnowPoint(class Game* game, int tex, Vec2 pos, Vec2 size);
    ~SnowPoint();
    void UpdateActor(float delta_time) override;
    void pointUVWHset(Vec2 uvwh);
private:
    class SpriteComponent* point_asc_;
    Vec2  UVWH;                 //UVWH�𑀍삵�ă������𓧖��E��������

    const Vec2 k_point_size;
};
