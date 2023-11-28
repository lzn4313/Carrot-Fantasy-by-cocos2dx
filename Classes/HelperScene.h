#ifndef __Helper_SCENE_H__
#define __Helper_SCENE_H__

#include "cocos2d.h"

class HelperScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//¼Ì³Ð´´½¨³¡¾°

    virtual bool init();

    virtual void goto_home(Ref* psender);

    CREATE_FUNC(HelperScene);
};
#endif // __Helper_SCENE_H__
