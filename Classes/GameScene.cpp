#include"Level_1_1.h"
#include"GameScene.h"
#include"sound&music.h"
#include"GameData.h"
#include"ui/CocosGUI.h"
#include<string>
#include<vector>
USING_NS_CC;
using namespace cocos2d::ui;
/*******************************  ������  ************************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}
/**********************  ȫ�ֱ���  ***********************/
int level_selection;//�ؿ�ѡ��
int if_speed_up;//�Ƿ����
int if_pause;//�Ƿ���ͣ
int game_money;//��Ǯ
int game_waves;//��ǰ����
int max_waves;//�ܲ���
char game_map[7][12];//������ͼ����
int tower_available[3];//�ɽ���������洢
/**********************************  GameScene  ***********************************/
Scene* GameScene::createScene()
{
    return GameScene::create();
}
/*��ʼ��*/
bool GameScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    /**********************  ����ȫ�ֱ�����ʼ��  **********************/
    if_speed_up = 0;//Ĭ�ϲ�����
    if_pause = 0;//Ĭ�ϲ���ͣ
    /**********************  ѡ��  ******************************/
    if (level_selection == 1) {
        auto level_1_1 = Level_1_1::createLayer();
        level_1_1->setName("PlayingLevel");
        this->addChild(level_1_1, -1);
    }
    /***********************  �˵���  ***************************/
    auto menu_layer = GameMenu::createLayer();
    menu_layer->setName("GameMenu");
    this->addChild(menu_layer, 1);

    return true;
}
/**********************************  GameMenu  ********************************/
Layer* GameMenu::createLayer()
{
    return GameMenu::create();
}
//��ʼ��
bool GameMenu::init()
{
    if (!Layer::init()) {
        return false;
    }
    //��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //����
    auto menu_image = Sprite::create("/GameScene/touming-hd.pvr_13.PNG");
    menu_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - menu_image->getContentSize().height / 2));
    this->addChild(menu_image);
    //��Ǯ��ʾ
    auto money_label = Label::createWithTTF(to_string(game_money), "/fonts/Marker Felt.ttf", 32);
    money_label->setName("MoneyLabel");
    money_label->setAnchorPoint(Vec2(0, 0.5));
    money_label->setPosition(Vec2(origin.x + visibleSize.width * 0.1,
        origin.y + visibleSize.height * 0.95));
    this->addChild(money_label);
    //������ʾ
    auto waves_image = Sprite::create("/GameScene/gameover0-hd_0.PNG");
    waves_image->setPosition(Vec2(origin.x + visibleSize.width * 0.4,
        origin.y + visibleSize.height * 0.95));
    this->addChild(waves_image);
    auto waves_label = Label::createWithTTF(to_string(game_waves / 10 % 10) + "   " + to_string(game_waves % 10), "/fonts/Marker Felt.ttf", 32);
    waves_label->setName("WavesLabel");
    waves_label->setColor(Color3B::YELLOW);
    waves_label->setPosition(Vec2(origin.x + visibleSize.width * 0.4,
        origin.y + visibleSize.height * 0.94));
    this->addChild(waves_label);
    auto waves_txt = Label::createWithTTF("/ " + to_string(max_waves) + " Waves", "/fonts/Marker Felt.ttf", 32);
    waves_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.525,
        origin.y + visibleSize.height * 0.94));
    this->addChild(waves_txt);
    //���ٿ���
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    auto speed_up_on_sprite = Sprite::create("/GameScene/touming-hd.pvr_7.PNG");
    auto speed_up_on = MenuItemSprite::create(speed_up_on_sprite, speed_up_on_sprite);
    auto speed_up_off_sprite = Sprite::create("/GameScene/touming-hd.pvr_9.PNG");
    auto speed_up_off = MenuItemSprite::create(speed_up_off_sprite, speed_up_off_sprite);
    auto speed_toggle = MenuItemToggle::createWithCallback([&](Ref* psender) {
        button_sound_effect();//������Ч
        if (if_speed_up == 0) {//����ѡ�����ʾ����������
            if_speed_up = 1;
        }
        else {
            if_speed_up = 0;
        }
        }, speed_up_on, speed_up_off, nullptr);
    speed_toggle->setPosition(Vec2(origin.x + visibleSize.width * 0.7,
        origin.y + visibleSize.height * 0.94));
    menu->addChild(speed_toggle);
    //��ͣ����
    //��ͣ����Ĵ�ɫ��
    auto black_layer = LayerColor::create(Color4B::BLACK);
    black_layer->setPosition(Vec2::ZERO);
    black_layer->setOpacity(85);
    black_layer->setVisible(false);
    this->addChild(black_layer, -1);
    //��ͣ������ʾ
    auto paused = Sprite::create("/GameScene/paused.png");
    paused->setScale(1.4);
    paused->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height * 0.95));
    paused->setVisible(false);
    this->addChild(paused);
    auto pause_off_sprite = Sprite::create("/GameScene/touming-hd.pvr_12.PNG");
    auto pause_off = MenuItemSprite::create(pause_off_sprite, pause_off_sprite);
    auto pause_on_sprite = Sprite::create("/GameScene/touming-hd.pvr_11.PNG");
    auto pause_on = MenuItemSprite::create(pause_on_sprite, pause_on_sprite);
    auto pause_toggle = MenuItemToggle::createWithCallback([=](Ref* psender) {
        button_sound_effect();//������Ч
        if (if_pause == 0) {//����ѡ�����ʾ��ͣ
            if_pause = 1;
            black_layer->setVisible(true);
            paused->setVisible(true);
            waves_image->setVisible(false);
            waves_label->setVisible(false);
            waves_txt->setVisible(false);
        }
        else {
            if_pause = 0;
            black_layer->setVisible(false);
            paused->setVisible(false);
            waves_image->setVisible(true);
            waves_label->setVisible(true);
            waves_txt->setVisible(true);
        }
        }, pause_off, pause_on, nullptr);
    pause_toggle->setPosition(Vec2(origin.x + visibleSize.width * 0.8,
        origin.y + visibleSize.height * 0.94));
    menu->addChild(pause_toggle);
    //ѡ��
    auto options_btn = Button::create("/GameScene/touming-hd.pvr_28.PNG", "/GameScene/touming-hd.pvr_26.PNG");
    options_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.88,
        origin.y + visibleSize.height * 0.94));
    options_btn->addTouchEventListener([this](Ref* psender, Button::TouchEventType type) {
        switch (type) {
            case Button::TouchEventType::BEGAN:
                break;
            case Button::TouchEventType::MOVED:
                break;
            case Button::TouchEventType::CANCELED:
                break;
            case Button::TouchEventType::ENDED:
                button_sound_effect();//������Ч
                options();
                break;
        }
        });
    this->addChild(options_btn);
    //�������
    Sprite* grid[7][12];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 12; j++) {
            grid[i][j] = Sprite::create("/GameScene/StartSprite.png");
            grid[i][j]->setPosition(Vec2(40 + 80 * j, 40 + 80 * (6 - i)));
            grid[i][j]->setTag(i * 100 + j);
            grid[i][j]->setVisible(false);
            this->addChild(grid[i][j], -1);
        }
    }
    //��Ϸ��ʼ�ĵ���ʱ
    start();
    //��Ϸ��ʼ��Ĵ����¼�
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        if (touch->getLocation().y < 560) {
            vec2 vec;
            vec.x = touch->getLocation().x;
            vec.y = touch->getLocation().y;
            pos position = trans_xy_to_ij(vec);
            if (game_map[position.i][position.j] == DISABLED) {
                return false;
            }
        }
        return true;
    };
    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        if (touch->getLocation().y < 560) {
            vec2 vec;
            vec.x = touch->getLocation().x;
            vec.y = touch->getLocation().y;
            pos position = trans_xy_to_ij(vec);
            Node* node = this->getChildByTag(100 * position.i + position.j);
            Sprite* grid = static_cast<Sprite*>(node);
            if (game_map[position.i][position.j] == EMPTY) {
                build(position, tower_available);
            }
            else if(game_map[position.i][position.j] == TOWER){
                tower_operations(position);
            }
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


    this->scheduleUpdate();
    return true;
}
//��дupdate����
void GameMenu::update(float dt) {
    //ʵʱ���½�Ǯ����
    Node* money_node = this->getChildByName("MoneyLabel");
    Label* money_label = static_cast<Label*>(money_node);
    money_label->setString(to_string(game_money));
    //ʵʱ���²���
    Node* waves_node = this->getChildByName("WavesLabel");
    Label* waves_label = static_cast<Label*>(waves_node);
    waves_label->setString(to_string(game_waves / 10 % 10) + "   " + to_string(game_waves % 10));
}
//���ý���
void GameMenu::options() {
    button_sound_effect();//������Ч
    //��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /************************  ��ɫ��  *****************************/
    auto black_layer = LayerColor::create(Color4B::BLACK);
    black_layer->setPosition(Vec2::ZERO);
    black_layer->setOpacity(90);
    this->addChild(black_layer, 1);
    /************************  �¼�������  *****************************/
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);//������û����ȷ�����밴��ť���ܷ�����һҳ
    listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);

    /******************  ����  ***************************/
    auto options_bg = Sprite::create("/GameScene/options_bg.png");
    options_bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    black_layer->addChild(options_bg);
    /*******************  �˵�  **************************/
    auto options_menu = Menu::create();
    options_menu->setPosition(Vec2::ZERO);
    black_layer->addChild(options_menu);
    //������Ϸ
    auto resume_btn = MenuItemImage::create("/GameScene/resume_normal.png", "/GameScene/resume_selected.png");
    resume_btn->setPosition(Vec2(visibleSize.width *0.49, visibleSize.height * 0.67));
    resume_btn->setCallback([this, black_layer](Ref* psender) {//��ť�ص��¼���������һ��
        button_sound_effect();
        this->removeChild(black_layer);
        });
    options_menu->addChild(resume_btn);
    //���¿�ʼ
    auto restart_btn = MenuItemImage::create("/GameScene/restart_normal.png", "/GameScene/restart_selected.png");
    restart_btn->setPosition(Vec2(visibleSize.width *0.49, visibleSize.height * 0.52));
    restart_btn->setCallback([this, black_layer](Ref* psender) {//��ť�ص��¼���������һ��
        button_sound_effect();
        this->removeChildByName("PlayingLevel");
        if (level_selection == 1) {
            auto level_1_1 = Level_1_1::createLayer();
            level_1_1->setName("PlayingLevel");
            this->addChild(level_1_1, -3);
            start();
        }
        this->removeChild(black_layer);
        });
    options_menu->addChild(restart_btn);
    //ѡ��ؿ�
    auto return_btn = MenuItemImage::create("/GameScene/return_normal.png", "/GameScene/return_selected.png");
    return_btn->setPosition(Vec2(visibleSize.width *0.49, visibleSize.height * 0.37));
    return_btn->setCallback([this, black_layer](Ref* psender) {//��ť�ص��¼���������һ��
        button_sound_effect();
        Director::getInstance()->popScene();
        });
    options_menu->addChild(return_btn);

}
//��ʼ
void GameMenu::start()
{   
    //��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //����ʱ��ʱ����Ϸ����ͣ��
    if_pause = 1;
    //����ʱҳ
    auto time_layer = Layer::create();
    this->addChild(time_layer);
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, time_layer);
    //����ʱ������
    auto panel = Sprite::create("/GameScene/Items02-hd_165.PNG");
    panel->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    time_layer->addChild(panel);
    //����ʱ����
    auto number = Sprite::create("/GameScene/Items02-hd_68.PNG");
    number->setPosition(Vec2(origin.x + visibleSize.width * 0.51,
        origin.y + visibleSize.height / 2));
    time_layer->addChild(number);
    //����ʱתȦ
    auto circle = Sprite::create("/GameScene/Items02-hd_50.PNG");
    circle->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    time_layer->addChild(circle);
    circle->runAction(Sequence::create(Repeat::create(RotateBy::create(1, -360), 3), FadeOut::create(0.1), nullptr));
    panel->runAction(Sequence::create(DelayTime::create(3), FadeOut::create(0.1), nullptr));
   //����֡����������ֵĵ���ʱ
    Vector<SpriteFrame*> frame;
    frame.pushBack(SpriteFrame::create("/GameScene/Items02-hd_68.PNG", Rect(0, 0, 95, 114)));
    frame.pushBack(SpriteFrame::create("/GameScene/Items02-hd_92.PNG", Rect(0, 0, 95, 114)));
    frame.pushBack(SpriteFrame::create("/GameScene/Items02-hd_88.PNG", Rect(0, 0, 95, 114)));
    number->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 1)),FadeOut::create(0.1),nullptr));
    //����ʱ��ʱ�����п��ø����˸
    Sprite* grid[7][12];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 12; j++) {
            grid[i][j] = static_cast<Sprite*>(this->getChildByTag(i * 100 + j));
            if (game_map[i][j] == 0) {
                grid[i][j]->setTexture("/GameScene/StartSprite.png");
                grid[i][j]->runAction(Blink::create(3, 2));
            }
        }
    }
    //���������ֲ�ɾ��
    auto start_call_back = CallFunc::create([=]() {
        this->removeChild(time_layer);
        });
    time_layer->runAction(Sequence::create(DelayTime::create(3.1), start_call_back, nullptr));
    if_pause = 0;
}
//����
void GameMenu::build(pos position, int tower_available[]) {
    //�������ֲ�
    auto touch_layer = Layer::create();
    this->addChild(touch_layer);
    //��ʾ
    Node* node = this->getChildByTag(100 * position.i + position.j);
    Sprite* sprite = static_cast<Sprite*>(node);
    sprite->setTexture("/GameScene/Grid.png");
    sprite->setVisible(true);
    //��̨����
    auto sprite_1 = Sprite::create();
    auto sprite_2 = Sprite::create();
    auto sprite_3 = Sprite::create();
    if (tower_available[2] == -1) {
        string str = "/GameScene/Tower/";
        //��һ����̨
        string str_1 = str + to_string(tower_available[0]) + "/";
        if (game_money </*getMoney(tower_available[0])*/100) {
            sprite_1->setTexture(str_1 + "CanClick0.PNG");
        }
        else {
            sprite_1->setTexture(str_1 + "CanClick1.PNG");
        }
        vec2 vec = trans_ij_to_xy(position);
        sprite_1->setPosition(Vec2(vec.x - sprite_1->getContentSize().width / 2,
            vec.y + sprite_1->getContentSize().height));
        touch_layer->addChild(sprite_1);
        //�ڶ�����̨
        string str_2 = str + to_string(tower_available[1]) + "/";
        if (game_money </*getMoney(tower_available[1])*/120) {
            sprite_2->setTexture(str_2 + "CanClick0.PNG");
        }
        else {
            sprite_2->setTexture(str_2 + "CanClick1.PNG");
        }
        vec = trans_ij_to_xy(position);
        sprite_2->setPosition(Vec2(vec.x + sprite_2->getContentSize().width / 2,
            vec.y + sprite_2->getContentSize().height));
        touch_layer->addChild(sprite_2);
    }
    else if (tower_available[2] != -1) {
        string str = "/GameScene/Tower/";
        //��һ����̨
        string str_1 = str + to_string(tower_available[0]) + "/";
        if (game_money </*getMoney(tower_available[0])*/100) {
            sprite_1->setTexture(str_1 + "CanClick0.PNG");
        }
        else {
            sprite_1->setTexture(str_1 + "CanClick1.PNG");
        }
        vec2 vec = trans_ij_to_xy(position);
        sprite_1->setPosition(Vec2(vec.x - sprite_1->getContentSize().width,
            vec.y + sprite_1->getContentSize().height));
        touch_layer->addChild(sprite_1);
        //�ڶ�����̨
        string str_2 = str + to_string(tower_available[1]) + "/";
        if (game_money </*getMoney(tower_available[1])*/120) {
            sprite_2->setTexture(str_2 + "CanClick0.PNG");
        }
        else {
            sprite_2->setTexture(str_2 + "CanClick1.PNG");
        }
        vec = trans_ij_to_xy(position);
        sprite_2->setPosition(Vec2(vec.x,
            vec.y + sprite_2->getContentSize().height));
        touch_layer->addChild(sprite_2);
        //��������̨
        string str_3 = str + to_string(tower_available[2]) + "/";
        if (game_money </*getMoney(tower_available[2])*/120) {
            sprite_3->setTexture(str_3 + "CanClick0.PNG");
        }
        else {
            sprite_3->setTexture(str_3 + "CanClick1.PNG");
        }
        vec = trans_ij_to_xy(position);
        sprite_3->setPosition(Vec2(vec.x + sprite_3->getContentSize().width,
            vec.y + sprite_3->getContentSize().height));
        touch_layer->addChild(sprite_3);
    }
    //������
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
    };
    listener->onTouchEnded = [this, sprite, sprite_1, sprite_2, sprite_3, touch_layer, position, tower_available](Touch* touch, Event* event) {
        //������λ���ڵ�һ������ͼ����
        if (touch->getLocation().x >= sprite_1->getPosition().x - sprite_1->getContentSize().width / 2 &&
            touch->getLocation().x <= sprite_1->getPosition().x + sprite_1->getContentSize().width / 2 &&
            touch->getLocation().y >= sprite_1->getPosition().y - sprite_1->getContentSize().height / 2 &&
            touch->getLocation().y <= sprite_1->getPosition().y + sprite_1->getContentSize().height / 2) {
            if (game_money >=/*getMoney(tower_available[0])*/100) {//��Ǯ��������
                // build_tower(position,tower_available[0]);
                log("build_tower(position, tower_available[0])");
                game_money -=/*getMoney(tower_available[0])*/100;
                sprite->setVisible(false);
                this->removeChild(touch_layer);
                game_map[position.i][position.j] = TOWER;
            }
        }
        else if (//������λ���ڵڶ�������ͼ����
            touch->getLocation().x >= sprite_2->getPosition().x - sprite_2->getContentSize().width / 2 &&
            touch->getLocation().x <= sprite_2->getPosition().x + sprite_2->getContentSize().width / 2 &&
            touch->getLocation().y >= sprite_2->getPosition().y - sprite_2->getContentSize().height / 2 &&
            touch->getLocation().y <= sprite_2->getPosition().y + sprite_2->getContentSize().height / 2) {
            if (game_money >=/*getMoney(tower_available[1])*/120) {//��Ǯ��������
                // build_tower(position, tower_available[1]);
                log("build_tower(position, tower_available[1])");
                game_money -=/*getMoney(tower_available[1])*/120;
                sprite->setVisible(false);
                this->removeChild(touch_layer);
                game_map[position.i][position.j] = TOWER;
            }
        }
        else if (//������λ���ڵ���������ͼ����
            tower_available[2] != -1 &&
            touch->getLocation().x >= sprite_3->getPosition().x - sprite_3->getContentSize().width / 2 &&
            touch->getLocation().x <= sprite_3->getPosition().x + sprite_3->getContentSize().width / 2 &&
            touch->getLocation().y >= sprite_3->getPosition().y - sprite_3->getContentSize().height / 2 &&
            touch->getLocation().y <= sprite_3->getPosition().y + sprite_3->getContentSize().height / 2) {
            if (game_money >=/*getMoney(tower_available[2])*/120) {//��Ǯ��������
                // build_tower(position, tower_available[2]);
                log("build_tower(position, tower_available[2])");
                game_money -=/*getMoney(tower_available[2])*/120;
                sprite->setVisible(false);
                this->removeChild(touch_layer);
                game_map[position.i][position.j] = TOWER;
            }
        }
        else {
            //������λ�ò���ͼ����
            sprite->setVisible(false);
            this->removeChild(touch_layer);
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, touch_layer);
}
//�Է������Ĳ���
void GameMenu::tower_operations(pos position) {
    float range_scale = 1;//getRange(position);
    int level = 1;// getLevel(position);
    int level_up_money = 100;// getLevelUpMoney(position);
    int sell_money = 100;//getSellMoney(position);
    vec2 vec = trans_ij_to_xy(position);
    //���ֲ�
    auto touch_layer = Layer::create();
    this->addChild(touch_layer);
    //��Χ��ʾ
    auto range = Sprite::create("/GameScene/Tower/AttackRange.PNG");
    range->setScale(range_scale);
    range->setPosition(Vec2(vec.x,
        vec.y));
    touch_layer->addChild(range);
    //������ʾ
    auto level_up = Sprite::create("/GameScene/Tower/Btn_CanUpLevel.png");
    if (game_money < level_up_money) {
        level_up->setTexture("/GameScene/Tower/Btn_CantUpLevel.png");
    }
    if (level == 3) {
        level_up->setTexture("/GameScene/Tower/Btn_ReachHighestLevel.PNG");
    }
    level_up->setPosition(Vec2(vec.x,
        vec.y + range->getContentSize().height/2));
    touch_layer->addChild(level_up);
    //������ʾ
    auto sell = Sprite::create("/GameScene/Tower/Btn_SellTower.png");
    sell->setPosition(Vec2(vec.x,
        vec.y - range->getContentSize().height/2));
    touch_layer->addChild(sell);

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
    };
    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        //�����������ť
        if (touch->getLocation().x >= level_up->getPosition().x - level_up->getContentSize().width / 2 &&
            touch->getLocation().x <= level_up->getPosition().x + level_up->getContentSize().width / 2 &&
            touch->getLocation().y >= level_up->getPosition().y - level_up->getContentSize().height / 2 &&
            touch->getLocation().y <= level_up->getPosition().y + level_up->getContentSize().height / 2) {
            if (level < 3 && game_money >= level_up_money) {
                //UpLevel(position);
                log("UpLevel(position)");
                game_money -= level_up_money;
                this->removeChild(touch_layer);
            }
        }
        else if (//��������۰�ť
            touch->getLocation().x >= sell->getPosition().x - sell->getContentSize().width / 2 &&
            touch->getLocation().x <= sell->getPosition().x + sell->getContentSize().width / 2 &&
            touch->getLocation().y >= sell->getPosition().y - sell->getContentSize().height / 2 &&
            touch->getLocation().y <= sell->getPosition().y + sell->getContentSize().height / 2) {
            //SellTower(position)
            log("SellTower(position)");
            game_money += sell_money;
            game_map[position.i][position.j] = EMPTY;
            this->removeChild(touch_layer);
        }
        else {
            this->removeChild(touch_layer);
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, touch_layer);
}
