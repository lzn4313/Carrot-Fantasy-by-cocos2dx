#include "enemy.h"
#include"sound&music.h"
#include"GameData.h"
#include"GameScene.h"
#include"Level_1_1.h"
#include <vector>
USING_NS_CC;
extern int if_speed_up;
extern int game_waves;
extern const char level_1_1_map[7][12];

using namespace cocos2d::ui;
//不是cocos自带

void Enemy::appear(int species, int model, int picture,pos position, cocos2d::Layer* this_layer)
{

	if (species == BARRIER) {
		enemy.enemy_picture=Sprite::create();
		enemy.damage = 0;
		enemy.speed = 0;
		string pictureText[6] = { "One1.PNG","One2.PNG","Two1.PNG","Two2.PNG","Four1.PNG","Four2.PNG" };
		string baseRoad = BARRIER_BASE_PICTURE;
		Vec2 change_position ;
		switch (model) {
		case BARRIER_ONE:
			enemy.hp = BARRIER_HP_ONE;
			enemy.coin = BARRIER_COIN_ONE;
			enemy.enemy_picture->setTexture(baseRoad+pictureText[picture]);
			break;
		case BARRIER_TWO:
			enemy.hp = BARRIER_HP_TWO;
			enemy.coin = BARRIER_COIN_TWO;
			picture+=2;
			enemy.enemy_picture->setTexture(baseRoad + pictureText[picture]);
			change_position.x = 0.25;
			change_position.y = 0.5;
			enemy.enemy_picture->setScale( 80/enemy.enemy_picture->getContentSize().height );
			enemy.enemy_picture->setAnchorPoint(change_position);
			
			break;
		case BARRIER_FOUR:
			enemy.hp = BARRIER_HP_FOUR;
			enemy.coin = BARRIER_COIN_FOUR;
			picture+=4;
			change_position.x = 0.25;
			change_position.y = 0.75;
			enemy.enemy_picture->setAnchorPoint(change_position);
			enemy.enemy_picture->setTexture(baseRoad + pictureText[picture]);
			
			
			break;
		}	
		vec2 startPosition = trans_ij_to_xy(position);
		enemy.enemy_picture->setPosition(startPosition.x, startPosition.y);
		this_layer->addChild(enemy.enemy_picture);
	}
	else if (species == MONSTER) {
		Vector<SpriteFrame*> monster_self_change;
		enemy.enemy_picture = Sprite::create();
		string baseRoad = MONSTER_BASE_PICTURE;
		string pictureText[6] = { "normal01-1.PNG","normal01-2.PNG","fast01-1.PNG","fast01-2.PNG","huge01-1.PNG","huge01-2.PNG" };
		vec2 startPosition = trans_ij_to_xy(position);
		switch (model) {
			
		case MONSTER_NORMAL:
			enemy.damage = 1;
			enemy.coin = MONSTER_COIN_NORMAL;
			enemy.hp = MONSTER_NORMAL_HP * game_waves;
			enemy.speed = MONSTER_NORMAL_SPEED;
			monster_self_change.pushBack(SpriteFrame::create(baseRoad + pictureText[1], Rect(0, 0, 90, 90)));
			monster_self_change.pushBack(SpriteFrame::create(baseRoad + pictureText[0], Rect(0, 0, 90, 90)));
			
			break;
		case MONSTER_FAST: 
			enemy.damage = 1;
			enemy.coin = MONSTER_COIN_NORMAL;
			enemy.hp = MONSTER_FAST_HP * game_waves;
			enemy.speed = MONSTER_FAST_SPEED;
			monster_self_change.pushBack(SpriteFrame::create(baseRoad + pictureText[2], Rect(0, 0, 154, 84)));
			monster_self_change.pushBack(SpriteFrame::create(baseRoad + pictureText[3], Rect(0, 0, 154, 84)));
			break;
		case MONSTER_HUGE:
			enemy.damage = 1;
			enemy.coin = MONSTER_COIN_HUGE;
			enemy.hp = MONSTER_HUGE_HP * game_waves;
			enemy.speed = MONSTER_HUGE_SPEED;
			monster_self_change.pushBack(SpriteFrame::create(baseRoad + pictureText[4], Rect(0, 0, 183, 148)));
			monster_self_change.pushBack(SpriteFrame::create(baseRoad + pictureText[5], Rect(0, 0, 183, 148)));
			break;
		}
		
		
		enemy.enemy_picture->setPosition(startPosition.x, startPosition.y);
		
		
		enemy.enemy_picture->runAction(RepeatForever::create(Sequence::create(Animate::create(Animation::createWithSpriteFrames(monster_self_change, 0.25/(1+if_speed_up))), nullptr)));

		this_layer->addChild(enemy.enemy_picture);
		Scheduler(move());
		
	}

}

void Enemy::move()
{
	Vec2 place;
	vec2 place2;          //求得pos位置后转为格子中心位置
	place2.x = place.x;
	place2.y = place.y;
	place=enemy.enemy_picture->getAnchorPoint();
	pos currentPosition=trans_xy_to_ij(place2);
	place2 = trans_ij_to_xy(currentPosition);
	bool flag;
	flag = (place2.x == place.x) && (place.y = place2.y)&&((currentPosition.i!=levelPath.at(0).point.i) || (currentPosition.j != levelPath.at(0).point.j));//是否到达下一点且不为起点
	if (flag)
		enemy.count++;
	if (levelPath.at(enemy.count).direction == 's') {
		enemy.enemy_picture->runAction(MoveBy::create(1, Vec2(0,-enemy.enemy_picture->getContentSize().height/2)));
	}



}

 void Enemy::update(float dt)
{
	 Enemy::move();

}
