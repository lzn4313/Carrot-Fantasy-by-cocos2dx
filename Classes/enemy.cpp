#include "enemy.h"
#include"sound&music.h"
#include"GameData.h"
#include"GameScene.h"
#include"Level_1_1.h"
#include <vector>
#include<algorithm>
#include <math.h>
#include "Tower.h"
USING_NS_CC;
extern int if_speed_up;
extern int game_waves;
extern int if_pause;
extern const char level_1_1_map[7][12];
extern vector<LevelPath>levelPath;
extern int carrot_hp;
extern char game_map[7][12];
extern int money_total;
extern int game_money;//金钱
extern int monster_total;//击杀怪物总数
extern int boss_total;//击杀boss总数
extern int barrier_total;//摧毁障碍总数
extern vector<Enemy*>monster;
extern vector<Enemy*>barrier;
extern Enemy* destination;
using namespace cocos2d::ui;
//不是cocos自带



Sprite* Enemy::createSprite()
{
	return Enemy::create();
}

bool Enemy::init()
{
	if (!Sprite::init()) {
		return false;
	}
	
	this->scheduleUpdate();
	return true;
}

void Enemy::setType(int selection)
{
	enemy.type = selection;
	//0-8 0为普通怪 1为高速怪 2为巨型怪 34为一格贴图 56为二格贴图 78为四格贴图
	string picture[] = { "normal01-2.PNG","fast01-2.PNG","huge01-2.PNG","One1.PNG","One2.PNG","Two1.PNG","Two2.PNG","Four1.PNG","Four2.PNG" };
	string pic[] = { "normal01-1.PNG","fast01-1.PNG","huge01-1.PNG" };
	string road1 = BARRIER_BASE_PICTURE;
	string road2 = MONSTER_BASE_PICTURE;
	Vector<SpriteFrame*> monster;
	this->enemy.time = 0;
	
	switch (selection)
	{
	case 0:
		monster.pushBack(SpriteFrame::create(road2 + picture[0], Rect(0, 0, 68, 87)));
		monster.pushBack(SpriteFrame::create(road2 + pic[0], Rect(0, 0, 75, 74)));
		
		this->runAction(RepeatForever::create(Sequence::create(Animate::create(Animation::createWithSpriteFrames(monster, 0.1)), nullptr)));
		this->enemy.coin = MONSTER_COIN_NORMAL;
		this->enemy.damage = 1;
		this->enemy.hp = MONSTER_NORMAL_HP * (game_waves + 1)/2;
		this->enemy.full_hp = MONSTER_NORMAL_HP * (game_waves + 1)/2;
		this->enemy.speed = MONSTER_NORMAL_SPEED;
		this->enemy.origin_speed = MONSTER_NORMAL_SPEED;
		break;
	case 1:
		monster.pushBack(SpriteFrame::create(road2 + picture[1], Rect(0, 0, 148, 84)));
		monster.pushBack(SpriteFrame::create(road2 + pic[1], Rect(0, 0, 154, 84)));
		this->runAction(RepeatForever::create(Sequence::create(Animate::create(Animation::createWithSpriteFrames(monster, 0.1)), nullptr)));
		this->enemy.coin = MONSTER_COIN_NORMAL;
		this->enemy.damage = 1;
		this->enemy.hp = MONSTER_FAST_HP * (game_waves + 1)/2;
		this->enemy.full_hp = MONSTER_FAST_HP  * (game_waves + 1)/2;
		this->enemy.speed = MONSTER_FAST_SPEED;
		this->enemy.origin_speed = MONSTER_FAST_SPEED;
		break;
	case 2:
		monster.pushBack(SpriteFrame::create(road2 + picture[2], Rect(0, 0, 144, 135)));
		monster.pushBack(SpriteFrame::create(road2 + pic[2], Rect(0, 0, 183, 148)));
		this->runAction(RepeatForever::create(Sequence::create(Animate::create(Animation::createWithSpriteFrames(monster, 0.1)), nullptr)));
		this->enemy.coin = MONSTER_COIN_HUGE;
		this->enemy.damage = 2;
		this->enemy.hp = MONSTER_HUGE_HP * (game_waves + 1);
		this->enemy.full_hp = MONSTER_HUGE_HP * (game_waves + 1);
		this->enemy.speed = MONSTER_HUGE_SPEED;
		this->enemy.origin_speed = MONSTER_HUGE_SPEED;
		break;
	case 3:
	case 4:
		this->setTexture(road1 + picture[selection]);
		this->enemy.coin = BARRIER_COIN_ONE;
		this->enemy.damage = 0;
		this->enemy.hp = BARRIER_HP_ONE;
		this->enemy.full_hp = BARRIER_HP_ONE;
		this->enemy.speed = 0;
		this->enemy.origin_speed = 0;
		break;
	case 5:
		this->setTexture(road1 + picture[selection]);
		this->enemy.coin = BARRIER_COIN_TWO;
		this->enemy.damage = 0;
		this->enemy.hp = BARRIER_HP_TWO;
		this->enemy.full_hp = BARRIER_HP_TWO;
		this->enemy.speed = 0;
		this->enemy.origin_speed = 0;
		break;
	case 6:
		this->setTexture(road1 + picture[selection]);
		this->enemy.coin = BARRIER_COIN_TWO;
		this->enemy.damage = 0;
		this->enemy.hp = BARRIER_HP_TWO;
		this->enemy.full_hp = BARRIER_HP_TWO;
		this->enemy.speed = 0;
		this->setScaleY(80 / this->getContentSize().height);
		this->enemy.origin_speed = 0;
		break;
	case 7:
	case 8:
		this->setTexture(road1 + picture[selection]);
		this->enemy.coin = BARRIER_COIN_FOUR;
		this->enemy.damage = 0;
		this->enemy.hp = BARRIER_HP_FOUR;
		this->enemy.full_hp = BARRIER_HP_FOUR;
		this->enemy.speed = 0;
		this->enemy.origin_speed = 0;
		break;
	}
	if (selection <= 2) {
		this->setAnchorPoint(Vec2(0.5, 0.25));
	}

	auto selected = Sprite::create("/Enemy/selected.PNG");
	selected->setName("Selected");
	this->addChild(selected);
	if (selection <= 2) {
		if (selection == 0) {
			selected->setPosition(Vec2(selected->getContentSize().width * 1.3, selected->getContentSize().height * 3.5));
		}
		else {
			selected->setPosition(Vec2(selected->getContentSize().width * 3, selected->getContentSize().height * 3.5));
		}
	}
	else {
		selected->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height + 30));
	}
	selected->setVisible(false);
	selected->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.2, Vec2(0, selected->getContentSize().height / 5)), MoveBy::create(0.2, Vec2(0, -selected->getContentSize().height / 5)), nullptr)));
}

