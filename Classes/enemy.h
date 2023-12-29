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

#define MONSTER_HUGE_SPEED    100                        //巨型怪移动速度，蜗牛爬，待改动！！！！
#define MONSTER_NORMAL_SPEED  2*MONSTER_HUGE_SPEED     //正常怪移速
#define MONSTER_FAST_SPEED    2*MONSTER_NORMAL_SPEED   //高速怪移速

#define MONSTER_COIN_NORMAL   18                       //正常怪和高速怪掉落金币
#define MONSTER_COIN_HUGE     188                      //巨型怪掉落金币

#define BARRIER_BASE_PICTURE  "/Enemy/barrier/0/"        //障碍路径
#define MONSTER_BASE_PICTURE  "/Enemy/monster/0/"


extern struct Tower_information;
struct Enemy_information {
	int hp;                                       //记录怪物血量
	int speed;                                    //记录怪物移动速度
	int coin;                                     //携带萝卜币
	int damage;                                   //对萝卜造成的伤害
	cocos2d::Sprite* enemy_picture;               //障碍贴图
	int count;                                    //走过的格子数
	int time = 0;                                 //记录生效时间
	int origin_speed;                             //记录常态化速度
	int full_hp;                                  //记录满血血量
	Enemy_information(int originalHp = 0, int originalSpeed = 200, int defeatedCoin = 0, int realDamage = 0, int n = 0,int currentTime=0)
		:hp(originalHp), speed(originalSpeed), coin(defeatedCoin), damage(realDamage), count(n),origin_speed(originalSpeed),time(currentTime),full_hp(originalHp)
	{
		enemy_picture = nullptr;

	}

};

class Enemy : public cocos2d::Sprite
{
private:
	Enemy_information enemy;
public:
	//void appear(int species, int model, int picture, pos position, cocos2d::Layer* this_layer);                            //怪物(含出场特效)或障碍上场以类别直接设定初始值
	///*void appear(int species, int picture, int hp, int speed, int coin, int damage, pos position, cocos2d::Layer* this_layer); *///怪物或障碍上场   自行设定初始值
	////void selfAction();//怪物贴图自身的变化
	//void move();     //怪物的基本移动(移动速度+特殊debuff)
	//void attacked(); //怪物受到攻击(移除攻击特效？)
	//void showHpRate();  //实时更新血条
	//void defeated(); //怪物被打败(音效+金币更新+清除)
	//void eatCarrot();      //怪物触碰到萝卜(萝卜掉血(交互)+移除+死亡音效)
    static cocos2d::Sprite* createSprite();
	virtual bool init();
	CREATE_FUNC(Enemy);
	virtual void update(float dt);
	void setType(int selection);
	void declineHp(Tower_information tower);
};


/*update() {
	static x = start.x;
	static y = start.y;

	this->setposition(Vec2(x + 10 * dx, y + 10 * dy));

}*/

void enemy_appear(int species, int model, int picture,int x,int y,cocos2d::Layer*this_layer);

/*appear() {
	auto new_enemy = Enemy::create();
	this_layer->Addchild(new_enemy);
}*/