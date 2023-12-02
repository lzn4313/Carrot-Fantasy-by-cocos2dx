#ifndef __Options_SCENE_H__
#define __Options_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
//设置界面
class OptionsScene : public cocos2d::Scene
{
public:
    //构造函数
    static cocos2d::Scene* createScene();//继承创建场景
    virtual bool init();
    CREATE_FUNC(OptionsScene);
    //去主菜单
    void goto_menu(Ref* psender);
    //去设置选项页
    void goto_set(Ref* psender, Widget::TouchEventType type);
    //去统计选项页
    void goto_statistics(Ref* psender, Widget::TouchEventType type);
    //去人员选项页
    void goto_person(Ref* psender, Widget::TouchEventType type);
};
//设置界面的设置选项页
class SetLayer :public cocos2d::Layer
{
public:
    //构造函数
    static cocos2d::Layer* createLayer();//继承创建场景
    virtual bool init();
    CREATE_FUNC(SetLayer);
    //关闭音效
    virtual void close_sound(Ref* psender);
    //关闭bgm
    virtual void close_bgmusic(Ref* psender);
    //重置游戏存档数据
    virtual void reset_game(Ref* psender);
};
//设置界面的统计选项页
class StatisticsLayer :public cocos2d::Layer
{
public:
    //构造函数
    static cocos2d::Layer* createLayer();//继承创建场景
    virtual bool init();
    CREATE_FUNC(StatisticsLayer);
};
//设置界面的人员选项页
class PersonLayer :public cocos2d::Layer
{
public:
    //构造函数
    static cocos2d::Layer* createLayer();//继承创建场景
    virtual bool init();
    CREATE_FUNC(PersonLayer);
};
#endif // __Options_SCENE_H__
