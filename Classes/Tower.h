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

const static int Tower_Value[4] = { 100,120,160,160 };
const static int Tower_Attack[4] = { 50,20,60,80 };
const static int Tower_Attack_Speed[4] = { 12,4,4,3 };

struct Tower_information {
	int name_tag;//��¼���Ʊ�ǩ
	int value;//��¼��ǰ��ֵ
	int attack;//��¼���ι�����
	int attack_speed;//��¼�����ٶ�
	int attack_range;//��¼������Χ
	int attack_special;//��¼���⹥��Ч������͸�����١����ѵȣ�
	int level;//��¼�ȼ�
};

/*��̨��*/
class Tower {
private:
	Tower_information tower;
public:
	int get_now_money(int tag);//��õ�ǰ��ֵ
	void build_tower(pos position, int tag, cocos2d::Layer* this_layer);//�������Ʊ�ǩ��ָ��λ�ý���һ����̨
};

int getMoney(int tag);//�������Ʊ�ǩ��ó�ʼ��ֵ