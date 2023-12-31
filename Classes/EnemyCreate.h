#include "cocos2d.h"
#include"GameScene.h"
#include<vector>
using namespace std; 
USING_NS_CC;


class EnemyCreate :public cocos2d::Layer
{
private:
	int level;
	int current_waves;
	int max_waves;
	pos start_position;
	vector<vector<int>> monster_data;
public:
	static cocos2d::Layer* createLayer();
	virtual bool init();
	CREATE_FUNC(EnemyCreate);
	virtual void update(float dt);

	void SetLevel(int level_selection);
	void monster_appear(int Type);
	void barrier_appear(int Type, pos position);
	void barrier_appear(int Type, pos position_l, pos position_r);
	void barrier_appear(int Type, pos position_l, pos position_r, pos position_u);
	void start();
	void create_waves();
};
