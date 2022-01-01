#pragma once
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"
#include "Player.h"

//�X�L���̃A�C�R����\���A�Ȃ�тɊǗ�����N���X
//�쐬�ҁ@�N������
// �쐬���@2021/12/08
//

class Skillicon :
    public Actor
{
private:
    std::vector<class Icon*> icons_; //�������I�u�W�F�N�g����铮�I�z��
    const int k_snowcost_[4];           //�X�L���̃R�X�g

    const int k_Skillicon_tex_[18];                         //Skillicon�̃e�N�X�`��

    const int k_Skillicon_num_;                              //Skillicon�̐�
    Vec2 k_Skillicon_pos_;                            //��ԍ���Skillicon�̈ʒu
    const Vec2 k_Skillicon_size_;                           //Skillicon�̑傫��
    const float k_Skillicon_var_;                            //Skillicon�Ԃ̕�

    const int k_who_player_;
    const bool k_Is_player_;
public:
    Skillicon(Game* game, bool Is_player,int who, int skillcost0, int skillcost1, int skillcost2, int skillcost3);
    ~Skillicon();
    void UpdateActor(float deltatime) override;
    void SetSnownum(int snownum);
};


//�A�C�R�����̃N���X
class Icon :
    public Actor
{
public:
    Icon(class Game* game, Vec2 pos, Vec2 size, int layer, int lighttex, int darktex);
    ~Icon();
    void UpdateActor(float delta_time) override;
    
   // void Icon_texchange(int texnum);
    void Icon_inset();
    void Icon_outset();
private:
    class SpriteComponent* Icon_asc_;
    
    const Vec2 k_Icon_size_;
    const Vec2 k_Icon_pos_;
    const int k_Icon_layer_;

    //int Icon_state_;
    
    const int k_Icon_tex_[2];                       //Icon�̃e�N�X�`��

    enum class Icon_frame_num : int
    {
        light = 1,
        dark = 1,
        LEAVE = 4,
    };

    enum class Icon_Motion :int
    {
        light,     //����
        dark,     //����Ȃ�
    };

};
