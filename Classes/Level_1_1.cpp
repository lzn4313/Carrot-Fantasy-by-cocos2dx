#include"Level_1_1.h"
#include"sound&music.h"
#include"GameData.h"
#include"GameScene.h"
#include"enemy.h"
#include<algorithm>

USING_NS_CC;
using namespace std;
extern int if_speed_up;//是否加速
extern int if_pause;//是否暂停
extern int game_money;//金钱
extern int game_waves;//当前波数
extern int max_waves;//总波数
extern char game_map[7][12];//辅助地图数组
extern int tower_available[3];//可建造防御塔存储vector
extern pos carrot_position;
extern vector<LevelPath> levelPath;//非cocos自带
extern vector<Enemy*> barrier;
extern vector<Enemy*> monster;

/*******************************  错误处理  ************************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}
/**********************************  Level_1_1  ***********************************/
Layer* Level_1_1::createLayer()
{
    return Level_1_1::create();
}
//初始化
bool Level_1_1::init()
{
    if (!Layer::init()) {
        return false;
    }
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /***********************  部分全局变量初始化  *******************/
    //更新金钱显示
    game_money = 450;
    //更新波数显示
    game_waves = 0; 
    max_waves = 15;
    //更新地图
    const char level_1_1_map[7][12] = {
       {0,0,0,1,1,1,1,1,1,0,0,0},
       {0,1,0,1,1,1,1,1,1,0,5,0},
       {0,1,0,0,1,0,0,1,0,0,1,0},
       {0,1,1,0,1,1,1,1,0,1,1,0},
       {0,1,1,1,1,1,1,1,1,1,1,0},
       {1,0,0,0,0,0,0,0,0,0,0,1},
       {1,1,1,0,0,0,0,0,0,1,1,1}
    };
    for (int i = 0; i <7; i++) {
        for (int j = 0; j < 12; j++) {
            game_map[i][j] = level_1_1_map[i][j];
            if (game_map[i][j] == CARROT) {
                carrot_position = { i,j };
            }
        }
    }
    //更新防御塔
    tower_available[0] = 1;
    tower_available[1] = 2;
    tower_available[2] = -1;
    /***********************  背景  ************************/
    auto bg_image = Sprite::create("/Level/Level_1_1_bg.png");
    if (bg_image == nullptr) {
        problemLoading("'Level_1_1_bg.png'");
    }
    bg_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(bg_image);
    //出怪点
    auto start_point = Sprite::create("/Level/startPoint.PNG");
    if (start_point == nullptr) {
        problemLoading("'startPoint.PNG'");
    }
    pos start_position = { 1,1 };
    vec2 vec = trans_ij_to_xy(start_position);
    start_point->setPosition(Vec2(vec.x, vec.y));
    this->addChild(start_point);
    //记录路径
    levelPath.clear();
    LevelPath temp;
    {
        temp = { {1,1},'s' };levelPath.push_back(temp);
        temp = { {2,1}, 's' }; levelPath.push_back(temp);
        temp = { {3,1},'s' }; levelPath.push_back(temp);
        temp = { {4,1},'d' }; levelPath.push_back(temp);//'r'表示右走
        temp = { {4,2}, 'd' }; levelPath.push_back(temp);
        temp = { {4,3},'d' }; levelPath.push_back(temp);
        temp = { {4,4},'w' }; levelPath.push_back(temp);
        temp = { {3,4},'d' }; levelPath.push_back(temp);
        temp = { {3,5},'d' }; levelPath.push_back(temp);
        temp = { {3,6},'d' }; levelPath.push_back(temp);
        temp = { {3,7},'s' }; levelPath.push_back(temp);
        temp = { {4,7},'d' }; levelPath.push_back(temp);
        temp = { {4,8},'d' }; levelPath.push_back(temp);
        temp = { {4,9},'d' }; levelPath.push_back(temp);
        temp = { {4,10},'w' }; levelPath.push_back(temp);
        temp = { {3,10},'w' }; levelPath.push_back(temp);
        temp = { {2,10},'w' }; levelPath.push_back(temp);
        temp = { {1,10},'o' }; levelPath.push_back(temp);
    }
    return true;
}




