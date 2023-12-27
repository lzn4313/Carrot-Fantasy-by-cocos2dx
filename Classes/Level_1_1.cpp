#include"Level_1_1.h"
#include"sound&music.h"
#include"GameData.h"
#include"GameScene.h"
#include"enemy.h"

USING_NS_CC;
extern int if_speed_up;//�Ƿ����
extern int if_pause;//�Ƿ���ͣ
extern int game_money;//��Ǯ
extern int game_waves;//��ǰ����
extern int max_waves;//�ܲ���
extern char game_map[7][12];//������ͼ����
extern int tower_available[3];//�ɽ���������洢vector

std::vector<LevelPath> levelPath;//��cocos�Դ�

/*******************************  ������  ************************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}
/**********************************  Level_1_1  ***********************************/
Layer* Level_1_1::createLayer()
{
    return Level_1_1::create();
}
//��ʼ��
bool Level_1_1::init()
{
    if (!Layer::init()) {
        return false;
    }
    //��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /***********************  ����ȫ�ֱ�����ʼ��  *******************/
    //���½�Ǯ��ʾ
    game_money = 450;
    //���²�����ʾ
    game_waves = 1; 
    max_waves = 15;
    //���µ�ͼ
    const char level_1_1_map[7][12] = {
       {0,0,0,1,1,1,1,1,1,0,0,0},
       {0,1,0,1,1,1,1,1,1,0,1,0},
       {0,1,0,0,1,0,0,1,0,0,1,0},
       {0,1,1,0,1,1,1,1,0,1,1,0},
       {0,1,1,1,1,1,1,1,1,1,1,0},
       {0,0,0,0,0,0,0,0,0,0,0,0},
       {0,0,0,0,0,0,0,0,0,0,0,0}
    };
    for (int i = 0; i <7; i++) {
        for (int j = 0; j < 12; j++) {
            game_map[i][j] = level_1_1_map[i][j];
        }
    }
    //���·�����
    tower_available[0] = 1;
    tower_available[1] = 2;
    tower_available[2] = -1;
    /***********************  ����  ************************/
    auto bg_image = Sprite::create("/Level_1_1/Level_1_1_bg.png");
    if (bg_image == nullptr) {
        problemLoading("'Level_1_1_bg.png'");
    }
    bg_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(bg_image);
    //���ֵ�
    auto start_point = Sprite::create("/Level_1_1/startPoint.PNG");
    if (start_point == nullptr) {
        problemLoading("'startPoint.PNG'");
    }
    pos start_position = { 1,1 };
    vec2 vec = trans_ij_to_xy(start_position);
    start_point->setPosition(Vec2(vec.x, vec.y));
    this->addChild(start_point);
    
    Enemy barrier[8];
    pos position[8] = {3,2,2,4,2,7,3,9,4,5,0,3,0,5,0,7};
    barrier[0].appear(BARRIER, BARRIER_ONE, 1, position[0], this);
    barrier[1].appear(BARRIER, BARRIER_ONE, 0, position[1], this);
    barrier[2].appear(BARRIER, BARRIER_ONE, 0, position[2], this);
    barrier[3].appear(BARRIER, BARRIER_ONE, 1, position[3], this);
    barrier[4].appear(BARRIER, BARRIER_TWO, 0, position[4], this);
    barrier[5].appear(BARRIER, BARRIER_FOUR, 1, position[5], this);
    barrier[6].appear(BARRIER, BARRIER_FOUR, 0, position[6], this);
    barrier[7].appear(BARRIER, BARRIER_FOUR, 1, position[7], this);
    

    //��¼·��
    
    LevelPath temp;
    {
        temp = { 1,1,'s' }; levelPath.push_back(temp);
        temp = { 2,1,'s' }; levelPath.push_back(temp);
        temp = { 3,1,'s' }; levelPath.push_back(temp);
        temp = { 4,1,'r' }; levelPath.push_back(temp);
        temp = { 4,2,'r' }; levelPath.push_back(temp);
        temp = { 4,3,'r' }; levelPath.push_back(temp);
        temp = { 4,4,'w' }; levelPath.push_back(temp);
        temp = { 3,4,'r' }; levelPath.push_back(temp);
        temp = { 3,5,'r' }; levelPath.push_back(temp);
        temp = { 3,6,'r' }; levelPath.push_back(temp);
        temp = { 3,7,'s' }; levelPath.push_back(temp);
        temp = { 4,7,'r' }; levelPath.push_back(temp);
        temp = { 4,8,'r' }; levelPath.push_back(temp);
        temp = { 4,9,'r' }; levelPath.push_back(temp);
        temp = { 4,10,'w' }; levelPath.push_back(temp);
        temp = { 3,10,'w' }; levelPath.push_back(temp);
        temp = { 2,10,'w' }; levelPath.push_back(temp);
        temp = { 1,10,'o' }; levelPath.push_back(temp);
    }
    
    Enemy monster;
    pos ab = { 1,1 };
    monster.appear(MONSTER, MONSTER_HUGE, 0, ab, this);
    
    return true;
}




