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
/************************************  ��ʼ��  ********************************/
cocos2d::Layer* EnemyCreate::createLayer() {
	return EnemyCreate::create();
}
bool EnemyCreate::init() {
	if (!Layer::init()) {
		return false;
	}
	return true;
}
/**********************************  ��Ա����ʵ��  ****************************/
/*���ùؿ�*/
void EnemyCreate::SetLevel(int level_selection) {
	level = level_selection;
	all_clear = 1;
	vector<int>waves;
	if (level == 1) {
		//��һ��
		start_position = { 1,1 };
		current_waves = 1;
		max_waves = 15;
		//ÿһ������洢
		//ǰ�߲�ȫ����ͨ��
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 10; j++) {
				waves.push_back(NORMAL);
			}
			monster_data.push_back(waves);
			waves.clear();
		}
		//��8����ͨ��5�������й�5��
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
		//��һ��
		start_position = { 1,4 };
		current_waves = 1;
		max_waves = 15;
		//ÿһ������洢
		//ǰ�߲�ȫ����ͨ��
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 10; j++) {
				waves.push_back(NORMAL);
			}
			monster_data.push_back(waves);
			waves.clear();
		}
		//��7����ͨ��5�������й�5��
		//���һ����һ��boss
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
/*����*/
void EnemyCreate::monster_appear(int Type) {
	//��������ΪType�Ĺ���
	auto enemy = Enemy::createSprite();
	static_cast<Enemy*>(enemy)->setType(Type);
	vec2 start = trans_ij_to_xy(start_position);
	enemy->setPosition(Vec2(start.x, start.y));
	this->addChild(enemy);
	monster.push_back(static_cast<Enemy*>(enemy));//������������
	//����ǹ�������ϰ���������Ч����
	if (Type < 3) {
		auto effect = Sprite::create("/EnemyCreate/Items02-hd_0.PNG");
		effect->setPosition(Vec2(start.x, start.y));
		this->addChild(enemy);
		effect->runAction(Sequence::create(ScaleTo::create(0.5, 1.5), CallFunc::create([effect]() {effect->removeFromParent(); }), nullptr));
	}
}
/*��ʼ��Ϸ*/
void EnemyCreate::start() {
	//��ʼ��Ϸ,�򿪵�����
	auto create_monster = CallFunc::create([=]() {this->scheduleUpdate(); });
	//���뵹��ʱ��ʼ����
	this->runAction(Sequence::create(DelayTime::create(3), create_monster, nullptr));
}
/*һ�����������*/
void EnemyCreate::create_waves() {
	auto create_func = CallFunc::create([=]() {
		monster_appear(monster_data[current_waves - 1][0]);
		for (int i = 0; i < monster_data[current_waves - 1].size() - 1; i++) {
			int temp = monster_data[current_waves - 1][i];
			monster_data[current_waves - 1][i] = monster_data[current_waves - 1][i + 1];
			monster_data[current_waves - 1][i + 1] = temp;
		}
		});
	//ÿһ����ʼʱ��һ��յ�������ÿ0.5sһ��
	this->runAction(Sequence::create(DelayTime::create(1), Repeat::create(Sequence::create(DelayTime::create(0.5), create_func, nullptr), monster_data[current_waves - 1].size()), nullptr));
	all_clear = 0;
	current_waves += 1;
}
/*update����*/
void EnemyCreate::update(float dt) {
	//�����ǰ��������Ϊ0����˵������ȫ��
	if (monster.size() == 0) {
		all_clear = 1;
	}
	//�����ǰ����ȫ�壬�һ��й���û��
	if (all_clear = 1 && current_waves <= max_waves) {
		create_waves();
		/*if (game_waves < max_waves) {
			game_waves += 1;
		}*/
	}
}

