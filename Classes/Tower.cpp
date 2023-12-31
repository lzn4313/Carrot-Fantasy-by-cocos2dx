#include"Tower.h"
#include"sound&music.h"
#include"enemy.h"
#include <string>
#include <cmath>
USING_NS_CC;
using namespace cocos2d::ui;

extern Tower* tower_map[7][12];//记录地图上的炮台信息
extern char game_map[7][12];//辅助地图数组
extern int if_speed_up;//是否加速
extern int if_pause;//是否暂停
extern int carrot_hp;//记录萝卜血量
extern int carrot_level;//记录萝卜等级
extern pos carrot_position;//记录萝卜位置
extern vector<Enemy*> monster;//储存怪物

/*
Sprite* Bullet::createSprite()
{
	return Bullet::create();
}

bool Bullet::init()
{
	if (!Sprite::init())
		return false;
	this->scheduleUpdate();
	return true;
}

void Bullet::update(float dt)
{
	if (if_pause == 0) {
		if (Target != nullptr && Farther != nullptr) {
			float x, y, r;
			x = Target->getPositionX() - this->getPositionX();
			y = Target->getPositionY() - this->getPositionY();
			r = -atan2f(y, x) / 3.14159 * 180;
			/*中心距离小于等于目标大小，视为击中
			((this->getPosition().x - Target->getPosition().x) * (this->getPosition().x - Target->getPosition().x)
				+ (this->getPosition().y - Target->getPosition().y) * (this->getPosition().y - Target->getPosition().y))
				<= ((Target->getContentSize().width / 2) * (Target->getContentSize().width / 2)
					+ (Target->getContentSize().height / 2) * (Target->getContentSize().height / 2))*
			if (fabs(this->getPosition().x - Target->getPosition().x) <= (Target->getContentSize().width / 2))
			{
				Target->declineHp(Farther->tower_information);
				this->removeFromParent();
			}
			else {
				double ds = 300 * dt * (if_speed_up + 1);
				double dx = ds * cos(360-r);
				double dy = dx * sin(360-r);
				this->setRotation(r);
				this->setPosition(this->getPosition().x + dx, this->getPosition().y + dy);
			}
		}
	}
}*/

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
	if (if_pause == 0) {
		time += dt;
		Vec2 my_position = this->getPosition();
		Vec2 enemy_position;
		Enemy* target = nullptr;
		extern Enemy* destination;

		if (destination != nullptr)
			enemy_position = destination->getPosition();

		if (((my_position.x - enemy_position.x) * (my_position.x - enemy_position.x) +
			(my_position.y - enemy_position.y) * (my_position.y - enemy_position.y))
			<= (tower_information.attack_range * 80) * (tower_information.attack_range * 80))
		{
			target = destination;
		}
		else {
			for (Enemy* enemy : monster) {
				enemy_position = enemy->getPosition();
				if (((my_position.x - enemy_position.x) * (my_position.x - enemy_position.x) +
					(my_position.y - enemy_position.y) * (my_position.y - enemy_position.y))
					<= (tower_information.attack_range * 80) * (tower_information.attack_range * 80))
				{
					target = enemy;
					break;
				}
			}
		}

		if (target != nullptr) {
			if (time >= (if_speed_up == 0 ? (4 / tower_information.attack_speed) : (2 / tower_information.attack_speed))) {
				time = 0;
				Node* this_layer = this->getParent();
				Layer* ThisLayer = static_cast<Layer*>(this_layer);
				/*攻击前摇动画*/
				float dx, dy, r;
				dx = target->getPosition().x - my_position.x;
				dy = target->getPosition().y - my_position.y;
				r = -atan2f(dy, dx) / 3.14159 * 180;
				string str[4] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" };

				if (tower_information.name_tag == Tower_Bottle) {
					bottle_atk_sound_effect();
					this->setRotation(r);
					Vector<SpriteFrame*> frame;
					switch (tower_information.level) {
						case 1:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk11.PNG", Rect(0, 0, 62, 24)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk12.PNG", Rect(0, 0, 62, 27)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin1.PNG", Rect(0, 0, 56, 25)));
							break;
						case 2:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk21.PNG", Rect(0, 0, 69, 32)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk22.PNG", Rect(0, 0, 67, 40)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin2.PNG", Rect(0, 0, 63, 35)));
							break;
						case 3:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk31.PNG", Rect(0, 0, 76, 43)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk32.PNG", Rect(0, 0, 72, 48)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin3.PNG", Rect(0, 0, 70, 46)));
							break;
						default:
							break;
					}
					this->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.11)), nullptr));
					auto bullet = Sprite::create();
					switch (tower_information.level)
					{
						case 1:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet1.PNG");
							break;
						case 2:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet2.PNG");
							break;
						case 3:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet3.PNG");
							break;
						default:
							break;
					}
					bullet->setPosition(this->getPosition());

					auto remove_bullet = CallFunc::create([=]() {
						bullet->removeFromParent();
						});

					auto attacked = CallFunc::create([=]() {
						if (target != nullptr)
							target->declineHp(tower_information, 0);
						});

					bullet->setRotation(r);
					auto bullet_move_to = cocos2d::MoveTo::create(if_speed_up == 0 ? 0.33 : 0.33 / 2, target->getPosition());
					bullet->runAction(Sequence::create(bullet_move_to, DelayTime::create(0), remove_bullet, DelayTime::create(0), attacked, nullptr));
					ThisLayer->addChild(bullet);
				}
				else if (tower_information.name_tag == Tower_Shit) {
					shit_atk_sound_effect();
					//利用帧动画完成攻击动画
					auto atk_Effect = Sprite::create();
					Vector<SpriteFrame*> frame;
					switch (tower_information.level) {
						case 1:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk11.PNG", Rect(0, 0, 43, 46)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk12.PNG", Rect(0, 0, 55, 46)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin1.PNG", Rect(0, 0, 47, 41)));
							break;
						case 2:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk21.PNG", Rect(0, 0, 48, 60)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk22.PNG", Rect(0, 0, 59, 57)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin2.PNG", Rect(0, 0, 52, 53)));
							break;
						case 3:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk31.PNG", Rect(0, 0, 56, 68)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk32.PNG", Rect(0, 0, 70, 66)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin3.PNG", Rect(0, 0, 61, 65)));
							break;
						default:
							break;
					}
					this->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.11)), nullptr));
					auto bullet = Sprite::create();
					switch (tower_information.level)
					{
						case 1:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet1.PNG");
							break;
						case 2:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet2.PNG");
							break;
						case 3:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet3.PNG");
							break;
						default:
							break;
					}
					bullet->setPosition(this->getPosition());

					auto remove_bullet = CallFunc::create([=]() {
						bullet->removeFromParent();
						});

					auto attacked = CallFunc::create([=]() {
						if (target != nullptr)
							target->declineHp(tower_information, 0);
						});

					bullet->setRotation(r);
					auto bullet_move_to = cocos2d::MoveTo::create(if_speed_up == 0 ? 0.33 : 0.33 / 2, target->getPosition());
					bullet->runAction(Sequence::create(bullet_move_to, DelayTime::create(0), remove_bullet, DelayTime::create(0), attacked, nullptr));
					ThisLayer->addChild(bullet);
				}
				else if (tower_information.name_tag == Tower_Star) {
					star_atk_sound_effect();
					//利用帧动画完成攻击动画
					auto atk_Effect = Sprite::create();
					Vector<SpriteFrame*> frame;
					switch (tower_information.level) {
						case 1:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk11.PNG", Rect(0, 0, 59, 59)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk12.PNG", Rect(0, 0, 61, 58)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin1.PNG", Rect(0, 0, 53, 54)));
							break;
						case 2:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk21.PNG", Rect(0, 0, 60, 60)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk22.PNG", Rect(0, 0, 70, 69)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin2.PNG", Rect(0, 0, 57, 56)));
							break;
						case 3:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk31.PNG", Rect(0, 0, 72, 73)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk32.PNG", Rect(0, 0, 73, 74)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin3.PNG", Rect(0, 0, 68, 70)));
							break;
						default:
							break;
					}

					this->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.11)), nullptr));
					auto bullet = Sprite::create();
					switch (tower_information.level)
					{
						case 1:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet1.PNG");
							break;
						case 2:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet2.PNG");
							break;
						case 3:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet3.PNG");
							break;
						default:
							break;
					}
					bullet->setPosition(this->getPosition());

					auto remove_bullet = CallFunc::create([=]() {
						bullet->removeFromParent();
						});

					auto attacked = CallFunc::create([=]() {
						if (target != nullptr) {
							Vec2 devided;
							if (target->declineHp(tower_information, 0)) {
								for (Enemy* enemy : monster) {
									devided = enemy->getPosition();
									if (((target->getPositionX() - devided.x) * (target->getPositionX() - devided.x) +
										(target->getPositionY() - devided.y) * (target->getPositionY() - devided.y))
										<= (160 * 160) * (tower_information.attack_range + 1) / 2)
									{
										enemy->declineHp(tower_information, 1);
									}
								}
							}
						}
						});

					auto bullet_move_to = cocos2d::MoveTo::create(if_speed_up == 0 ? 0.33 : 0.33 / 2, target->getPosition());
					auto rotate = Spawn::create(bullet_move_to, Repeat::create(RotateBy::create(if_speed_up == 0 ? 0.33 : 0.33 / 2, 360), 1), nullptr);
					bullet->runAction(Sequence::create(rotate, DelayTime::create(0), remove_bullet, DelayTime::create(0), attacked, nullptr));
					ThisLayer->addChild(bullet);
				}
			}
		}
	}
}

