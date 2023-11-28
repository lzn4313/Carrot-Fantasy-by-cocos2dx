#ifndef __Options_SCENE_H__
#define __Options_SCENE_H__

#include "cocos2d.h"

class OptionsScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//¼Ì³Ð´´½¨³¡¾°

    virtual bool init();

    virtual void goto_menu(Ref* psender);

    virtual void goto_set(Ref* psender);

    virtual void goto_statistics(Ref* psender);

    virtual void goto_person(Ref* psender);

    virtual void close_sound(Ref* psender);

    virtual void close_bgmusic(Ref* psender);

    virtual void reset_game(Ref* psender);

    CREATE_FUNC(OptionsScene);
};
#endif // __Options_SCENE_H__
