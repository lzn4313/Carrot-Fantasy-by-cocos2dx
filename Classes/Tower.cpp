#include "Tower.h"
#include <string>
USING_NS_CC;
using namespace cocos2d::ui;

extern Tower_information tower_map[7][12];

/*建造炮台*/
void Tower::build_tower(pos position, int tag, cocos2d::Layer* this_layer)
{
	string str[4] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" };
	Tower_information tower(tag - 1, Tower_Value[tag - 1], Tower_Attack[tag - 1], Tower_Attack_Speed[tag - 1], 1, tag - 1, 1);
	vec2 vec = trans_ij_to_xy(position);
	tower.tower_base = Sprite::create();
	tower.tower_body = Sprite::create();
	tower.tower_base->setPosition(vec.x, vec.y);
	switch (tag) {
		case 1:
			tower.tower_base->setTexture(str[tag - 1] + "ID1_11.PNG");
			break;
		case 2:
			tower.tower_base->setTexture(str[tag - 1] + "ID2_29.PNG");
			break;
		case 3:
			tower.tower_base->setTexture(str[tag - 1] + "ID4_0.PNG");
			break;
		case 4:
			tower.tower_base->setTexture(str[tag - 1] + "ID3_56.PNG");
			break;
		default:
			break;
	}
	this_layer->addChild(tower.tower_base);
	tower.tower_body->setPosition(vec.x, vec.y);
	switch (tag) {
		case 1:
			tower.tower_body->setTexture(str[tag - 1] + "ID1_22.PNG");
			tower.tower_body->setRotation(0);
			break;
		case 2:
			tower.tower_body->setTexture(str[tag - 1] + "ID2_4.PNG");
			break;
		case 3:
			tower.tower_body->setTexture(str[tag - 1] + "ID4_16.PNG");
			break;
		case 4:
			tower.tower_body->setTexture(str[tag - 1] + "ID3_87.PNG");
			tower.tower_body->setRotation(0);
			break;
		default:
			break;
	}
	this_layer->addChild(tower.tower_body);
	tower_map[position.i][position.j] = tower;
}

/*升级炮台*/
void Tower::up_level_tower(pos position)
{
	if (tower_map[position.i][position.j].level < Max_Level) {
		tower_map[position.i][position.j].level++;

	}
}

/*出售炮台*/
void Tower::sell_tower(pos postion)
{

}

/*获得出售价格*/
int Tower::get_sell_money(pos position) 
{
	return int(tower_map[position.i][position.j].value * 0.8);
}

/*获得攻击范围*/
float Tower::get_attack_range(pos position)
{
	return tower_map[position.i][position.j].attack_range;
}

/*获得等级*/
int Tower::get_level(pos position)
{
	return tower_map[position.i][position.j].level;
}

/*获得升级所需金币*/
int Tower::get_level_up_money(pos position)
{
	return (tower_map[position.i][position.j].value + (tower_map[position.i][position.j].level) * 40);
}

/*获得初始建造金币*/
int getMoney(int tag) {
	return Tower_Value[tag - 1];
}