/*建造炮台*/
void Tower::build_tower(pos position, int tag, cocos2d::Layer* this_layer)
{
	if (tag <= 4) {
		build_sound_effect();

		string str[5] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" ,"/Tower/Build/" };
		vec2 vec = trans_ij_to_xy(position);

		TowerBase = Sprite::create();
		TowerBody = Tower_body::create();
		TowerBody->tower_information = { tag, Tower_Value[tag - 1], Tower_Attack[tag - 1], Tower_Attack_Speed[tag - 1], 1.2, tag - 1, 1 };

		switch (tag) {
			case 1:
				TowerBase->setTexture(str[tag - 1] + "ID1_11.PNG");
				TowerBody->setTexture(str[tag - 1] + "origin1.PNG");
				TowerBody->setRotation(-90);
				break;
			case 2:
				TowerBase->setTexture(str[tag - 1] + "ID2_29.PNG");
				TowerBody->setTexture(str[tag - 1] + "origin1.PNG");
				break;
			case 3:
				TowerBase->setTexture(str[tag - 1] + "ID4_0.PNG");
				TowerBody->setTexture(str[tag - 1] + "origin1.PNG");
				break;
			case 4:
				TowerBase->setTexture(str[tag - 1] + "ID3_56.PNG");
				TowerBody->setTexture(str[tag - 1] + "origin1.PNG");
				TowerBody->setRotation(0);
				break;
			default:
				break;
		}

		TowerBase->setPosition(vec.x, vec.y);
		this_layer->addChild(TowerBase);
		TowerBody->setPosition(vec.x, vec.y);
		this_layer->addChild(TowerBody);
		tower_map[position.i][position.j] = this;

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
	vec2 vec = trans_ij_to_xy(position);
	uplevel_sound_effect();

	if (game_map[position.i][position.j] != CARROT) {
		if (this->get_level() < Max_Level) {
			string str[4] = { "/Tower/Bottle/" ,"/Tower/Shit/", "/Tower/Fan/","/Tower/Star/" };

			/*更新基本信息*/
			TowerBody->tower_information.value += get_level_up_money();
			TowerBody->tower_information.level++;
			TowerBody->tower_information.attack *= 2;
			TowerBody->tower_information.attack_range += 0.5;
			TowerBody->tower_information.attack_speed *= 1.5;

			//TowerBody->tower_information = tower_map[position.i][position.j];

			/*更新画面*/
			switch (TowerBody->tower_information.name_tag) {
				case 1:
					TowerBase->setTexture(str[TowerBody->tower_information.name_tag - 1] + "ID1_11.PNG");
					if (TowerBody->tower_information.level == 2) {
						TowerBody->setTexture(str[TowerBody->tower_information.name_tag - 1] + "ID1_15.PNG");
					}
					else if (TowerBody->tower_information.level == 3) {
						TowerBody->setTexture(str[TowerBody->tower_information.name_tag - 1] + "ID1_5.PNG");
					}
					TowerBody->setRotation(-90);
					break;
				case 2:
					if (TowerBody->tower_information.level == 2) {
						TowerBase->setTexture(str[TowerBody->tower_information.name_tag - 1] + "ID2_9.PNG");
						TowerBody->setTexture(str[TowerBody->tower_information.name_tag - 1] + "ID2_21.PNG");
					}
					else if (TowerBody->tower_information.level == 3) {
						TowerBase->setTexture(str[TowerBody->tower_information.name_tag - 1] + "ID2_7.PNG");
						TowerBody->setTexture(str[TowerBody->tower_information.name_tag - 1] + "ID2_22.PNG");
					}
					break;
				case 3:
					if (TowerBody->tower_information.level == 2) {
						TowerBase->setTexture(str[TowerBody->tower_information.name_tag - 1] + "ID4_1.PNG");
						TowerBody->setTexture(str[TowerBody->tower_information.name_tag - 1] + "ID4_8.PNG");
					}
					else if (TowerBody->tower_information.level == 3) {
						TowerBase->setTexture(str[TowerBody->tower_information.name_tag - 1] + "ID4_2.PNG");
						TowerBody->setTexture(str[TowerBody->tower_information.name_tag - 1] + "ID4_11.PNG");
					}
					break;
				case 4:
					if (TowerBody->tower_information.level == 2) {
						TowerBase->setTexture(str[TowerBody->tower_information.name_tag - 1] + "ID3_56.PNG");
						TowerBody->setTexture(str[TowerBody->tower_information.name_tag - 1] + "ID3_98.PNG");
					}
					else if (TowerBody->tower_information.level == 3) {
						TowerBase->setTexture(str[TowerBody->tower_information.name_tag - 1] + "ID3_84.PNG");
						TowerBody->setTexture(str[TowerBody->tower_information.name_tag - 1] + "ID3_46.PNG");
					}
					TowerBody->setRotation(0);
					break;
				default:
					break;
			}

			TowerBase->setPosition(vec.x, vec.y);
			TowerBody->setPosition(vec.x, vec.y);

			//this_layer->addChild(TowerBase);
			//this_layer->addChild(TowerBody);
		}
		
	}
	else if (carrot_level < Max_Level) {
		carrot_level++;
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

/*出售炮台*/
void Tower::sell_tower(pos position, cocos2d::Layer* this_layer)
{
	sell_sound_effect();

	this_layer->removeChild(TowerBase);
	this_layer->removeChild(TowerBody);
	//delete TowerBody;
	//TowerBody->removeFromParent();

	tower_map[position.i][position.j] = nullptr;

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

	delete this;
}

/*获得出售价格*/
int Tower::get_sell_money() 
{
	if (this != nullptr && TowerBody != nullptr)
		return TowerBody->tower_information.value * 0.8;
	else
		return 0;
}

/*获得攻击范围*/
float Tower::get_attack_range()
{
	if (this != nullptr && TowerBody != nullptr)
		return TowerBody->tower_information.attack_range;
	else
		return 1;
}

/*获得等级*/
int Tower::get_level()
{
	if (this != nullptr && TowerBody != nullptr)
		return TowerBody->tower_information.level;
	else
		return 0;
}

/*获得升级所需金币*/
int Tower::get_level_up_money()
{
	if (this != nullptr && TowerBody != nullptr) {
		if (TowerBody->tower_information.name_tag == Tower_Bottle)
			return (100 + TowerBody->tower_information.level * 80);
		else
			return (TowerBody->tower_information.level == 1 ? 220 : 260);
	}
	else
		return (carrot_level == 1 ? 500 : 1000);
}

/*获得初始建造金币*/
int getMoney(int tag) {
	return Tower_Value[tag - 1];
}