#include"Tower.h"
#include"sound&music.h"
#include"enemy.h"
#include <string>
#include <cmath>
USING_NS_CC;
using namespace cocos2d::ui;

extern Tower_information tower_map[7][12];
extern int if_speed_up;
extern int if_pause;
extern int carrot_hp;
extern vector<Enemy*> monster;

Sprite* Tower_body::createSprite()
{
	return Tower_body::create();
}

bool Tower_body::init()
{
	if (!Sprite::init())
		return false;
	this->scheduleUpdate();
	return true;
}

/*重写update函数*/
void Tower_body::update(float dt)
{
	static float time = 0;
	time += dt;
	/*****************************************
	*********************
	************
	*********
	********
	*****调试*/

	Vec2 my_position = tower.tower_body->getPosition();
	Vec2 enemy_position;
	Sprite* target;
	for (Enemy* enemy : monster) {
		enemy_position = enemy->getPosition();
		if (((my_position.x - enemy_position.x) * (my_position.x - enemy_position.x) +
			(my_position.y - enemy_position.y) * (my_position.y - enemy_position.y))
			<= (tower.attack_range * 80) * (tower.attack_range * 80))
		{
			target = enemy;
			break;
		}
	}
	if (time >= (4 / tower.attack_speed)) {
		time = 0;
		Node* this_layer = tower.tower_body->getParent();
		Layer* ThisLayer = static_cast<Layer*>(this_layer);
		attack_once(tower, my_position, enemy_position, ThisLayer);
	}
	/*****************************************
	*********************
	************
	*********
	********
	*****调试*/
		



	/*****************************************
	*********************
	************
	*********
	********
	*****调试
	static bool carr = 1;
	if (carrot_hp == 9 && carr == 1) {
		//利用帧动画完成建造特效
		Node* this_layer = tower.tower_body->getParent();
		Layer* ThisLayer = static_cast<Layer*>(this_layer);
		auto Effect = Sprite::create();
		Vector<SpriteFrame*> frame;
		Vec2 vec = tower.tower_body->getPosition();
		frame.pushBack(SpriteFrame::create("/Tower/Build/Items02-hd_1.PNG", Rect(0, 0, 161, 133)));
		frame.pushBack(SpriteFrame::create("/Tower/Build/Items02-hd_2.PNG", Rect(0, 0, 169, 175)));
		frame.pushBack(SpriteFrame::create("/Tower/Build/Items02-hd_3.PNG", Rect(0, 0, 199, 224)));
		frame.pushBack(SpriteFrame::create("/Tower/Build/Items02-hd_4.PNG", Rect(0, 0, 242, 243)));
		auto remove_effect = CallFunc::create([=]() {
			ThisLayer->removeChild(Effect);
			});
		Effect->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.05)), remove_effect, nullptr));
		Effect->setPosition(vec.x, vec.y);
		ThisLayer->addChild(Effect);
		carr = 0;
	}
	/*****************************************
	*********************
	************
	*********
	********
	*****调试*/
}

/*建造炮台*/
void Tower::build_tower(pos position, int tag, cocos2d::Layer* this_layer)
{
	if (tag <= 4) {
		build_sound_effect();

		string str[5] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" ,"/Tower/Build/" };
		vec2 vec = trans_ij_to_xy(position);

		Tower = { tag, Tower_Value[tag - 1], Tower_Attack[tag - 1], Tower_Attack_Speed[tag - 1], 1, tag - 1, 1 };
		Tower.tower_base = Sprite::create();
		Tower.tower_body = Tower_body::create();

		switch (tag) {
			case 1:
				Tower.tower_base->setTexture(str[tag - 1] + "ID1_11.PNG");
				Tower.tower_body->setTexture(str[tag - 1] + "ID1_22.PNG");
				Tower.tower_body->setRotation(-90);
				break;
			case 2:
				Tower.tower_base->setTexture(str[tag - 1] + "ID2_29.PNG");
				Tower.tower_body->setTexture(str[tag - 1] + "ID2_4.PNG");
				break;
			case 3:
				Tower.tower_base->setTexture(str[tag - 1] + "ID4_0.PNG");
				Tower.tower_body->setTexture(str[tag - 1] + "ID4_16.PNG");
				break;
			case 4:
				Tower.tower_base->setTexture(str[tag - 1] + "ID3_56.PNG");
				Tower.tower_body->setTexture(str[tag - 1] + "ID3_99.PNG");
				Tower.tower_body->setRotation(0);
				break;
			default:
				break;
		}

		Tower.tower_base->setPosition(vec.x, vec.y);
		this_layer->addChild(Tower.tower_base);
		Tower.tower_body->setPosition(vec.x, vec.y);
		this_layer->addChild(Tower.tower_body);
		tower_map[position.i][position.j] = Tower;
		Tower.tower_body->tower = Tower;

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
	}
}

