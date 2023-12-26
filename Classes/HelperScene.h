#ifndef __Helper_SCENE_H__
#define __Helper_SCENE_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
using namespace cocos2d::ui;
//��������Scene
class HelperScene : public cocos2d::Scene
{
public:
    //���캯��
    static cocos2d::Scene* createScene();//�̳д�������
    virtual bool init();
    CREATE_FUNC(HelperScene);
    //�������˵�
    virtual void goto_home(Ref* psender);
    //ȥ����ѡ�
    void goto_help(Ref* psender,Widget::TouchEventType type);
    //ȥ����ѡ�
    void goto_monster(Ref* psender, Widget::TouchEventType type);
    //ȥ������ѡ�
    void goto_tower(Ref* psender, Widget::TouchEventType type);
};
//����ѡ�
class HelpLayer : public cocos2d::Layer {
public:
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(HelpLayer);
};
//����ѡ�
class MonsterLayer :public cocos2d::Layer {
public:
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(MonsterLayer);
};
//������չʾѡ�
class TowerLayer :public cocos2d::Layer {
public:
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(TowerLayer);
};
#endif // __Helper_SCENE_H__
