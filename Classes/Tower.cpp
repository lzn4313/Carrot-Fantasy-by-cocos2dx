#include "Tower.h"
#include <string>
USING_NS_CC;
using namespace cocos2d::ui;

int Tower::get_now_money(int tag) {
	
}

void Tower::build_tower(pos position, int tag, cocos2d::Layer* this_layer) {
	string str[4] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" };
	name_tag;//��¼���Ʊ�ǩ
	value;//��¼��ǰ��ֵ
	attack;//��¼���ι�����
	attack_speed;//��¼�����ٶ�
	attack_range;//��¼������Χ
	attack_special;//��¼���⹥��Ч������͸�����١����ѵȣ�
	level;//��¼�ȼ�
}

int getMoney(int tag) {
	return Tower_Value[tag - 1];
}