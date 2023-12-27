#include "Tower.h"
#include"sound&music.h"
#include <string>
#include <cmath>
USING_NS_CC;
using namespace cocos2d::ui;

extern Tower_information tower_map[7][12];
extern int if_speed_up;
extern int if_pause;

/*建造炮台*/
void Tower::build_tower(pos position, int tag, cocos2d::Layer* this_layer)
{
	build_sound_effect();

	string str[5] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" ,"/Tower/Build/" };
	vec2 vec = trans_ij_to_xy(position);

	Tower_information tower(tag, Tower_Value[tag - 1], Tower_Attack[tag - 1], Tower_Attack_Speed[tag - 1], 1, tag - 1, 1);
	tower.tower_base = Sprite::create();
	tower.tower_body = Sprite::create();

	switch (tag) {
		case 1:
			tower.tower_base->setTexture(str[tag - 1] + "ID1_11.PNG");
			tower.tower_body->setTexture(str[tag - 1] + "ID1_22.PNG");
			tower.tower_body->setRotation(-90);
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
			tower.tower_body->setTexture(str[tag - 1] + "ID3_99.PNG");
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

	//利用帧动画完成建造特效
	auto Effect = Sprite::create();
	Vector<SpriteFrame*> frame;
	frame.pushBack(SpriteFrame::create(str[4] + "Items02-hd_1.PNG", Rect(0, 0, 161, 133)));
	frame.pushBack(SpriteFrame::create(str[4] + "Items02-hd_2.PNG", Rect(0, 0, 169, 175)));
	frame.pushBack(SpriteFrame::create(str[4] + "Items02-hd_3.PNG", Rect(0, 0, 199, 224)));
	frame.pushBack(SpriteFrame::create(str[4] + "Items02-hd_4.PNG", Rect(0, 0, 242, 243)));
	auto remove_effect = CallFunc::create([=]() {
		this_layer->removeChild(Effect);
		});
	Effect->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.05)), remove_effect, nullptr));
	Effect->setPosition(vec.x, vec.y);
	this_layer->addChild(Effect);

	Vec2 Start = { vec.x,vec.y };
	Vec2 End = { vec.x + 200,vec.y + 200 };
	attack_once(tower, Start, End, this_layer);
	//bullet_fly(tower, Start, End, this_layer);
}

/*升级炮台*/
void Tower::up_level_tower(pos position, cocos2d::Layer* this_layer)
{
	uplevel_sound_effect();

	/*删掉旧炮台*/
	this_layer->removeChild(tower_map[position.i][position.j].tower_base);
	this_layer->removeChild(tower_map[position.i][position.j].tower_body);

	string str[4] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" };

	if (tower_map[position.i][position.j].level < Max_Level) {
		/*更新基本信息*/
		tower_map[position.i][position.j].value += get_level_up_money(position);
		tower_map[position.i][position.j].level++;
		tower_map[position.i][position.j].attack *= 2;
		tower_map[position.i][position.j].attack_range++;
		tower_map[position.i][position.j].attack_speed *= 1.5;

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

		Vec2 Start = { vec.x,vec.y };
		Vec2 End = { vec.x + 200,vec.y + 200 };
		attack_once(tower_map[position.i][position.j], Start, End, this_layer);
	}

}

/*出售炮台*/
void Tower::sell_tower(pos position, cocos2d::Layer* this_layer)
{
	sell_sound_effect();

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

	//利用帧动画完成删除特效
	vec2 vec = trans_ij_to_xy(position);
	auto Effect = Sprite::create();
	Vector<SpriteFrame*> frame;
	frame.pushBack(SpriteFrame::create("/Tower/Build/Items02-hd_1.PNG", Rect(0, 0, 161, 133)));
	frame.pushBack(SpriteFrame::create("/Tower/Build/Items02-hd_2.PNG", Rect(0, 0, 169, 175)));
	frame.pushBack(SpriteFrame::create("/Tower/Build/Items02-hd_3.PNG", Rect(0, 0, 199, 224)));
	frame.pushBack(SpriteFrame::create("/Tower/Build/Items02-hd_4.PNG", Rect(0, 0, 242, 243)));
	Effect->setPosition(vec.x, vec.y);
	this_layer->addChild(Effect);
	auto remove_effect = CallFunc::create([=]() {
		this_layer->removeChild(Effect);
		});
	Effect->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.05)), remove_effect, nullptr));
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
	if (tower_map[position.i][position.j].name_tag == Tower_Bottle)
		return (100 + tower_map[position.i][position.j].level * 80);
	else
		return(tower_map[position.i][position.j].level == 1 ? 220 : 260);
}