void Enemy::update(float dt)
{
	sort(monster.begin(), monster.end(), [](Enemy* a, Enemy* b) {return  a->enemy.get_length() > b->enemy.get_length(); });
	if (destination == this) {
		this->getChildByName("Selected")->setVisible(true);
	}
	else {
		this->getChildByName("Selected")->setVisible(false);
	}

	static int appear_waves = game_waves;
	//减速状态时间累计判断
	if (enemy.origin_speed > enemy.speed) {
		enemy.time += dt * (1 + if_speed_up) * (1 - if_pause) * 100;
		if (enemy.time > 300) {
			enemy.time = 0;
			this->removeChildByName("shit");
			enemy.speed = enemy.origin_speed;
		}
	}
	//对于移动的判断
	if (if_pause == 0&&enemy.speed>0) {//无暂停和速度大于0(即非障碍物)则动
		int x = this->getPositionX();
		int y = this->getPositionY();
		static vec2 startPosition = trans_ij_to_xy(levelPath[0].point);
		//出场动画
		int ix = 0, iy = 0;
		if (levelPath[enemy.count].direction == 's') {
			ix = 0;
			iy = -1;
		}
		else if (levelPath[enemy.count].direction == 'w') {
			ix = 0;
			iy = 1;
		}
		else if (levelPath[enemy.count].direction == 'a') {
			ix = -1;
			iy = 0;
		}
		else if (levelPath[enemy.count].direction == 'd') {
			ix = 1;
			iy = 0;
		}
		else if (levelPath[enemy.count].direction == 'o') {
			ix = 0;
			iy = 0;
		}
		double this_x = enemy.speed * (if_speed_up + 1) * dt * ix;
		double this_y = enemy.speed * (if_speed_up + 1) * dt * iy;
		if (enemy.count + 1!=levelPath.size()) {
			vec2 nextPosition;
			nextPosition = trans_ij_to_xy(levelPath[enemy.count + 1].point);
			enemy.total_length = enemy.total_length + fabs(this_x) + fabs(this_y);
			int range = 4;
			if (enemy.type == FLY) {
				range = 6;
			}
			if (((fabs(x + this_x - nextPosition.x) < range)||ix==0) && ((fabs(y + this_y - nextPosition.y) < range)||iy==0))
				enemy.count++;
		}
		
		this->setPosition(Vec2(x + this_x, y + this_y));
		if (levelPath[enemy.count].direction == 'o') {
			carrot_eaten_sound_effect();
			carrot_hp -= enemy.damage;
			Vector<SpriteFrame*> death;
			death.pushBack(SpriteFrame::create("/Enemy/monster/1.PNG",Rect(0,0,109,99)));
			death.pushBack(SpriteFrame::create("/Enemy/monster/2.PNG", Rect(0, 0, 111, 114)));
			death.pushBack(SpriteFrame::create("/Enemy/monster/3.PNG", Rect(0, 0, 194, 197)));
			death.pushBack(SpriteFrame::create("/Enemy/monster/4.PNG", Rect(0, 0, 256, 211)));
			death.pushBack(SpriteFrame::create("/Enemy/monster/5.PNG", Rect(0, 0, 154, 163)));
			death.pushBack(SpriteFrame::create("/Enemy/monster/6.PNG", Rect(0, 0, 275, 277)));
			auto sprite = Sprite::create();
			vec2 nextPosition = trans_ij_to_xy(levelPath[levelPath.size()-1].point);
			sprite->runAction(Repeat::create(Sequence::create(Animate::create(Animation::createWithSpriteFrames(death, 0.05 / (1 + if_speed_up))), FadeOut::create(0.2 / (1 + if_speed_up)), CallFunc::create([sprite]() {sprite->removeFromParent(); }), nullptr), 1));
			sprite->setPosition(Vec2(nextPosition.x, nextPosition.y));
			this->getParent()->addChild(sprite);
			if (destination == this) {
				destination = nullptr;
			}
			if (enemy.type <= 2) {
				monster.erase(find_if(monster.begin(), monster.end(), [this](const Enemy* enemy) {return enemy == this; }));
			}
			else {
				barrier.erase(find_if(barrier.begin(), barrier.end(), [this](const Enemy* enemy) {return enemy == this; }));
			}
			this->removeFromParent();
			return;
		}



	}

	//显示血条
	if (enemy.hp > 0&&enemy.hp<enemy.full_hp) {
		int special_hp=0;
		auto hpHolder = Sprite::create("/Enemy/monster/HpHolder.PNG");
		auto hpSlider = Sprite::create("/Enemy/monster/HpSlider.PNG");
		if (enemy.full_hp == MONSTER_HUGE_HP * appear_waves / 2)
			 special_hp = 1;
		
		hpHolder->setScaleX(1 + special_hp);
		hpSlider->setScaleX((1 + special_hp)* float(enemy.hp) / float(enemy.full_hp));
		this->removeChildByTag(0);
		this->removeChildByTag(1);
		Vec2 currentPosition = this->getPosition();
		hpSlider->setAnchorPoint(Vec2(0, 0.5));
		
		hpHolder->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height+10));
		hpHolder->setTag(0);
		hpSlider->setTag(1);
		this->addChild(hpHolder,1);
		currentPosition = hpHolder->getAnchorPoint();
		hpSlider->setPosition((Vec2(this->getContentSize().width / 2-float(hpHolder->getContentSize().width)*48/52*0.5*(1+special_hp), this->getContentSize().height + 10)));
		this->addChild(hpSlider, 2);
	}
	//没血了就消失
	else if(enemy.hp<=0){
		if (enemy.type == NORMAL) {
			normal_dead_sound_effect();
		}
		else if (enemy.type == FLY) {
			fly_dead_sound_effect();
		}
		else if (enemy.type == BOSS) {
			boss_dead_sound_effect();
		}
		Vector<SpriteFrame*> death;
		death.pushBack(SpriteFrame::create("/Enemy/monster/1.PNG", Rect(0, 0, 109, 99)));
		death.pushBack(SpriteFrame::create("/Enemy/monster/2.PNG", Rect(0, 0, 111, 114)));
		death.pushBack(SpriteFrame::create("/Enemy/monster/3.PNG", Rect(0, 0, 194, 197)));
		death.pushBack(SpriteFrame::create("/Enemy/monster/4.PNG", Rect(0, 0, 256, 211)));
		death.pushBack(SpriteFrame::create("/Enemy/monster/5.PNG", Rect(0, 0, 154, 163)));
		death.pushBack(SpriteFrame::create("/Enemy/monster/6.PNG", Rect(0, 0, 275, 277)));
		auto sprite = Sprite::create();
		sprite->runAction(Repeat::create(Sequence::create(Animate::create(Animation::createWithSpriteFrames(death, 0.05 / (1 + if_speed_up))), FadeOut::create(0.2 / (1 + if_speed_up)), CallFunc::create([sprite]() {sprite->removeFromParent(); }), nullptr), 1));
		sprite->setPosition(Vec2(this->getPositionX(), this->getPositionY()));
		this->getParent()->addChild(sprite);
		money_total += enemy.coin;
		game_money += enemy.coin;
		if (destination == this) {
			destination = nullptr;
		}

		if (enemy.type <= 1) {
			monster_total++;
		}
		else if (enemy.type == 2) {
			boss_total++;
		}
		else {
			barrier_total++;
			if (enemy.type == 3 || enemy.type == 4) {
				game_map[enemy.position.i][enemy.position.j] = 0;
			}
			else if (enemy.type == 5 || enemy.type == 6) {
				game_map[enemy.position.i][enemy.position.j] = 0;
				game_map[enemy.position.i][enemy.position.j + 1] = 0;
			}
			else if (enemy.type == 7 || enemy.type == 8) {
				game_map[enemy.position.i][enemy.position.j] = 0;
				game_map[enemy.position.i][enemy.position.j + 1] = 0;
				game_map[enemy.position.i - 1][enemy.position.j] = 0;
				game_map[enemy.position.i - 1][enemy.position.j + 1] = 0;
			}
		}
		if (enemy.type <= 2) {
			monster.erase(find_if(monster.begin(), monster.end(), [this](const Enemy* enemy) {return enemy == this; }));
		}
		else {
			barrier.erase(find_if(barrier.begin(), barrier.end(), [this](const Enemy* enemy) {return enemy == this; }));
		}
		this->removeFromParent();
		return;
	}
}