/*升级炮台*/
void Tower::up_level_tower(pos position, cocos2d::Layer* this_layer)
{
	uplevel_sound_effect();

	if (tower_map[position.i][position.j].level < Max_Level) {
		vec2 vec = trans_ij_to_xy(position);
		if (tower_map[position.i][position.j].name_tag != CARROT) {
			/*删掉旧炮台*/
			this_layer->removeChild(tower_map[position.i][position.j].tower_base);
			this_layer->removeChild(tower_map[position.i][position.j].tower_body);

			string str[4] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" };

			/*更新基本信息*/
			tower_map[position.i][position.j].value += get_level_up_money(position);
			tower_map[position.i][position.j].level++;
			tower_map[position.i][position.j].attack *= 2;
			tower_map[position.i][position.j].attack_range += 0.5;
			tower_map[position.i][position.j].attack_speed *= 1.5;

			tower_map[position.i][position.j].tower_base = Sprite::create();
			tower_map[position.i][position.j].tower_body = Tower_body::create();

			Tower = tower_map[position.i][position.j];

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

			tower_map[position.i][position.j].tower_base->setPosition(vec.x, vec.y);
			tower_map[position.i][position.j].tower_body->setPosition(vec.x, vec.y);

			this_layer->addChild(tower_map[position.i][position.j].tower_base);
			this_layer->addChild(tower_map[position.i][position.j].tower_body);
		}
		else {
			tower_map[position.i][position.j].level++;
			carrot_hp += 2;
		}
		//利用帧动画完成升级特效
		auto Effect_1 = Sprite::create();
		Vector<SpriteFrame*> frame;
		frame.pushBack(SpriteFrame::create("/Tower/Build/up1.png", Rect(0, 0, 77, 62)));
		frame.pushBack(SpriteFrame::create("/Tower/Build/up2.png", Rect(0, 0, 86, 69)));
		frame.pushBack(SpriteFrame::create("/Tower/Build/up3.png", Rect(0, 0, 95, 69)));
		frame.pushBack(SpriteFrame::create("/Tower/Build/up4.png", Rect(0, 0, 120, 80)));
		Effect_1->setScale(2);
		auto remove_effect_1 = CallFunc::create([=]() {
			this_layer->removeChild(Effect_1);
			});
		Effect_1->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.05)), remove_effect_1, nullptr));
		Effect_1->setPosition(vec.x, vec.y);
		this_layer->addChild(Effect_1, -1);

		auto Effect_2 = Sprite::create();
		Effect_2->setPosition(vec.x, vec.y);
		Effect_2->setTexture("/Tower/Build/up5.png");
		auto effect_move = cocos2d::MoveTo::create(0.2, Vec2{ vec.x,vec.y + 300 });
		Effect_2->setScale(2);
		auto remove_effect_2 = CallFunc::create([=]() {
			this_layer->removeChild(Effect_2);
			});
		Effect_2->runAction(Sequence::create(effect_move, remove_effect_2, nullptr));
		this_layer->addChild(Effect_2);
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

	Tower = tower_map[position.i][position.j];

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
	else if (tower_map[position.i][position.j].name_tag == CARROT)
		return (tower_map[position.i][position.j].level == 1 ? 500 : 1000);
	else
		return (tower_map[position.i][position.j].level == 1 ? 220 : 260);
}

