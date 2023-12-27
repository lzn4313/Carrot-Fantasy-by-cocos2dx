#include"Level_1_1.h"
#include"GameScene.h"
#include"GameSelectionScene.h"
#include"sound&music.h"
#include"GameData.h"
#include"ui/CocosGUI.h"
#include"Tower.h"
#include<string>
#include<vector>
USING_NS_CC;
using namespace cocos2d::ui;
/*******************************  错误处理  ************************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}
/**********************  全局变量  ***********************/
int level_selection;//关卡选择
int if_speed_up;//是否加速
int if_pause;//是否暂停
int game_money;//金钱
int game_waves;//当前波数
int max_waves;//总波数
char game_map[7][12];//辅助地图数组
int carrot_hp;//记录萝卜血量
pos carrot_position;//记录萝卜位置
int tower_available[3];//可建造防御塔存储
Tower_information tower_map[7][12];//储存防御塔信息的数组
/**********************************  GameScene  ***********************************/
Scene* GameScene::createScene()
{
    return GameScene::create();
}
/*初始化*/
bool GameScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    /**********************  部分全局变量初始化  **********************/
    if_speed_up = 0;//默认不加速
    if_pause = 0;//默认不暂停
    /**********************  选关  ******************************/
    if (level_selection == 1) {
        auto level_1_1 = Level_1_1::createLayer();
        level_1_1->setName("PlayingLevel");
        this->addChild(level_1_1, -1);
    }
    /***********************  菜单层  ***************************/
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
//初始化
bool GameMenu::init()
{
    if (!Layer::init()) {
        return false;
    }
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //背景
    auto menu_image = Sprite::create("/GameScene/touming-hd.pvr_13.PNG");
    menu_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - menu_image->getContentSize().height / 2));
    this->addChild(menu_image);
    //金钱显示
    auto money_label = Label::createWithTTF(to_string(game_money), "/fonts/Marker Felt.ttf", 32);
    money_label->setName("MoneyLabel");
    money_label->setAnchorPoint(Vec2(0, 0.5));
    money_label->setPosition(Vec2(origin.x + visibleSize.width * 0.1,
        origin.y + visibleSize.height * 0.95));
    this->addChild(money_label);
    //波数显示
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
    //倍速开关
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    auto speed_up_on_sprite = Sprite::create("/GameScene/touming-hd.pvr_7.PNG");
    auto speed_up_on = MenuItemSprite::create(speed_up_on_sprite, speed_up_on_sprite);
    auto speed_up_off_sprite = Sprite::create("/GameScene/touming-hd.pvr_9.PNG");
    auto speed_up_off = MenuItemSprite::create(speed_up_off_sprite, speed_up_off_sprite);
    auto speed_toggle = MenuItemToggle::createWithCallback([&](Ref* psender) {
        button_sound_effect();//播放音效
        if (if_speed_up == 0) {//若勾选，则表示开启二倍速
            if_speed_up = 1;
        }
        else {
            if_speed_up = 0;
        }
        }, speed_up_on, speed_up_off, nullptr);
    speed_toggle->setPosition(Vec2(origin.x + visibleSize.width * 0.7,
        origin.y + visibleSize.height * 0.94));
    menu->addChild(speed_toggle);
    //暂停开关
    //暂停界面提示
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
        button_sound_effect();//播放音效
        if (if_pause == 0) {//若勾选，则表示暂停
            if_pause = 1;
            paused->setVisible(true);
            waves_image->setVisible(false);
            waves_label->setVisible(false);
            waves_txt->setVisible(false);
        }
        else {
            if_pause = 0;
            paused->setVisible(false);
            waves_image->setVisible(true);
            waves_label->setVisible(true);
            waves_txt->setVisible(true);
        }
        }, pause_off, pause_on, nullptr);
    pause_toggle->setPosition(Vec2(origin.x + visibleSize.width * 0.8,
        origin.y + visibleSize.height * 0.94));
    menu->addChild(pause_toggle);
    //选项
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
                button_sound_effect();//播放音效
                options();
                break;
        }
        });
    this->addChild(options_btn);
    //触摸格点
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

    //萝卜
    carrot_hp = 10;
    vec2 carrot_pos = trans_ij_to_xy(carrot_position);
    auto carrot = Sprite::create();
    carrot->setName("Carrot");
    carrot->setTexture("/Carrot/HP_MAX.PNG");
    carrot->setPosition(carrot_pos.x, carrot_pos.y);
    carrot->setAnchorPoint(Vec2{ 0.3, 0.2 });
    tower_map[carrot_position.i][carrot_position.j] = { CARROT, 0, 0, 0, 1, 0, 1 };
    this->addChild(carrot);
    //萝卜血量
    auto carrot_hp_image = Sprite::create();
    carrot_hp_image->setTexture("/Carrot/Hp.png");
    carrot_hp_image->setAnchorPoint(Vec2{ 0,0.5 });
    carrot_hp_image->setPosition(carrot_pos.x + carrot->getContentSize().width * 0.5, carrot_pos.y + carrot->getContentSize().height * 0.3);
    this->addChild(carrot_hp_image);
    auto hp_label = Label::createWithTTF(to_string(carrot_hp), "/fonts/Marker Felt.ttf", 20);
    hp_label->setTextColor(Color4B::WHITE);
    hp_label->setName("HpLabel");
    hp_label->setAnchorPoint(Vec2(0, 0.5));
    hp_label->setPosition(Vec2(carrot_pos.x + carrot->getContentSize().width * 0.5 + carrot_hp_image->getContentSize().width * 0.5,
        carrot_pos.y + carrot->getContentSize().height * 0.3));
    this->addChild(hp_label);

    //游戏开始的倒计时
    start();
    //游戏开始后的触摸事件
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
                button_sound_effect();
                build(position, tower_available);
            }
            else if (game_map[position.i][position.j] == TOWER || game_map[position.i][position.j] == CARROT) {
                button_sound_effect();
                tower_operations(position);
            }
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


    this->scheduleUpdate();
    return true;
}
//失败
void GameMenu::lose() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /************************  纯色层  *****************************/
    auto black_layer = LayerColor::create(Color4B::BLACK);
    black_layer->setPosition(Vec2::ZERO);
    black_layer->setOpacity(90);
    this->addChild(black_layer, 1);
    /************************  事件监听器  *****************************/
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);//设置吞没，以确保必须按按钮才能返回上一页
    listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);

    /******************  背景  ***************************/
    auto lose_bg = Sprite::create("/GameScene/lose.png");
    lose_bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    lose_bg->setScale(1.7);
    black_layer->addChild(lose_bg);
    //当前波数显示
    auto waves_label = Label::createWithTTF(to_string(game_waves / 10 % 10) + "   " + to_string(game_waves % 10), "/fonts/Marker Felt.ttf", 32);
    waves_label->setColor(Color3B::YELLOW);
    waves_label->setPosition(Vec2(origin.x + visibleSize.width * 0.475,
        origin.y + visibleSize.height * 0.52));
    black_layer->addChild(waves_label);
    //波数显示
    auto waves_txt = Label::createWithTTF(to_string(max_waves), "/fonts/Marker Felt.ttf", 32);
    waves_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.58,
        origin.y + visibleSize.height * 0.52));
    black_layer->addChild(waves_txt);
    //关卡显示
    auto level_txt = Label::createWithTTF("0" + to_string(level_selection), "/fonts/Marker Felt.ttf", 32);
    level_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.4,
        origin.y + visibleSize.height * 0.43));
    black_layer->addChild(level_txt);
    /*******************  菜单  **************************/
    auto options_menu = Menu::create();
    options_menu->setPosition(Vec2::ZERO);
    black_layer->addChild(options_menu);
    //重新开始
    auto again_btn = MenuItemImage::create("/GameScene/again_normal.png", "/GameScene/again_selected.png");
    again_btn->setPosition(Vec2(visibleSize.width * 0.6, visibleSize.height * 0.3));
    again_btn->setCallback([this, black_layer](Ref* psender) {//按钮回调事件，返回上一级
        button_sound_effect();
        this->removeChildByName("PlayingLevel");
        if (level_selection == 1) {
            auto level_1_1 = Level_1_1::createLayer();
            level_1_1->setName("PlayingLevel");
            this->addChild(level_1_1, -3);
            carrot_hp = 10;
            start();
        }
        this->scheduleUpdate();
        this->removeChild(black_layer);
        });
    options_menu->addChild(again_btn);
    //选择关卡
    auto return_btn = MenuItemImage::create("/GameScene/return_normal.png", "/GameScene/return_selected.png");
    return_btn->setPosition(Vec2(visibleSize.width * 0.35, visibleSize.height * 0.3));
    return_btn->setCallback([this, black_layer](Ref* psender) {//按钮回调事件，返回上一级
        button_sound_effect();
        Director::getInstance()->popScene();
        });
    options_menu->addChild(return_btn);

}
//胜利
void GameMenu::win() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /************************  获胜  ******************************/
    UserDefault::getInstance()->setIntegerForKey("adventure_statistics", UserDefault::getInstance()->getIntegerForKey("adventure_statistics") + 1);
    UserDefault::getInstance()->setIntegerForKey("level_1", UserDefault::getInstance()->getIntegerForKey("level_1") + 1);
    /************************  纯色层  *****************************/
    auto black_layer = LayerColor::create(Color4B::BLACK);
    black_layer->setPosition(Vec2::ZERO);
    black_layer->setOpacity(90);
    this->addChild(black_layer, 1);
    /************************  事件监听器  *****************************/
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);//设置吞没，以确保必须按按钮才能返回上一页
    listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);

    /******************  背景  ***************************/
    auto win_bg = Sprite::create("/GameScene/win.png");
    win_bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    win_bg->setScale(1.7);
    black_layer->addChild(win_bg);
    //当前波数显示
    auto waves_label = Label::createWithTTF(to_string(game_waves / 10 % 10) + "   " + to_string(game_waves % 10), "/fonts/Marker Felt.ttf", 32);
    waves_label->setColor(Color3B::YELLOW);
    waves_label->setPosition(Vec2(origin.x + visibleSize.width * 0.475,
        origin.y + visibleSize.height * 0.51));
    black_layer->addChild(waves_label);
    //波数显示
    auto waves_txt = Label::createWithTTF(to_string(max_waves), "/fonts/Marker Felt.ttf", 32);
    waves_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.58,
        origin.y + visibleSize.height * 0.51));
    black_layer->addChild(waves_txt);
    //关卡显示
    auto level_txt = Label::createWithTTF("0" + to_string(level_selection), "/fonts/Marker Felt.ttf", 32);
    level_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.4,
        origin.y + visibleSize.height * 0.42));
    level_txt->setColor(Color3B::YELLOW);
    black_layer->addChild(level_txt);
    /*******************  菜单  **************************/
    auto options_menu = Menu::create();
    options_menu->setPosition(Vec2::ZERO);
    black_layer->addChild(options_menu);
    //继续游戏
    auto resume_btn = MenuItemImage::create("/GameScene/resume_normal.png", "/GameScene/resume_selected.png");
    resume_btn->setPosition(Vec2(visibleSize.width * 0.6, visibleSize.height * 0.3));
    resume_btn->setCallback([this, black_layer](Ref* psender) {//按钮回调事件，返回上一级
        button_sound_effect();
        this->removeChildByName("PlayingLevel");
        /*if (level_selection == 1) {
            auto level_1_2 = Level_1_2::createLayer();
            level_1_2->setName("PlayingLevel");
            this->addChild(level_1_2, -3);
            this->scheduleUpdate();
            carrot_hp = 10;
            start();
        }
        else if (level_selection == 2) {
            log("To be continued");
            Director::getInstance()->popScene();
        }*/
        this->removeChild(black_layer);
        Director::getInstance()->popScene();
        Director::getInstance()->replaceScene(GameSelectionScene::createScene());
        });
    options_menu->addChild(resume_btn);
    //选择关卡
    auto return_btn = MenuItemImage::create("/GameScene/return_normal.png", "/GameScene/return_selected.png");
    return_btn->setPosition(Vec2(visibleSize.width * 0.35, visibleSize.height * 0.3));
    return_btn->setCallback([this, black_layer](Ref* psender) {//按钮回调事件，返回上一级
        button_sound_effect();
        Director::getInstance()->popScene();
        Director::getInstance()->replaceScene(GameSelectionScene::createScene());
        });
    options_menu->addChild(return_btn);

}
//重写update函数
void GameMenu::update(float dt) {
    //实时更新金钱数据
    Node* money_node = this->getChildByName("MoneyLabel");
    Label* money_label = static_cast<Label*>(money_node);
    money_label->setString(to_string(game_money));
    //实时更新波数
    Node* waves_node = this->getChildByName("WavesLabel");
    Label* waves_label = static_cast<Label*>(waves_node);
    waves_label->setString(to_string(game_waves / 10 % 10) + "   " + to_string(game_waves % 10));
    //实时更新萝卜生命值
    Node* hp_node = this->getChildByName("HpLabel");
    Label* hp_label = static_cast<Label*>(hp_node);
    hp_label->setString(to_string(carrot_hp));
    //根据萝卜生命值更新萝卜外观
    Node* carrot_node = this->getChildByName("Carrot");
    Sprite* carrot_image = static_cast<Sprite*>(carrot_node);
    switch (carrot_hp) {
        case 0:
        case 1:
            carrot_image->setAnchorPoint(Vec2{ 0.5, 0.2 });
            carrot_image->setTexture("/Carrot/HP_1.PNG");
            break;
        case 2:
            carrot_image->setAnchorPoint(Vec2{ 0.5, 0.2 });
            carrot_image->setTexture("/Carrot/HP_2.PNG");
            break;
        case 3:
            carrot_image->setAnchorPoint(Vec2{ 0.5, 0.2 });
            carrot_image->setTexture("/Carrot/HP_3.PNG");
            break;
        case 4:
            carrot_image->setAnchorPoint(Vec2{ 0.3, 0.2 });
            carrot_image->setTexture("/Carrot/HP_4.PNG");
            break;
        case 5:
        case 6:
            carrot_image->setAnchorPoint(Vec2{ 0.3, 0.2 });
            carrot_image->setTexture("/Carrot/HP_5-6.PNG");
            break;
        case 7:
        case 8:
            carrot_image->setAnchorPoint(Vec2{ 0.3, 0.2 });
            carrot_image->setTexture("/Carrot/HP_7-8.PNG");
            break;
        case 9:
            carrot_image->setAnchorPoint(Vec2{ 0.3, 0.2 });
            carrot_image->setTexture("/Carrot/HP_9.PNG");
            break;
        default:
            carrot_image->setAnchorPoint(Vec2{ 0.3, 0.2 });
            carrot_image->setTexture("/Carrot/HP_MAX.PNG");
            break;
    }
    //判断胜利失败
    if (carrot_hp == 0) {
        this->unscheduleUpdate();
        lose();
    }
    if (game_waves == max_waves/*&&monster数组为空*/) {
        this->unscheduleUpdate();
        win();
    }
}
//设置界面
void GameMenu::options() {
    button_sound_effect();//播放音效
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /************************  纯色层  *****************************/
    auto black_layer = LayerColor::create(Color4B::BLACK);
    black_layer->setPosition(Vec2::ZERO);
    black_layer->setOpacity(90);
    this->addChild(black_layer, 1);
    /************************  事件监听器  *****************************/
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);//设置吞没，以确保必须按按钮才能返回上一页
    listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);

    /******************  背景  ***************************/
    auto options_bg = Sprite::create("/GameScene/options_bg.png");
    options_bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    black_layer->addChild(options_bg);
    /*******************  菜单  **************************/
    auto options_menu = Menu::create();
    options_menu->setPosition(Vec2::ZERO);
    black_layer->addChild(options_menu);
    //继续游戏
    auto resume_btn = MenuItemImage::create("/GameScene/resume_normal.png", "/GameScene/resume_selected.png");
    resume_btn->setPosition(Vec2(visibleSize.width *0.49, visibleSize.height * 0.67));
    resume_btn->setCallback([this, black_layer](Ref* psender) {//按钮回调事件，返回上一级
        button_sound_effect();
        this->removeChild(black_layer);
        });
    options_menu->addChild(resume_btn);
    //重新开始
    auto restart_btn = MenuItemImage::create("/GameScene/restart_normal.png", "/GameScene/restart_selected.png");
    restart_btn->setPosition(Vec2(visibleSize.width *0.49, visibleSize.height * 0.52));
    restart_btn->setCallback([this, black_layer](Ref* psender) {//按钮回调事件，返回上一级
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
    //选择关卡
    auto return_btn = MenuItemImage::create("/GameScene/return_normal.png", "/GameScene/return_selected.png");
    return_btn->setPosition(Vec2(visibleSize.width *0.49, visibleSize.height * 0.37));
    return_btn->setCallback([this, black_layer](Ref* psender) {//按钮回调事件，返回上一级
        button_sound_effect();
        Director::getInstance()->popScene();
        });
    options_menu->addChild(return_btn);

}
//开始
void GameMenu::start()
{   
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //倒计时的时候游戏是暂停的
    if_pause = 1;
    //倒计时页
    auto time_layer = Layer::create();
    this->addChild(time_layer);
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, time_layer);
    //倒计时背景盘
    auto panel = Sprite::create("/GameScene/Items02-hd_165.PNG");
    panel->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    time_layer->addChild(panel);
    //倒计时数字
    auto number = Sprite::create("/GameScene/Items02-hd_68.PNG");
    number->setPosition(Vec2(origin.x + visibleSize.width * 0.51,
        origin.y + visibleSize.height / 2));
    time_layer->addChild(number);
    //倒计时转圈
    auto circle = Sprite::create("/GameScene/Items02-hd_50.PNG");
    circle->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    time_layer->addChild(circle);
    circle->runAction(Sequence::create(Repeat::create(RotateBy::create(1, -360), 3), FadeOut::create(0.1), nullptr));
    panel->runAction(Sequence::create(DelayTime::create(3), FadeOut::create(0.1), nullptr));
   //利用帧动画完成数字的倒计时
    Vector<SpriteFrame*> frame;
    frame.pushBack(SpriteFrame::create("/GameScene/Items02-hd_68.PNG", Rect(0, 0, 95, 114)));
    frame.pushBack(SpriteFrame::create("/GameScene/Items02-hd_92.PNG", Rect(0, 0, 95, 114)));
    frame.pushBack(SpriteFrame::create("/GameScene/Items02-hd_88.PNG", Rect(0, 0, 95, 114)));
    number->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 1)),FadeOut::create(0.1),nullptr));
    //倒计时的时候所有可用格点闪烁
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
    //三秒后把遮罩层删除
    auto start_call_back = CallFunc::create([=]() {
        this->removeChild(time_layer);
        });
    time_layer->runAction(Sequence::create(DelayTime::create(3.1), start_call_back, nullptr));
    if_pause = 0;
}
//建造
void GameMenu::build(pos position, int tower_available[]) {
    //创建遮罩层
    auto touch_layer = Layer::create();
    this->addChild(touch_layer);
    //显示
    Node* node = this->getChildByTag(100 * position.i + position.j);
    Sprite* sprite = static_cast<Sprite*>(node);
    sprite->setTexture("/GameScene/Grid.png");
    sprite->setVisible(true);
    //炮台建造
    auto sprite_1 = Sprite::create();
    auto sprite_2 = Sprite::create();
    auto sprite_3 = Sprite::create();
    if (tower_available[2] == -1) {
        string str = "/GameScene/Tower/";
        //第一个炮台
        string str_1 = str + to_string(tower_available[0]) + "/";
        if (game_money <getMoney(tower_available[0])) {
            sprite_1->setTexture(str_1 + "CanClick0.PNG");
        }
        else {
            sprite_1->setTexture(str_1 + "CanClick1.PNG");
        }
        vec2 vec = trans_ij_to_xy(position);
        sprite_1->setPosition(Vec2(vec.x - sprite_1->getContentSize().width / 2,
            vec.y + sprite_1->getContentSize().height));
        touch_layer->addChild(sprite_1);
        //第二个炮台
        string str_2 = str + to_string(tower_available[1]) + "/";
        if (game_money <getMoney(tower_available[1])) {
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
        //第一个炮台
        string str_1 = str + to_string(tower_available[0]) + "/";
        if (game_money <getMoney(tower_available[0])) {
            sprite_1->setTexture(str_1 + "CanClick0.PNG");
        }
        else {
            sprite_1->setTexture(str_1 + "CanClick1.PNG");
        }
        vec2 vec = trans_ij_to_xy(position);
        sprite_1->setPosition(Vec2(vec.x - sprite_1->getContentSize().width,
            vec.y + sprite_1->getContentSize().height));
        touch_layer->addChild(sprite_1);
        //第二个炮台
        string str_2 = str + to_string(tower_available[1]) + "/";
        if (game_money <getMoney(tower_available[1])) {
            sprite_2->setTexture(str_2 + "CanClick0.PNG");
        }
        else {
            sprite_2->setTexture(str_2 + "CanClick1.PNG");
        }
        vec = trans_ij_to_xy(position);
        sprite_2->setPosition(Vec2(vec.x,
            vec.y + sprite_2->getContentSize().height));
        touch_layer->addChild(sprite_2);
        //第三个炮台
        string str_3 = str + to_string(tower_available[2]) + "/";
        if (game_money <getMoney(tower_available[2])) {
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
    //触摸层
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
    };
    listener->onTouchEnded = [this, sprite, sprite_1, sprite_2, sprite_3, touch_layer, position, tower_available](Touch* touch, Event* event) {
        //若按下位置在第一个炮塔图标内
        if (touch->getLocation().x >= sprite_1->getPosition().x - sprite_1->getContentSize().width / 2 &&
            touch->getLocation().x <= sprite_1->getPosition().x + sprite_1->getContentSize().width / 2 &&
            touch->getLocation().y >= sprite_1->getPosition().y - sprite_1->getContentSize().height / 2 &&
            touch->getLocation().y <= sprite_1->getPosition().y + sprite_1->getContentSize().height / 2) {
            if (game_money >=getMoney(tower_available[0])) {//若钱够，则建造
                Tower newtower;
                newtower.build_tower(position, tower_available[0], this);
                log("build_tower(position, tower_available[0])");
                game_money -=getMoney(tower_available[0]);
                sprite->setVisible(false);
                this->removeChild(touch_layer);
                game_map[position.i][position.j] = TOWER;
            }
        }
        else if (//若按下位置在第二个炮塔图标内
            touch->getLocation().x >= sprite_2->getPosition().x - sprite_2->getContentSize().width / 2 &&
            touch->getLocation().x <= sprite_2->getPosition().x + sprite_2->getContentSize().width / 2 &&
            touch->getLocation().y >= sprite_2->getPosition().y - sprite_2->getContentSize().height / 2 &&
            touch->getLocation().y <= sprite_2->getPosition().y + sprite_2->getContentSize().height / 2) {
            if (game_money >=getMoney(tower_available[1])) {//若钱够，则建造
                Tower newtower;
                newtower.build_tower(position, tower_available[1], this);
                log("build_tower(position, tower_available[1])");
                game_money -=getMoney(tower_available[1]);
                sprite->setVisible(false);
                this->removeChild(touch_layer);
                game_map[position.i][position.j] = TOWER;
            }
        }
        else if (//若按下位置在第三个炮塔图标内
            tower_available[2] != -1 &&
            touch->getLocation().x >= sprite_3->getPosition().x - sprite_3->getContentSize().width / 2 &&
            touch->getLocation().x <= sprite_3->getPosition().x + sprite_3->getContentSize().width / 2 &&
            touch->getLocation().y >= sprite_3->getPosition().y - sprite_3->getContentSize().height / 2 &&
            touch->getLocation().y <= sprite_3->getPosition().y + sprite_3->getContentSize().height / 2) {
            if (game_money >=getMoney(tower_available[2])) {//若钱够，则建造
                Tower newtower;
                newtower.build_tower(position, tower_available[2], this);
                log("build_tower(position, tower_available[2])");
                game_money -=getMoney(tower_available[2]);
                sprite->setVisible(false);
                this->removeChild(touch_layer);
                game_map[position.i][position.j] = TOWER;
            }
        }
        else {
            //若按下位置不在图标内
            sprite->setVisible(false);
            this->removeChild(touch_layer);
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, touch_layer);
}
//对防御塔的操作
void GameMenu::tower_operations(pos position) {
    Tower newtower;
    float range_scale = newtower.get_attack_range(position);//getRange(position);
    int level = newtower.get_level(position);// getLevel(position);
    int level_up_money = newtower.get_level_up_money(position);// getLevelUpMoney(position);
    int sell_money = newtower.get_sell_money(position);//getSellMoney(position);
    vec2 vec = trans_ij_to_xy(position);
    //遮罩层
    auto touch_layer = Layer::create();
    this->addChild(touch_layer);
    //范围显示
    auto range = Sprite::create("/GameScene/Tower/AttackRange.PNG");
    range->setScale(range_scale);
    range->setPosition(Vec2(vec.x,
        vec.y));
    touch_layer->addChild(range);
    //升级显示
    auto level_up = Sprite::create("/GameScene/Tower/Btn_CanUpLevel.png");
    if (game_money < level_up_money) {
        level_up->setTexture("/GameScene/Tower/Btn_CantUpLevel.png");
    }
    if (level == 3) {
        level_up->setTexture("/GameScene/Tower/Btn_ReachHighestLevel.PNG");
    }
    level_up->setPosition(Vec2(vec.x,
        vec.y + range->getContentSize().height / 2));
    touch_layer->addChild(level_up);

    if (level != 3) {
        auto level_up_label = Label::createWithTTF(to_string(level_up_money), "/fonts/Marker Felt.ttf", 22);
        level_up_label->setPosition(Vec2(vec.x + range->getContentSize().width * 0.04,
            vec.y + range->getContentSize().height * 0.38));
        level_up_label->setTextColor(Color4B::BLACK);
        touch_layer->addChild(level_up_label);
    }

    if (game_map[position.i][position.j] == TOWER) {
        //出售显示
        auto sell = Sprite::create("/GameScene/Tower/Btn_SellTower.png");
        sell->setPosition(Vec2(vec.x,
            vec.y - range->getContentSize().height / 2));
        touch_layer->addChild(sell);

        auto  sell_label = Label::createWithTTF(to_string(sell_money), "/fonts/Marker Felt.ttf", 22);
        sell_label->setPosition(Vec2(vec.x + range->getContentSize().width * 0.04,
            vec.y - range->getContentSize().height * 0.62));
        sell_label->setTextColor(Color4B::BLACK);
        touch_layer->addChild(sell_label);

        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [](Touch* touch, Event* event) {
            return true;
            };
        listener->onTouchEnded = [=](Touch* touch, Event* event) {
            //若点击升级按钮
            if (touch->getLocation().x >= level_up->getPosition().x - level_up->getContentSize().width / 2 &&
                touch->getLocation().x <= level_up->getPosition().x + level_up->getContentSize().width / 2 &&
                touch->getLocation().y >= level_up->getPosition().y - level_up->getContentSize().height / 2 &&
                touch->getLocation().y <= level_up->getPosition().y + level_up->getContentSize().height / 2) {
                if (level < 3 && game_money >= level_up_money) {
                    Tower newtower;
                    newtower.up_level_tower(position, this);
                    log("UpLevel(position)");
                    game_money -= level_up_money;
                    this->removeChild(touch_layer);
                }
            }
            else if (//若点击出售按钮
                touch->getLocation().x >= sell->getPosition().x - sell->getContentSize().width / 2 &&
                touch->getLocation().x <= sell->getPosition().x + sell->getContentSize().width / 2 &&
                touch->getLocation().y >= sell->getPosition().y - sell->getContentSize().height / 2 &&
                touch->getLocation().y <= sell->getPosition().y + sell->getContentSize().height / 2) {
                Tower newtower;
                newtower.sell_tower(position, this);
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
    else if (game_map[position.i][position.j] == CARROT) {
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [](Touch* touch, Event* event) {
            return true;
            };
        listener->onTouchEnded = [=](Touch* touch, Event* event) {
            //若点击升级按钮
            if (touch->getLocation().x >= level_up->getPosition().x - level_up->getContentSize().width / 2 &&
                touch->getLocation().x <= level_up->getPosition().x + level_up->getContentSize().width / 2 &&
                touch->getLocation().y >= level_up->getPosition().y - level_up->getContentSize().height / 2 &&
                touch->getLocation().y <= level_up->getPosition().y + level_up->getContentSize().height / 2) {
                if (level < 3 && game_money >= level_up_money) {
                    Tower newtower;
                    newtower.up_level_tower(position, this);
                    log("UpLevel(position)");
                    game_money -= level_up_money;
                    this->removeChild(touch_layer);
                }
            }
            else {
                this->removeChild(touch_layer);
            }
            };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, touch_layer);
    }
}