bool Enemy::declineHp(Tower_information tower, int op)
{
	if (enemy.hp > 0 && tower.attack > 0) {
		if (op == 0) {
			Vec2 currentPosition = this->getPosition();
			Vector<SpriteFrame*> attacked;
			auto sprite = Sprite::create();
			enemy.hp -= tower.attack;
			switch (tower.name_tag) {
				case Tower_Bottle:
					attacked.pushBack(SpriteFrame::create("/Tower/Bottle/ID1_20.PNG", Rect(0, 0, 28, 29)));
					attacked.pushBack(SpriteFrame::create("/Tower/Bottle/ID1_10.PNG", Rect(0, 0, 64, 60)));
					break;
				case Tower_Shit:
					attacked.pushBack(SpriteFrame::create("/Tower/Shit/ID2_41.PNG", Rect(0, 0, 22, 21)));
					attacked.pushBack(SpriteFrame::create("/Tower/Shit/ID2_13.PNG", Rect(0, 0, 52, 47)));
					break;
				case Tower_Fan:
					attacked.pushBack(SpriteFrame::create("/Tower/Fan/ID4_14.PNG", Rect(0, 0, 61, 66)));
					attacked.pushBack(SpriteFrame::create("/Tower/Fan/ID4_15.PNG", Rect(0, 0, 79, 87)));
					break;
				case Tower_Star:
					attacked.pushBack(SpriteFrame::create("/Tower/Star/ID3_78.PNG", Rect(0, 0, 30, 30)));
					attacked.pushBack(SpriteFrame::create("/Tower/Star/ID3_94.PNG", Rect(0, 0, 52, 52)));
					attacked.pushBack(SpriteFrame::create("/Tower/Star/ID3_79.PNG", Rect(0, 0, 103, 104)));
					attacked.pushBack(SpriteFrame::create("/Tower/Star/ID3_57.PNG", Rect(0, 0, 148, 144)));
					attacked.pushBack(SpriteFrame::create("/Tower/Star/ID3_22.PNG", Rect(0, 0, 192, 189)));
					attacked.pushBack(SpriteFrame::create("/Tower/Star/ID3_21.PNG", Rect(0, 0, 217, 212)));
			}
			sprite->runAction(Repeat::create(Sequence::create(Animate::create(Animation::createWithSpriteFrames(attacked, 0.05 / (1 + if_speed_up))), FadeOut::create(0.2 / (1 + if_speed_up)), nullptr), 1));
			sprite->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
			this->addChild(sprite);

			if (enemy.origin_speed != 0) {
				if (tower.attack_special == Slow) {
					if (tower.level == 1)
						enemy.speed = enemy.origin_speed * 0.8;
					else if (tower.level == 2||tower.level == 3)
						enemy.speed = enemy.origin_speed * 0.6;
					if (tower.name_tag == Tower_Shit && enemy.time == 0) {
						auto slowByShit = Sprite::create();
						Vector<SpriteFrame*>shit;
						shit.pushBack(SpriteFrame::create("/Tower/Shit/ID2_1.PNG", Rect(0, 0, 80, 21)));
						shit.pushBack(SpriteFrame::create("/Tower/Shit/ID2_10.PNG", Rect(0, 0, 78, 18)));
						slowByShit->runAction(RepeatForever::create(Sequence::create(Animate::create(Animation::createWithSpriteFrames(shit, 0.1)), nullptr)));
						slowByShit->setPosition(Vec2(this->getContentSize().width / 2, 0));
						slowByShit->setName("shit");
						this->addChild(slowByShit);
					}
					enemy.time = 0;
				}
			}
		}
		else if (op == 1 && tower.name_tag == Tower_Star) {
			Vec2 currentPosition = this->getPosition();
			auto sprite = Sprite::create();
			enemy.hp -= tower.attack * 0.3;
			switch (tower.level) {
				case 1:
				case 2:
					sprite->setTexture("/Tower/Star/ID3_73.PNG");
					break;
				case 3:
					sprite->setTexture("/Tower/Star/ID3_85.PNG");
					break;
				default:
					break;
			}
			sprite->runAction(Sequence::create(Blink::create(0.3 / (1 + if_speed_up), 1), FadeOut::create(0.1 / (1 + if_speed_up)), nullptr));
			sprite->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
			this->addChild(sprite);
		}
		return true;
	}
	return false;
}