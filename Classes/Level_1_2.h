#ifndef __Level_1_2_LAYER_H__
#define __Level_1_2_LAYER_H__

#include "cocos2d.h"

//Level_1_2
class Level_1_2 : public cocos2d::Layer
{
public:
    //¹¹Ôìº¯Êý
    static cocos2d::Layer* createLayer();
    virtual bool init();

    CREATE_FUNC(Level_1_2);
};
#endif // __Level_1_2_LAYER_H__
