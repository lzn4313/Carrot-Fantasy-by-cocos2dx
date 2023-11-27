#ifndef __Menu_SCENE_H__
#define __Menu_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//¼Ì³Ð´´½¨³¡¾°

    virtual bool init();

    virtual void update(float dt);
    
    void close_game(Ref* pSender);

    void goto_options(Ref* pSender);

    void goto_helper(Ref* pSender);

    void goto_adventure(Ref* psender);

    void goto_boss(Ref* psender);

    void goto_nest(Ref* psender);

    CREATE_FUNC(MenuScene);
};

#endif // __Menu_SCENE_H__
