#include "cocos2d.h"
#include "GameScene.h"
#include "enemy.h"
using namespace std;

/*名称与标签对应*/
#define Tower_Bottle 1
#define Tower_Shit 2
#define Tower_Fan 3
#define Tower_Star 4

/*攻击效果与标签对应*/
#define None 0
#define Slow 1
#define Penetrate 2
#define Divide 3

#define Max_Level 3

const int Tower_Value[4] = { 100,120,160,160 };
const float Tower_Attack[4] = { 50,20,60,80 };
const float Tower_Attack_Speed[4] = { 12,4,4,3 };

class Tower_body;

struct Tower_information {
	int name_tag;//记录名称标签
	int value;//记录当前价值
	float attack;//记录单次攻击力
	float attack_speed;//记录攻击速度
	float attack_range;//记录攻击范围
	int attack_special;//记录特殊攻击效果（穿透、减速、分裂等）
	int level;//记录等级

	Tower_information(int t = 0, int v = 0, float atk = 0, float atk_speed = 0, float atk_r = 1, int atk_special = 0, int L = 1)
		:name_tag(t), value(v), attack(atk), attack_speed(atk_speed), attack_range(atk_r), attack_special(atk_special), level(L)
	{}//构造函数

};

/*
class Bullet :public cocos2d::Sprite {
	friend class Tower_body;
private:
	Enemy* Target;
	Tower_body* Farther;
public:
	//构造函数
	static cocos2d::Sprite* createSprite();
	virtual bool init();
	virtual void update(float dt);//实时判断范围内是否有敌人，有则攻击
	CREATE_FUNC(Bullet);
};*/

class Tower_body :public cocos2d::Sprite {
	friend class Tower;
	friend class Bullet;
private:
	Tower_information tower_information;
	float time = 0;//控制攻击间隔
public:
	//构造函数
	static cocos2d::Sprite* createSprite();
	virtual bool init();
	virtual void update(float dt);//实时判断范围内是否有敌人，有则攻击
	CREATE_FUNC(Tower_body);
};

/*炮台类*/
class Tower {
private:
	Tower_body* TowerBody;
	cocos2d::Sprite* TowerBase;
public:
	void build_tower(pos position, int tag, cocos2d::Layer* this_layer);//根据名称标签在指定位置建造一个炮台
	void up_level_tower(pos position, cocos2d::Layer* this_layer);//升级炮台
	void sell_tower(pos position, cocos2d::Layer* this_layer);//出售炮台
	float get_attack_range();//获得攻击范围
	int get_level();//获得等级
	int get_level_up_money();//获得升级所需金币
	int get_sell_money();//获得出售价格
	//void bullet_fly(Tower_information 
	// 
	// , cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Layer* this_layer);//子弹飞行动画
	//void attack_once(Tower_information tower, cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Layer* this_layer);//单次攻击动画
};

int getMoney(int tag);//根据名称标签获得初始价值