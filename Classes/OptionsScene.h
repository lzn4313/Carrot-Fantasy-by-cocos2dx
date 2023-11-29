#ifndef __Options_SCENE_H__
#define __Options_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class OptionsScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//继承创建场景

    virtual bool init();

    CREATE_FUNC(OptionsScene);

    virtual void goto_menu(Ref* psender);

    virtual void goto_set(Ref* psender);

    virtual void goto_statistics(Ref* psender);

    virtual void goto_person(Ref* psender);
};

class SetLayer :public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer();//继承创建场景

    virtual bool init();

    CREATE_FUNC(SetLayer);

    virtual void close_sound(Ref* psender);

    virtual void close_bgmusic(Ref* psender);

    virtual void reset_game(Ref* psender);
};

class StatisticsLayer :public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer();//继承创建场景

    virtual bool init();

    CREATE_FUNC(StatisticsLayer);
};

class PersonLayer :public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer();//继承创建场景

    virtual bool init();

    CREATE_FUNC(PersonLayer);
};
#endif // __Options_SCENE_H__
