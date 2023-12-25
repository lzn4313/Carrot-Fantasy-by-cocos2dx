#include "Tower.h"
#include <string>
USING_NS_CC;
using namespace cocos2d::ui;

extern Tower_information tower_map[7][12];

int Tower::get_now_money(int tag) {
	return 0;
}

/*建造炮台*/
void Tower::build_tower(pos position, int tag, cocos2d::Layer* this_layer) {
	string str[4] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" };
	tower = { tag - 1,Tower_Value[tag - 1],Tower_Attack[tag - 1],Tower_Attack_Speed[tag - 1],1,tag - 1,1 };
	tower_map[position.i][position.j] = tower;
	auto tower_base = Sprite::create();//炮台底座
	auto tower_body = Sprite::create();//炮台主体
	vec2 vec = trans_ij_to_xy(position);
	tower_base->setPosition(vec.x, vec.y);
	switch (tag) {
		case 1:
			tower_base->setTexture(str[tag - 1] + "ID1_11.PNG");
			break;
		case 2:
			tower_base->setTexture(str[tag - 1] + "ID2_29.PNG");
			break;
		case 3:
			tower_base->setTexture(str[tag - 1] + "ID4_0.PNG");
			break;
		case 4:
			tower_base->setTexture(str[tag - 1] + "ID3_56.PNG");
			break;
		default:
			break;
	}
	this_layer->addChild(tower_base);
	tower_body->setPosition(vec.x, vec.y);
	switch (tag) {
		case 1:
			tower_body->setTexture(str[tag - 1] + "ID1_22.PNG");
			tower_body->setRotation(0);
			break;
		case 2:
			tower_body->setTexture(str[tag - 1] + "ID2_4.PNG");
			break;
		case 3:
			tower_body->setTexture(str[tag - 1] + "ID4_16.PNG");
			break;
		case 4:
			tower_body->setTexture(str[tag - 1] + "ID3_87.PNG");
			tower_body->setRotation(0);
			break;
		default:
			break;
	}
	this_layer->addChild(tower_body);
}

int getMoney(int tag) {
	return Tower_Value[tag - 1];
}