#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__

#include "cocos2d.h"

#define EMPTY 0
#define DISABLED 1
#define TOWER 2
//工具函数
struct pos {
    int i;
    int j;
};
struct vec2 {
    float x;
    float y;
};
//把每个格点的数组坐标转换为世界坐标
static vec2 trans_ij_to_xy(pos position);
//把每个世界坐标转换成对应的格点的数组坐标
static pos trans_xy_to_ij(vec2 vec);
//冒险模式游戏类
class GameScene : public cocos2d::Scene
{
public:
    //构造函数
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
};
//游戏菜单类
class GameMenu :public cocos2d::Layer 
{
public:
    //构造函数
    static cocos2d::Layer* createLayer();
    virtual bool init();
    CREATE_FUNC(GameMenu);
    //选项
    void options();
    //开始
    void start();
    //建造
    void build(pos position, Vector<int> tower_available);
    //升级删除
    void tower_operations(pos position);
    //实时更新金币等数据
    virtual void update(float dt);
};
#endif // __Game_SCENE_H__
