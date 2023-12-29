#include "cocos2d.h"
#include "GameScene.h"
using namespace std;

/*�������ǩ��Ӧ*/
#define Tower_Bottle 1
#define Tower_Shit 2
#define Tower_Fan 3
#define Tower_Star 4

/*����Ч�����ǩ��Ӧ*/
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
	int name_tag;//��¼���Ʊ�ǩ
	int value;//��¼��ǰ��ֵ
	float attack;//��¼���ι�����
	float attack_speed;//��¼�����ٶ�
	float attack_range;//��¼������Χ
	int attack_special;//��¼���⹥��Ч������͸�����١����ѵȣ�
	int level;//��¼�ȼ�
	cocos2d::Sprite* tower_base;//��̨����
	Tower_body* tower_body;//��̨����

	Tower_information(int t = 0, int v = 0, float atk = 0, float atk_speed = 0, float atk_r = 1, int atk_special = 0, int L = 1)
		:name_tag(t), value(v), attack(atk), attack_speed(atk_speed), attack_range(atk_r), attack_special(atk_special), level(L)
	{
		tower_base = nullptr;
		tower_body = nullptr;
	}//���캯��

};

class Tower_body:public cocos2d::Sprite {
	friend class Tower;
private:
	Tower_information tower;
public:
	//���캯��
	static cocos2d::Sprite* createSprite();
	virtual bool init();
	virtual void update(float dt);//ʵʱ�жϷ�Χ���Ƿ��е��ˣ����򹥻�
	void bullet_fly(Tower_information tower, cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Layer* this_layer);//�ӵ����ж���
	void attack_once(Tower_information tower, cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Layer* this_layer);//���ι�������
	CREATE_FUNC(Tower_body);
};

/*��̨��*/
class Tower {
private:
	Tower_information Tower;
public:
	void build_tower(pos position, int tag, cocos2d::Layer* this_layer);//�������Ʊ�ǩ��ָ��λ�ý���һ����̨
	void up_level_tower(pos position, cocos2d::Layer* this_layer);//������̨
	void sell_tower(pos position, cocos2d::Layer* this_layer);//������̨
	float get_attack_range(pos position);//��ù�����Χ
	int get_level(pos position);//��õȼ�
	int get_level_up_money(pos position);//�������������
	int get_sell_money(pos position);//��ó��ۼ۸�
	//void bullet_fly(Tower_information tower, cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Layer* this_layer);//�ӵ����ж���
	//void attack_once(Tower_information tower, cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Layer* this_layer);//���ι�������
};

int getMoney(int tag);//�������Ʊ�ǩ��ó�ʼ��ֵ