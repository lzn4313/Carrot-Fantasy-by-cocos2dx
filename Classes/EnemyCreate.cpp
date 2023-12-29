#include "cocos2d.h"
#include"GameScene.h"
#include"enemy.h"
#include"EnemyCreate.h"
#include<vector>
using namespace std;
USING_NS_CC;

extern int game_waves;
extern vector<Enemy*> monster;
extern vector<Enemy*> barrier;
/************************************  初始化  ********************************/
cocos2d::Layer* EnemyCreate::createLayer() {
	return EnemyCreate::create();
}
bool EnemyCreate::init() {
	if (!Layer::init()) {
		return false;
	}
	return true;
}
/**********************************  成员函数实现  ****************************/
/*设置关卡*/
void EnemyCreate::SetLevel(int level_selection) {
	level = level_selection;
	all_clear = 1;
	vector<int>waves;
	if (level == 1) {
		//第一关
		start_position = { 1,1 };
		current_waves = 1;
		max_waves = 15;
		//每一波怪物存储
		//前七波全是普通怪
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 10; j++) {
				waves.push_back(NORMAL);
			}
			monster_data.push_back(waves);
			waves.clear();
		}
		//后8波普通怪5个，飞行怪5个
		for (int i = 6; i < 15; i++) {
			for (int j = 0; j < 5; j++) {
				waves.push_back(NORMAL);
			}
			for (int j = 0; j < 5; j++) {
				waves.push_back(FLY);
			}
			monster_data.push_back(waves);
			waves.clear();
		}
	}
	else if (level == 2) {
		//第一关
		start_position = { 1,4 };
		current_waves = 1;
		max_waves = 15;
		//每一波怪物存储
		//前七波全是普通怪
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 10; j++) {
				waves.push_back(NORMAL);
			}
			monster_data.push_back(waves);
			waves.clear();
		}
		//后7波普通怪5个，飞行怪5个
		//最后一波加一个boss
		for (int i = 6; i < 15; i++) {
			for (int j = 0; j < 5; j++) {
				waves.push_back(NORMAL);
			}
			for (int j = 0; j < 5; j++) {
				waves.push_back(FLY);
			}
			monster_data.push_back(waves);
			waves.clear();
			if (i == 14) {
				monster_data[i].push_back(BOSS);
			}
		}

	}
}
/*出怪*/
void EnemyCreate::monster_appear(int Type) {
	//创建类型为Type的怪物
	auto enemy = Enemy::createSprite();
	static_cast<Enemy*>(enemy)->setType(Type);
	vec2 start = trans_ij_to_xy(start_position);
	enemy->setPosition(Vec2(start.x, start.y));
	this->addChild(enemy);
	monster.push_back(static_cast<Enemy*>(enemy));//加入索敌数组
	//如果是怪物，不是障碍，出怪特效设置
	if (Type < 3) {
		auto effect = Sprite::create("/EnemyCreate/Items02-hd_0.PNG");
		effect->setPosition(Vec2(start.x, start.y));
		this->addChild(enemy);
		effect->runAction(Sequence::create(ScaleTo::create(0.5, 1.5), CallFunc::create([effect]() {effect->removeFromParent(); }), nullptr));
	}
}
/*开始游戏*/
void EnemyCreate::start() {
	//开始游戏,打开调度器
	auto create_monster = CallFunc::create([=]() {this->scheduleUpdate(); });
	//三秒倒计时后开始出怪
	this->runAction(Sequence::create(DelayTime::create(3), create_monster, nullptr));
}
/*一波怪物的生成*/
void EnemyCreate::create_waves() {
	auto create_func = CallFunc::create([=]() {
		monster_appear(monster_data[current_waves - 1][0]);
		for (int i = 0; i < monster_data[current_waves - 1].size() - 1; i++) {
			int temp = monster_data[current_waves - 1][i];
			monster_data[current_waves - 1][i] = monster_data[current_waves - 1][i + 1];
			monster_data[current_waves - 1][i + 1] = temp;
		}
		});
	//每一波开始时有一秒空挡，出怪每0.5s一个
	this->runAction(Sequence::create(DelayTime::create(1), Repeat::create(Sequence::create(DelayTime::create(0.5), create_func, nullptr), monster_data[current_waves - 1].size()), nullptr));
	all_clear = 0;
	current_waves += 1;
}
/*update函数*/
void EnemyCreate::update(float dt) {
	//如果当前怪物数组为0，则说明怪物全清
	if (monster.size() == 0) {
		all_clear = 1;
	}
	//如果当前怪物全清，且还有怪物没出
	if (all_clear = 1 && current_waves <= max_waves) {
		create_waves();
		/*if (game_waves < max_waves) {
			game_waves += 1;
		}*/
	}
}

