#ifndef __Menu_SCENE_H__
#define __Menu_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//¼Ì³Ð´´½¨³¡¾°

    virtual bool init();

    CREATE_FUNC(MenuScene);
};

#endif // __Menu_SCENE_H__
