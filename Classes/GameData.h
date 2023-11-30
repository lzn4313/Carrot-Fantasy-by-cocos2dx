#pragma once
#include<string>
#include<fstream>
#include "cocos2d.h"
#include "sound&music.h"
using namespace std;
USING_NS_CC;

static void reset_data() {
	UserDefault::getInstance()->setBoolForKey("have_init", true);
	UserDefault::getInstance()->setIntegerForKey("adventure_statistics", 0);
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

static void init_data() {
	if (!UserDefault::getInstance()->getBoolForKey("have_init", false)) {
		//�޴浵
		reset_data();
		init_sound();
	}
}