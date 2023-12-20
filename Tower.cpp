#include "Tower.h"
#include <string>
USING_NS_CC;
using namespace cocos2d::ui;

int Tower::get_now_money(int tag) {
	
}

void Tower::build_tower(pos position, int tag, cocos2d::Layer* this_layer) {
	string str[4] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" };
	name_tag;//记录名称标签
	value;//记录当前价值
	attack;//记录单次攻击力
	attack_speed;//记录攻击速度
	attack_range;//记录攻击范围
	attack_special;//记录特殊攻击效果（穿透、减速、分裂等）
	level;//记录等级
}

int getMoney(int tag) {
	return Tower_Value[tag - 1];
}