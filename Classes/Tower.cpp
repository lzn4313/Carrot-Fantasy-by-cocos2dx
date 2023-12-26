#include "Tower.h"
#include <string>
USING_NS_CC;
using namespace cocos2d::ui;

extern Tower_information tower_map[7][12];

/*建造炮台*/
void Tower::build_tower(pos position, int tag, cocos2d::Layer* this_layer)
{
	string str[5] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" ,"/Tower/Build/" };
	vec2 vec = trans_ij_to_xy(position);

	//利用帧动画完成建造特效
	auto Effect = Sprite::create();
	Vector<SpriteFrame*> frame;
	frame.pushBack(SpriteFrame::create(str[4] + "Items02-hd_1.PNG", Rect(0, 0, 40, 40)));
	frame.pushBack(SpriteFrame::create(str[4] + "Items02-hd_2.PNG", Rect(0, 0, 40, 40)));
	frame.pushBack(SpriteFrame::create(str[4] + "Items02-hd_3.PNG", Rect(0, 0, 40, 40)));
	frame.pushBack(SpriteFrame::create(str[4] + "Items02-hd_4.PNG", Rect(0, 0, 40, 40)));
	Effect->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.1)), FadeOut::create(0.1), nullptr));
	Effect->setPosition(vec.x, vec.y);
	this_layer->addChild(Effect);

	Tower_information tower(tag, Tower_Value[tag - 1], Tower_Attack[tag - 1], Tower_Attack_Speed[tag - 1], 1, tag - 1, 1);
	tower.tower_base = Sprite::create();
	tower.tower_body = Sprite::create();
	switch (tag) {
		case 1:
			tower.tower_base->setTexture(str[tag - 1] + "ID1_11.PNG");
			tower.tower_body->setTexture(str[tag - 1] + "ID1_22.PNG");
			tower.tower_body->setRotation(0);
			break;
		case 2:
			tower.tower_base->setTexture(str[tag - 1] + "ID2_29.PNG");
			tower.tower_body->setTexture(str[tag - 1] + "ID2_4.PNG");
			break;
		case 3:
			tower.tower_base->setTexture(str[tag - 1] + "ID4_0.PNG");
			tower.tower_body->setTexture(str[tag - 1] + "ID4_16.PNG");
			break;
		case 4:
			tower.tower_base->setTexture(str[tag - 1] + "ID3_56.PNG");
			tower.tower_body->setTexture(str[tag - 1] + "ID3_97.PNG");
			tower.tower_body->setRotation(0);
			break;
		default:
			break;
	}
	tower.tower_base->setPosition(vec.x, vec.y);
	this_layer->addChild(tower.tower_base);
	tower.tower_body->setPosition(vec.x, vec.y);
	this_layer->addChild(tower.tower_body);
	tower_map[position.i][position.j] = tower;
}