/*获得初始建造金币*/
int getMoney(int tag) {
	return Tower_Value[tag - 1];
}

/*子弹飞行动画*/
void Tower::bullet_fly(Tower_information tower, cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Layer* this_layer)
{
	float dx, dy, r;
	dx = end.x - start.x;
	dy = end.y - start.y;
	r = -atan2f(dy, dx) / 3.14159 * 180;
	string str[4] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" };

	auto bullet = Sprite::create();
	switch (tower.level)
	{
		case 1:
			bullet->setTexture(str[tower.name_tag - 1] + "bullet1.PNG");
			break;
		case 2:
			bullet->setTexture(str[tower.name_tag - 1] + "bullet2.PNG");
			break;
		case 3:
			bullet->setTexture(str[tower.name_tag - 1] + "bullet3.PNG");
			break;
		default:
			break;
	}
	bullet->setPosition(start);

	auto remove_bullet = CallFunc::create([=]() {
		this_layer->removeChild(bullet);
		});

	if (tower.name_tag == Tower_Bottle || tower.name_tag == Tower_Shit) {
		bullet->setRotation(r);
		//auto bullet_move_to = cocos2d::MoveTo::create(if_speed_up == 0 ? 0.33 : 0.33 / 2, end);
		auto bullet_move_to = cocos2d::MoveTo::create(if_speed_up == 0 ? 3 : 0.33 / 2, end);
		bullet->runAction(Sequence::create(bullet_move_to, DelayTime::create(0), remove_bullet, DelayTime::create(0), nullptr));
	}
	else if (tower.name_tag == Tower_Star || tower.name_tag == Tower_Fan) {
		auto bullet_move_to = cocos2d::MoveTo::create(if_speed_up == 0 ? 1.5 : 1.5 / 2, end);
		auto rotate = Spawn::create(bullet_move_to, Repeat::create(RotateBy::create(if_speed_up == 0 ? 0.5 : 0.5 / 2, 360), 3), nullptr);
		bullet->runAction(Sequence::create(rotate, DelayTime::create(0), remove_bullet, DelayTime::create(0), nullptr));
	}

	this_layer->addChild(bullet);
}

/*单次攻击动画*/
void Tower::attack_once(Tower_information tower, cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Layer* this_layer)
{
	float dx, dy, r;
	dx = end.x - start.x;
	dy = end.y - start.y;
	r = -atan2f(dy, dx) / 3.14159 * 180;
	string str[4] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" };

	if (tower.name_tag == Tower_Bottle ) {
		//利用帧动画完成攻击动画
		auto atk_Effect = Sprite::create();
		Vector<SpriteFrame*> frame;
		switch (tower.level) {
			case 1:
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID1_18.PNG", Rect(0, 0, 62, 24)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID1_13.PNG", Rect(0, 0, 62, 27)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID1_22.PNG", Rect(0, 0, 56, 25)));
				break;
			case 2:
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID1_8.PNG", Rect(0, 0, 69, 32)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID1_12.PNG", Rect(0, 0, 67, 40)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID1_15.PNG", Rect(0, 0, 63, 35)));
				break;
			case 3:
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID1_6.PNG", Rect(0, 0, 76, 43)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID1_3.PNG", Rect(0, 0, 72, 48)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID1_5.PNG", Rect(0, 0, 70, 46)));
				break;
			default:
				break;
		}
		atk_Effect->setRotation(r);
		atk_Effect->setPosition(start.x, start.y);
		this_layer->addChild(atk_Effect);
		auto hide_body = CallFunc::create([=]() {
			tower.tower_body->setVisible(0);
			});
		auto unhide_body = CallFunc::create([=]() {
			tower.tower_body->setVisible(1);
			});
		auto remove_atk_Effect= CallFunc::create([=]() {
			atk_Effect->removeFromParent();
			});
		atk_Effect->runAction(Sequence::create(
			hide_body, Animate::create(Animation::createWithSpriteFrames(frame, 0.11)), unhide_body, remove_atk_Effect, nullptr));
		bullet_fly(tower, start, end, this_layer);

	}
	else if (tower.name_tag == Tower_Shit) {
		//auto seq = Sequence::create(
			//hide_body, Animate::create(Animation::createWithSpriteFrames(frame, 0.11)), nullptr);
	}
}