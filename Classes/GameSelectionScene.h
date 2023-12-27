#ifndef __GameSelection_SCENE_H__
#define __GameSelection_SCENE_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
using namespace cocos2d::ui;
//ð��ģʽѡ�ؽ�����
class GameSelectionScene : public cocos2d::Scene
{
public:
    //���캯��
    static cocos2d::Scene* createScene();//�̳д�������
    virtual bool init();
    CREATE_FUNC(GameSelectionScene);
};
//ѡ��ؽ���
class BigLevelLayer : public cocos2d::Layer {
public:
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(BigLevelLayer);
    //���������㣨��������ҳ��
    void create_slide_layer();
    //ȥð��ģʽ
    void goto_evaluate(Ref* psender);
    //�԰�ť��ʽ����ҳ
    void page_left(Ref* psender);
    //�԰�ť��ʽ���ҷ�ҳ
    void page_right(Ref* psender);
    //ȥ���ѡС��
    void goto_level_1(Ref* psender);
    //ȥ����ѡС��
    void goto_level_2(Ref* psender);
    //ȥɳĮѡС��
    void goto_level_3(Ref* psender);
};
//ѡ���С�ؽ���
class Level_1_Layer :public cocos2d::Layer
{
public:
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(Level_1_Layer);
    //���������㣨��������ҳ��
    void create_slide_layer();
    //����ѡ��ؽ���
    void return_to_biglevel(Ref* psender);
    //ѡ���1С��
    void level_1_1(Ref* psender, Widget::TouchEventType type);
    //ѡ���2С��
    void level_1_2(Ref* psender, Widget::TouchEventType type);
    //ѡ���3С��
    void level_1_3(Ref* psender, Widget::TouchEventType type);
    //ѡ���4С��
    void level_1_4(Ref* psender, Widget::TouchEventType type);
    //ѡ���5С��
    void level_1_5(Ref* psender, Widget::TouchEventType type);
};
#endif // __GameSelection_SCENE_H__
