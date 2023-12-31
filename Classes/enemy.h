#pragma once
#include "cocos2d.h"
#include "GameScene.h"

#define BARRIER 0
#define MONSTER 1

#define BARRIER_ONE   1     //一格的障碍
#define BARRIER_TWO   2     //两格的障碍
#define BARRIER_FOUR  4     //四格的障碍

#define BARRIER_HP_ONE     1600               //一格障碍的血
#define BARRIER_HP_TWO     3 * BARRIER_HP_ONE //两格障碍的血
#define BARRIER_HP_FOUR    3 * BARRIER_HP_TWO //四格障碍的血

#define BARRIER_COIN_ONE     50 
#define BARRIER_COIN_TWO     2 * BARRIER_COIN_ONE //两格障碍的血
#define BARRIER_COIN_FOUR    2 * BARRIER_COIN_TWO //四格障碍的血

#define MONSTER_NORMAL 0    //中等血量，中等速度
#define MONSTER_FAST   1    //低血量，高速度
#define MONSTER_HUGE   2    //高血量，速度较低

#define MONSTER_FAST_HP       20                     //高速怪的基础血量
#define MONSTER_NORMAL_HP     3 * MONSTER_FAST_HP    //普通怪血量
#define MONSTER_HUGE_HP       3 * MONSTER_NORMAL_HP  //巨型怪血量

#define MONSTER_HUGE_SPEED    100                  //巨型怪移动速度，蜗牛爬，待改动！！！！
#define MONSTER_NORMAL_SPEED  1.5*MONSTER_HUGE_SPEED     //正常怪移速
#define MONSTER_FAST_SPEED    2*MONSTER_NORMAL_SPEED   //高速怪移速

#define MONSTER_COIN_NORMAL   18                       //正常怪和高速怪掉落金币
#define MONSTER_COIN_HUGE     188                      //巨型怪掉落金币

#define BARRIER_BASE_PICTURE  "/Enemy/barrier/0/"        //障碍路径
#define MONSTER_BASE_PICTURE  "/Enemy/monster/0/"

//0-8 0为普通怪 1为高速怪 2为巨型怪 34为一格贴图 56为二格贴图 78为四格贴图
#define NORMAL 0
#define FLY 1
#define BOSS 2
#define BARRIER_1 3
#define BARRIER_2 4
#define BARRIER_3 5
#define BARRIER_4 6
#define BARRIER_5 7
#define BARRIER_6 8


struct Tower_information;
struct Enemy_information {
	int type;                                     //记录怪物种类
	int hp;                                       //记录怪物血量
	int speed;                                    //记录怪物移动速度
	int coin;                                     //携带萝卜币
	int damage;                                   //对萝卜造成的伤害
	cocos2d::Sprite* enemy_picture;               //障碍贴图
	int count;                                    //走过的格子数
	double time = 0;                                 //记录生效时间
	int origin_speed;                             //记录常态化速度
	int full_hp;                                  //记录满血血量
	float total_length = 0;						  //记录走过的路程长度
	pos position;                                 //记录障碍物位置
		Enemy_information(int _type=0,int originalHp = 0, int originalSpeed = 200, int defeatedCoin = 0, int realDamage = 0, int n = 0,int currentTime=0,pos Position={0,0})
		:type(_type),hp(originalHp), speed(originalSpeed), coin(defeatedCoin), damage(realDamage), count(n),origin_speed(originalSpeed),time(currentTime),full_hp(originalHp),position(Position)
	{
		enemy_picture = nullptr;

	}
		float get_length() { return total_length; }
};

class Enemy : public cocos2d::Sprite
{
	friend class Tower_body;
private:
	Enemy_information enemy;
public:
    static cocos2d::Sprite* createSprite();
	virtual bool init();
	CREATE_FUNC(Enemy);
	virtual void update(float dt);
	void setType(int selection);
	void set_position(pos _position) { enemy.position = _position; }
	bool declineHp(Tower_information tower, int op);
};