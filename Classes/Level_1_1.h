#ifndef __Level_1_1_LAYER_H__
#define __Level_1_1_LAYER_H__

#include "cocos2d.h"
#include "GameScene.h"
#include <vector>


class LevelPath {
public:
    pos point;
    char direction;
    pos*operator->() {
        return &point;
    }
};
extern std::vector<LevelPath> levelPath;//非cocos自带

//Level_1_1
class Level_1_1 : public cocos2d::Layer
{
public:
    //构造函数
    static cocos2d::Layer* createLayer();
    virtual bool init();
    
    CREATE_FUNC(Level_1_1);
};
#endif // __Level_1_1_LAYER_H__
