#ifndef __Level_1_1_LAYER_H__
#define __Level_1_1_LAYER_H__

#include "cocos2d.h"
#include"GameScene.h"

struct LevelPath {
    pos point;
    char direction;
};

//Level_1_1
class Level_1_1 : public cocos2d::Layer
{
public:
    //¹¹Ôìº¯Êý
    static cocos2d::Layer* createLayer();
    virtual bool init();
    
    CREATE_FUNC(Level_1_1);
};
#endif // __Level_1_1_LAYER_H__