/*获得初始建造金币*/
int getMoney(int tag) {
	return Tower_Value[tag - 1];
}

/*子弹飞行动画*/
void Tower_body::bullet_fly(Tower_information tower, cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Layer* this_layer)
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
		auto bullet_move_to = cocos2d::MoveTo::create(if_speed_up == 0 ? 0.33 : 0.33 / 2, end);
		//auto bullet_move_to = cocos2d::MoveTo::create(if_speed_up == 0 ? 3 : 0.33 / 2, end);
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
void Tower_body::attack_once(Tower_information tower, cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Layer* this_layer)
{
	float dx, dy, r;
	dx = end.x - start.x;
	dy = end.y - start.y;
	r = -atan2f(dy, dx) / 3.14159 * 180;
	string str[4] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" };

	if (tower.name_tag == Tower_Bottle ) {
		tower.tower_body->setRotation(r);
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
		//利用帧动画完成攻击动画
		auto atk_Effect = Sprite::create();
		Vector<SpriteFrame*> frame;
		switch (tower.level) {
			case 1:
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID2_5.PNG", Rect(0, 0, 43,46)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID2_28.PNG", Rect(0, 0, 55, 46)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID2_4.PNG", Rect(0, 0, 47, 41)));
				break;
			case 2:
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID2_37.PNG", Rect(0, 0, 48, 60)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID2_23.PNG", Rect(0, 0, 59, 57)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID2_21.PNG", Rect(0, 0, 52, 53)));
				break;
			case 3:
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID2_19.PNG", Rect(0, 0, 56, 68)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID2_14.PNG", Rect(0, 0, 70, 66)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID2_22.PNG", Rect(0, 0, 61, 65)));
				break;
			default:
				break;
		}
		atk_Effect->setPosition(start.x, start.y);
		this_layer->addChild(atk_Effect);
		auto hide_body = CallFunc::create([=]() {
			tower.tower_body->setVisible(0);
			});
		auto unhide_body = CallFunc::create([=]() {
			tower.tower_body->setVisible(1);
			});
		auto remove_atk_Effect = CallFunc::create([=]() {
			atk_Effect->removeFromParent();
			});
		atk_Effect->runAction(Sequence::create(
			hide_body, Animate::create(Animation::createWithSpriteFrames(frame, 0.11)), unhide_body, remove_atk_Effect, nullptr));
		bullet_fly(tower, start, end, this_layer);
	}
	else if (tower.name_tag == Tower_Fan) {
		//利用帧动画完成攻击动画
		auto atk_Effect = Sprite::create();
		Vector<SpriteFrame*> frame;
		switch (tower.level) {
			case 1:
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "atk11.PNG", Rect(0, 0, 59, 59)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "atk12.PNG", Rect(0, 0, 61, 58)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID4_16.PNG", Rect(0, 0, 53, 54)));
				break;
			case 2:
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "atk21.PNG", Rect(0, 0, 60, 60)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "atk22.PNG", Rect(0, 0, 70, 69)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID4_8.PNG", Rect(0, 0, 57, 56)));
				break;
			case 3:
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "atk32.PNG", Rect(0, 0, 72, 73)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "atk32.PNG", Rect(0, 0, 73, 74)));
				frame.pushBack(SpriteFrame::create(str[tower.name_tag - 1] + "ID4_11.PNG", Rect(0, 0, 68, 70)));
				break;
			default:
				break;
		}
		atk_Effect->setPosition(start.x, start.y);
		this_layer->addChild(atk_Effect);
		auto hide_body = CallFunc::create([=]() {
			tower.tower_body->setVisible(0);
			});
		auto unhide_body = CallFunc::create([=]() {
			tower.tower_body->setVisible(1);
			});
		auto remove_atk_Effect = CallFunc::create([=]() {
			atk_Effect->removeFromParent();
			});
		atk_Effect->runAction(Sequence::create(
			hide_body, Animate::create(Animation::createWithSpriteFrames(frame, 0.11)), unhide_body, remove_atk_Effect, nullptr));
		bullet_fly(tower, start, end, this_layer);
	}
}
