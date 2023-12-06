#include"Level_1_1.h"
#include"GameScene.h"
#include"sound&music.h"
#include"GameData.h"
#include"ui/CocosGUI.h"
#include<string>
USING_NS_CC;
using namespace cocos2d::ui;
/*******************************  错误处理  ************************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}
/********************************  工具函数  *********************************/
vec2 trans_ij_to_xy(pos position) {
    vec2 vec;
    vec.x = 40 + position.j * 80;
    vec.y = 40 + (6 - position.i) * 80;
    return vec;
}
pos trans_xy_to_ij(vec2 vec) {
    pos position;
    position.j = static_cast<int>((vec.x) / 80);
    position.i = 6 - static_cast<int>((vec.y) / 80);
    return position;
}
/**********************  全局变量  ***********************/
int level_selection;//关卡选择
int if_speed_up;//是否加速
int if_pause;//是否暂停
int game_money;//金钱
int game_waves;//当前波数
char game_map[7][12];//辅助地图数组
extern int level_1_1_waves;
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
    auto waves_txt = Label::createWithTTF("/ " + to_string(level_1_1_waves) + " Waves", "/fonts/Marker Felt.ttf", 32);
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
    //暂停界面的纯色层
    auto black_layer = LayerColor::create(Color4B::BLACK);
    black_layer->setPosition(Vec2::ZERO);
    black_layer->setOpacity(85);
    black_layer->setVisible(false);
    this->addChild(black_layer, -1);
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
    //游戏开始的倒计时
    start();
    //游戏开始后的触摸事件
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
    };
    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        if (touch->getLocation().y < 560) {
            vec2 vec;
            vec.x = touch->getLocation().x;
            vec.y = touch->getLocation().y;
            pos position = trans_xy_to_ij(vec);
            Node* node = this->getChildByTag(position.i * 100 + position.j);
            Sprite* selection = static_cast<Sprite*>(node);
            if (game_map[position.i][position.j] == 0) {
                selection->setTexture("/GameScene/Grid.png");
                selection->runAction(Sequence::create(Show::create(), DelayTime::create(1), Hide::create(), nullptr));
            }
            else {
                selection->setTexture("/GameScene/cantBuild.png");
                selection->runAction(Blink::create(1, 3));
            }
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


    this->scheduleUpdate();
    return true;
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
