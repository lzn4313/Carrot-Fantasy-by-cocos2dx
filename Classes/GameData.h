#pragma once
#include<string>
#include "cocos2d.h"
#include "sound&music.h"
using namespace std;
USING_NS_CC;
/*本游戏数据存储采用cocos自带的UserDefault进行存储，将会在保存地址生成对应的.xml文件，可以对数据进行获取和写入*/
//重置所有数据
static void reset_data() {
	UserDefault::getInstance()->setBoolForKey("have_init", true);
	UserDefault::getInstance()->setIntegerForKey("adventure_statistics", 1);
	UserDefault::getInstance()->setIntegerForKey("hide_statistics", 0);
	UserDefault::getInstance()->setIntegerForKey("bosspattern_statistics", 0);
	UserDefault::getInstance()->setIntegerForKey("money_statistics", 0);
	UserDefault::getInstance()->setIntegerForKey("monster_statistics", 0);
	UserDefault::getInstance()->setIntegerForKey("boss_statistics", 0);
	UserDefault::getInstance()->setIntegerForKey("damage_statistics", 0);
	UserDefault::getInstance()->setIntegerForKey("level_1", 1);
	UserDefault::getInstance()->setIntegerForKey("level_2", 0);
	UserDefault::getInstance()->setIntegerForKey("level_3", 0);
	UserDefault::getInstance()->setIntegerForKey("if_boss_lock", 1);
	UserDefault::getInstance()->setIntegerForKey("if_nest_lock", 1);
}
//初始化存档数据
static void init_data() {
	if (!UserDefault::getInstance()->getBoolForKey("have_init", false)) {
		//如果无存档，则重置存档数据，初始化声音数据；若有存档则不进行操作
		reset_data();
		init_sound();
	}
}