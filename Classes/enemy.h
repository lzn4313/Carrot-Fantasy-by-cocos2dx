#pragma once
#include "cocos2d.h"
#include "GameScene.h"


#define BARRIER 0
#define MONSTER 1

#define BARRIER_ONE   1     //һ����ϰ�
#define BARRIER_TWO   2     //������ϰ�
#define BARRIER_FOUR  4     //�ĸ���ϰ�

#define BARRIER_HP_ONE     1600               //һ���ϰ���Ѫ
#define BARRIER_HP_TWO     3 * BARRIER_HP_ONE //�����ϰ���Ѫ
#define BARRIER_HP_FOUR    3 * BARRIER_HP_TWO //�ĸ��ϰ���Ѫ

#define BARRIER_COIN_ONE     50 
#define BARRIER_COIN_TWO     2 * BARRIER_COIN_ONE //�����ϰ���Ѫ
#define BARRIER_COIN_FOUR    2 * BARRIER_COIN_TWO //�ĸ��ϰ���Ѫ

#define MONSTER_NORMAL 0    //�е�Ѫ�����е��ٶ�
#define MONSTER_FAST   1    //��Ѫ�������ٶ�
#define MONSTER_HUGE   2    //��Ѫ�����ٶȽϵ�

#define MONSTER_FAST_HP       20                     //���ٹֵĻ���Ѫ��
#define MONSTER_NORMAL_HP     3 * MONSTER_FAST_HP    //��ͨ��Ѫ��
#define MONSTER_HUGE_HP       3 * MONSTER_NORMAL_HP  //���͹�Ѫ��

#define MONSTER_HUGE_SPEED    100                        //���͹��ƶ��ٶȣ���ţ�������Ķ���������
#define MONSTER_NORMAL_SPEED  2*MONSTER_HUGE_SPEED     //����������
#define MONSTER_FAST_SPEED    2*MONSTER_NORMAL_SPEED   //���ٹ�����

#define MONSTER_COIN_NORMAL   18                       //�����ֺ͸��ٹֵ�����
#define MONSTER_COIN_HUGE     188                      //���͹ֵ�����

#define BARRIER_BASE_PICTURE  "/Enemy/barrier/0/"        //�ϰ�·��
#define MONSTER_BASE_PICTURE  "/Enemy/monster/0/"


extern struct Tower_information;
struct Enemy_information {
	int hp;                                       //��¼����Ѫ��
	int speed;                                    //��¼�����ƶ��ٶ�
	int coin;                                     //Я���ܲ���
	int damage;                                   //���ܲ���ɵ��˺�
	cocos2d::Sprite* enemy_picture;               //�ϰ���ͼ
	int count;                                    //�߹��ĸ�����
	int time = 0;                                 //��¼��Чʱ��
	int origin_speed;                             //��¼��̬���ٶ�
	int full_hp;                                  //��¼��ѪѪ��
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
	//void appear(int species, int model, int picture, pos position, cocos2d::Layer* this_layer);                            //����(��������Ч)���ϰ��ϳ������ֱ���趨��ʼֵ
	///*void appear(int species, int picture, int hp, int speed, int coin, int damage, pos position, cocos2d::Layer* this_layer); *///������ϰ��ϳ�   �����趨��ʼֵ
	////void selfAction();//������ͼ����ı仯
	//void move();     //����Ļ����ƶ�(�ƶ��ٶ�+����debuff)
	//void attacked(); //�����ܵ�����(�Ƴ�������Ч��)
	//void showHpRate();  //ʵʱ����Ѫ��
	//void defeated(); //���ﱻ���(��Ч+��Ҹ���+���)
	//void eatCarrot();      //���ﴥ�����ܲ�(�ܲ���Ѫ(����)+�Ƴ�+������Ч)
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