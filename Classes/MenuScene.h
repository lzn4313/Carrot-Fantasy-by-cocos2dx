#ifndef __Menu_SCENE_H__
#define __Menu_SCENE_H__

#include "cocos2d.h"
//菜单界面大类
class MenuScene : public cocos2d::Scene
{
public:
    //构造函数
    static cocos2d::Scene* createScene();//继承创建场景
    virtual bool init();
    CREATE_FUNC(MenuScene);
    //关闭游戏
    void close_game(Ref* pSender);
    //去设置界面
    void goto_options(Ref* pSender);
    //去帮助界面
    void goto_helper(Ref* pSender);
    //去冒险模式
    void goto_adventure(Ref* psender);
    //去boss模式
    void goto_boss(Ref* psender);
    //去怪物窝
    void goto_nest(Ref* psender);
};

#endif // __Menu_SCENE_H__
