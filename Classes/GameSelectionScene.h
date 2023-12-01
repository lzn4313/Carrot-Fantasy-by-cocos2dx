#ifndef __GameSelection_SCENE_H__
#define __GameSelection_SCENE_H__

#include "cocos2d.h"

class GameSelectionScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//继承创建场景

    virtual bool init();

    CREATE_FUNC(GameSelectionScene);
};

class BigLevelLayer : public cocos2d::Layer {
public:
    static cocos2d::Layer* createLayer();//继承创建场景

    virtual bool init();

    CREATE_FUNC(BigLevelLayer);

    void create_slide_layer();

    void goto_evaluate(Ref* psender);

    void page_left(Ref* psender);

    void page_right(Ref* psender);

    void goto_level_1(Ref* psender);

    void goto_level_2(Ref* psender);

    void goto_level_3(Ref* psender);
};
#endif // __GameSelection_SCENE_H__