/*升级炮台*/
void Tower::up_level_tower(pos position, cocos2d::Layer* this_layer)
{
	/*删掉旧炮台*/
	this_layer->removeChild(tower_map[position.i][position.j].tower_base);
	this_layer->removeChild(tower_map[position.i][position.j].tower_body);

	string str[4] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" };
	
	if (tower_map[position.i][position.j].level < Max_Level) {
		/*更新基本信息*/
		tower_map[position.i][position.j].level++;
		tower_map[position.i][position.j].attack *= 2;
		tower_map[position.i][position.j].attack_range++;
		tower_map[position.i][position.j].attack_speed *= 1.5;
		tower_map[position.i][position.j].value += get_level_up_money(position);

		tower_map[position.i][position.j].tower_base = Sprite::create();
		tower_map[position.i][position.j].tower_body = Sprite::create();

		/*更新画面*/
		switch (tower_map[position.i][position.j].name_tag) {
			case 1:
				tower_map[position.i][position.j].tower_base->setTexture(str[tower_map[position.i][position.j].name_tag - 1] + "ID1_11.PNG");
				if (tower_map[position.i][position.j].level == 2) {
					tower_map[position.i][position.j].tower_body->setTexture(str[tower_map[position.i][position.j].name_tag - 1] + "ID1_15.PNG");
				}
				else if (tower_map[position.i][position.j].level == 3) {
					tower_map[position.i][position.j].tower_body->setTexture(str[tower_map[position.i][position.j].name_tag - 1] + "ID1_5.PNG");
				}
				tower_map[position.i][position.j].tower_body->setRotation(-90);
				break;
			case 2:
				if (tower_map[position.i][position.j].level == 2) {
					tower_map[position.i][position.j].tower_base->setTexture(str[tower_map[position.i][position.j].name_tag - 1] + "ID2_9.PNG");
					tower_map[position.i][position.j].tower_body->setTexture(str[tower_map[position.i][position.j].name_tag - 1] + "ID2_21.PNG");
				}
				else if (tower_map[position.i][position.j].level == 3) {
					tower_map[position.i][position.j].tower_base->setTexture(str[tower_map[position.i][position.j].name_tag - 1] + "ID2_7.PNG");
					tower_map[position.i][position.j].tower_body->setTexture(str[tower_map[position.i][position.j].name_tag - 1] + "ID2_22.PNG");
				}
				break;
			case 3:
				if (tower_map[position.i][position.j].level == 2) {
					tower_map[position.i][position.j].tower_base->setTexture(str[tower_map[position.i][position.j].name_tag - 1] + "ID4_1.PNG");
					tower_map[position.i][position.j].tower_body->setTexture(str[tower_map[position.i][position.j].name_tag - 1] + "ID4_8.PNG");
				}
				else if (tower_map[position.i][position.j].level == 3) {
					tower_map[position.i][position.j].tower_base->setTexture(str[tower_map[position.i][position.j].name_tag - 1] + "ID4_2.PNG");
					tower_map[position.i][position.j].tower_body->setTexture(str[tower_map[position.i][position.j].name_tag - 1] + "ID4_11.PNG");
				}
				break;
			case 4:
				if (tower_map[position.i][position.j].level == 2) {
					tower_map[position.i][position.j].tower_base->setTexture(str[tower_map[position.i][position.j].name_tag - 1] + "ID3_56.PNG");
					tower_map[position.i][position.j].tower_body->setTexture(str[tower_map[position.i][position.j].name_tag - 1] + "ID3_98.PNG");
				}
				else if (tower_map[position.i][position.j].level == 3) {
					tower_map[position.i][position.j].tower_base->setTexture(str[tower_map[position.i][position.j].name_tag - 1] + "ID3_84.PNG");
					tower_map[position.i][position.j].tower_body->setTexture(str[tower_map[position.i][position.j].name_tag - 1] + "ID3_46.PNG");
				}
				tower_map[position.i][position.j].tower_body->setRotation(0);
				break;
			default:
				break;
		}

		vec2 vec = trans_ij_to_xy(position);
		tower_map[position.i][position.j].tower_base->setPosition(vec.x, vec.y);
		tower_map[position.i][position.j].tower_body->setPosition(vec.x, vec.y);

		this_layer->addChild(tower_map[position.i][position.j].tower_base);
		this_layer->addChild(tower_map[position.i][position.j].tower_body);
	}

}

/*出售炮台*/
void Tower::sell_tower(pos position, cocos2d::Layer* this_layer)
{
	/*重置基本信息*/
	tower_map[position.i][position.j].name_tag = 0;
	tower_map[position.i][position.j].attack_special = 0;
	tower_map[position.i][position.j].level = 1;
	tower_map[position.i][position.j].attack =0;
	tower_map[position.i][position.j].attack_range=1;
	tower_map[position.i][position.j].attack_speed =0;
	tower_map[position.i][position.j].value =0;

	this_layer->removeChild(tower_map[position.i][position.j].tower_base);
	this_layer->removeChild(tower_map[position.i][position.j].tower_body);

	tower_map[position.i][position.j].tower_base = nullptr;
	tower_map[position.i][position.j].tower_body = nullptr;
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