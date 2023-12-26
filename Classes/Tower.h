#include "cocos2d.h"
#include "GameScene.h"
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

const static int Tower_Value[4] = { 100,120,160,160 };
const static float Tower_Attack[4] = { 50,20,60,80 };
const static float Tower_Attack_Speed[4] = { 12,4,4,3 };

struct Tower_information {
	int name_tag;//记录名称标签
	int value;//记录当前价值
	float attack;//记录单次攻击力
	float attack_speed;//记录攻击速度
	float attack_range;//记录攻击范围
	int attack_special;//记录特殊攻击效果（穿透、减速、分裂等）
	int level;//记录等级
	cocos2d::Sprite* tower_base;//炮台底座
	cocos2d::Sprite* tower_body;//炮台主体

	Tower_information(int t = 0, int v = 0, float atk = 0, float atk_speed = 0, float atk_r = 1, int atk_special = 0, int L = 1)
		:name_tag(t), value(v), attack(atk), attack_speed(atk_speed), attack_range(atk_r), attack_special(atk_special), level(L)
	{
		tower_base = nullptr;
		tower_body = nullptr;
	}//构造函数
};

/*炮台类*/
class Tower {
private:
	Tower_information tower;
public:
	void build_tower(pos position, int tag, cocos2d::Layer* this_layer);//根据名称标签在指定位置建造一个炮台
	void up_level_tower(pos position, cocos2d::Layer* this_layer);//升级炮台
	void sell_tower(pos position, cocos2d::Layer* this_layer);//出售炮台
	float get_attack_range(pos position);//获得攻击范围
	int get_level(pos position);//获得等级
	int get_level_up_money(pos position);//获得升级所需金币
	int get_sell_money(pos position);//获得出售价格
};

int getMoney(int tag);//根据名称标签获得初始价值