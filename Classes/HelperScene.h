#ifndef __Helper_SCENE_H__
#define __Helper_SCENE_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
using namespace cocos2d::ui;
//帮助界面Scene
class HelperScene : public cocos2d::Scene
{
public:
    //构造函数
    static cocos2d::Scene* createScene();//继承创建场景
    virtual bool init();
    CREATE_FUNC(HelperScene);
    //返回主菜单
    virtual void goto_home(Ref* psender);
    //去帮助选项卡
    void goto_help(Ref* psender,Widget::TouchEventType type);
    //去怪物选项卡
    void goto_monster(Ref* psender, Widget::TouchEventType type);
    //去防御塔选项卡
    void goto_tower(Ref* psender, Widget::TouchEventType type);
};
//帮助选项卡
class HelpLayer : public cocos2d::Layer {
public:
    //构造函数
    static cocos2d::Layer* createLayer();//继承创建场景
    virtual bool init();
    CREATE_FUNC(HelpLayer);
};
//怪物选项卡
class MonsterLayer :public cocos2d::Layer {
public:
    //构造函数
    static cocos2d::Layer* createLayer();//继承创建场景
    virtual bool init();
    CREATE_FUNC(MonsterLayer);
};
//防御塔展示选项卡
class TowerLayer :public cocos2d::Layer {
public:
    //构造函数
    static cocos2d::Layer* createLayer();//继承创建场景
    virtual bool init();
    CREATE_FUNC(TowerLayer);
};
#endif // __Helper_SCENE_H__
