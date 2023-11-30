#ifndef __Helper_SCENE_H__
#define __Helper_SCENE_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
using namespace cocos2d::ui;
class HelperScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//继承创建场景

    virtual bool init();

    virtual void goto_home(Ref* psender);

    void goto_help(Ref* psender,Widget::TouchEventType type);

    void goto_monster(Ref* psender, Widget::TouchEventType type);

    void goto_tower(Ref* psender, Widget::TouchEventType type);

    CREATE_FUNC(HelperScene);
};

class HelpLayer : public cocos2d::Layer {
public:
    static cocos2d::Layer* createLayer();//继承创建场景

    virtual bool init();

    CREATE_FUNC(HelpLayer);
};

class MonsterLayer :public cocos2d::Layer {
public:
    static cocos2d::Layer* createLayer();//继承创建场景

    virtual bool init();

    CREATE_FUNC(MonsterLayer);
};

class TowerLayer :public cocos2d::Layer {
public:
    static cocos2d::Layer* createLayer();//继承创建场景

    virtual bool init();

    CREATE_FUNC(TowerLayer);
};
#endif // __Helper_SCENE_H__
