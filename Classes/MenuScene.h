#ifndef __Menu_SCENE_H__
#define __Menu_SCENE_H__

#include "cocos2d.h"
//�˵��������
class MenuScene : public cocos2d::Scene
{
public:
    //���캯��
    static cocos2d::Scene* createScene();//�̳д�������
    virtual bool init();
    CREATE_FUNC(MenuScene);
    //�ر���Ϸ
    void close_game(Ref* pSender);
    //ȥ���ý���
    void goto_options(Ref* pSender);
    //ȥ��������
    void goto_helper(Ref* pSender);
    //ȥð��ģʽ
    void goto_adventure(Ref* psender);
    //ȥbossģʽ
    void goto_boss(Ref* psender);
    //ȥ������
    void goto_nest(Ref* psender);
};

#endif // __Menu_SCENE_H__
