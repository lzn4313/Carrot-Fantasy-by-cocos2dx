#include"GameScene.h"
#include "GameSelectionScene.h"
#include "MenuScene.h"
#include "OptionsScene.h"
#include "HelperScene.h"
#include "sound&music.h"
#include "GameData.h"
#include"ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
extern int level_selection;
/*******************************  错误处理  ************************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}
/*******************************  工具函数  **************************************/
//同HelperScene.cpp中的用法
int find(float page[], int N, float x) {
    for (int i = 0; i < N; i++) {
        if (x >= page[i]) {
            return i - 1;
        }
    }
    return N - 1;
}
/*******************************  GameSelectionScene  ******************************/
Scene*  GameSelectionScene::createScene()
{
    return GameSelectionScene::create();
}
/*初始化*/
bool GameSelectionScene::init()
{
    /*初始化场景*/
    if (!Scene::init())
    {
        return false;
    }
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /**************************  背景  *******************************/
    auto background_image = Sprite::create("/GameSelectionScene/stages_bg-hd_0.PNG");
    background_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(background_image);
    /**************************  帮助  ******************************/
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    //去帮助界面
    auto help_btn = MenuItemImage::create("/GameSelectionScene/stages_bg-hd_42.PNG", "/GameSelectionScene/stages_bg-hd_33.PNG");
    help_btn->setCallback([](Ref* psender) {//按钮回调函数
        button_sound_effect();//播放音效
        auto helper_scene = HelperScene::createScene();//创建帮助场景
        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.2, helper_scene));//以消失形式切换
        });
    help_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.8,
        origin.y + visibleSize.height * 0.95));
    menu->addChild(help_btn);

    this->addChild(menu);
    /*************************  biglevel  ****************************/
    auto biglevel = BigLevelLayer::createLayer();//创建选大关的Layer
    this->addChild(biglevel);//添加渲染


    return true;
}
/*******************************  BigLevelLayer  ******************************/
cocos2d::Layer* BigLevelLayer::createLayer()
{
	return BigLevelLayer::create();
}
//初始化
bool BigLevelLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
    //获取屏幕大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /*****************************************  页码  ***********************************/
    auto page_0 = Sprite::create("/GameSelectionScene/page_no.png");
    page_0->setTag(0);
    page_0->setScale(1.4);
    page_0->setPosition(Vec2(origin.x + visibleSize.width * 0.47,
        origin.y + visibleSize.height * 0.05));
    this->addChild(page_0);

    auto page_1 = Sprite::create("/GameSelectionScene/page_yes.png");
    page_1->setTag(1);
    page_1->setScale(1.4);
    page_1->setPosition(Vec2(origin.x + visibleSize.width * 0.49,
        origin.y + visibleSize.height * 0.05));
    this->addChild(page_1);

    auto page_2 = Sprite::create("/GameSelectionScene/page_no.png");
    page_2->setTag(2);
    page_2->setScale(1.4);
    page_2->setPosition(Vec2(origin.x + visibleSize.width * 0.51,
        origin.y + visibleSize.height * 0.05));
    this->addChild(page_2);

    auto page_3 = Sprite::create("/GameSelectionScene/page_no.png");
    page_3->setTag(3);
    page_3->setScale(1.4);
    page_3->setPosition(Vec2(origin.x + visibleSize.width * 0.53,
        origin.y + visibleSize.height * 0.05));
    this->addChild(page_3);
    /***************************  滑动层  *********************************/
    create_slide_layer();//创建滑动层
    /***************************  菜单层  *********************************/
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0);
    //返回主菜单
    auto home_btn = MenuItemImage::create("/GameSelectionScene/themescene1-hd_8.PNG", "/GameSelectionScene/themescene1-hd_17.PNG");
    home_btn->setCallback([this](Ref* psender) {//回调函数
        button_sound_effect();//播放音效
        auto menu_scene = MenuScene::createScene();//创建主菜单对应Scene
        Director::getInstance()->replaceScene(TransitionFlipAngular::create(0.2, menu_scene));//以对角反转形式切换
        });
    home_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.2,
        origin.y + visibleSize.height * 0.95));
    menu->addChild(home_btn);
    //向左翻页按钮
    auto left_btn = MenuItemImage::create("/GameSelectionScene/themescene1-hd_32.PNG", "/GameSelectionScene/themescene1-hd_31.PNG",
        CC_CALLBACK_1(BigLevelLayer::page_left, this));
    left_btn->setPosition(Vec2(origin.x + visibleSize.width *0.1,
        origin.y + visibleSize.height / 2));
    menu->addChild(left_btn);
    //向右翻页按钮
    auto right_btn = MenuItemImage::create("/GameSelectionScene/themescene1-hd_26.PNG", "/GameSelectionScene/themescene1-hd_25.PNG",
        CC_CALLBACK_1(BigLevelLayer::page_right, this));
    right_btn->setPosition(Vec2(origin.x + visibleSize.width *0.9,
        origin.y + visibleSize.height / 2));
    menu->addChild(right_btn);

    return true;
}
//创建滑动层
void BigLevelLayer::create_slide_layer()
{
    auto slide_layer = Layer::create();
    slide_layer->setName("SlideLayer");
    this->addChild(slide_layer,1);
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /*******************************  滑动层  ************************************/
    //evaluate
    auto evaluate = Sprite::create("/GameSelectionScene/themescene1-hd.png");
    evaluate->setName("Evaluate");
    evaluate->setPosition(Vec2(origin.x + visibleSize.width * (-0.5),
        origin.y + visibleSize.height / 2));
    slide_layer->addChild(evaluate);
    //天际
    auto skyline = Sprite::create("/GameSelectionScene/themescene2-hd.pvr_2.PNG");
    skyline->setName("Skyline");
    skyline->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height * 0.45));
    slide_layer->addChild(skyline);
    //天际关卡统计
    auto level_1_statistics_image = Sprite::create("/GameSelectionScene/Items03-hd.pvr_0.PNG");
    level_1_statistics_image->setPosition(Vec2(origin.x + visibleSize.width * 0.66,
        origin.y + visibleSize.height * 0.11));
    slide_layer->addChild(level_1_statistics_image);

    auto level_1_statistics_txt = Label::createWithTTF(to_string(UserDefault::getInstance()->getIntegerForKey("level_1")) + "/9",
        "/fonts/Marker Felt.ttf", 20);
    level_1_statistics_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.66,
        origin.y + visibleSize.height * 0.12));
    slide_layer->addChild(level_1_statistics_txt);
    //丛林
    auto jungle = Sprite::create("/GameSelectionScene/themescene2-hd.pvr_0.PNG");
    jungle->setName("Jungle");
    jungle->setPosition(Vec2(origin.x + visibleSize.width *1.5,
        origin.y + visibleSize.height * 0.45));
    slide_layer->addChild(jungle);
    //丛林关卡统计
    if (UserDefault::getInstance()->getIntegerForKey("level_2") == 0) {
        auto level_2_lock = Sprite::create("/GameSelectionScene/themescene1-hd_10.PNG");
        level_2_lock->setPosition(Vec2(origin.x + visibleSize.width * 1.78,
            origin.y + visibleSize.height * 0.2));
        slide_layer->addChild(level_2_lock);
    }
    else {
        //待开发
    }
    //沙漠
    auto desert = Sprite::create("/GameSelectionScene/themescene2-hd.pvr_1.PNG");
    desert->setName("Desert");
    desert->setPosition(Vec2(origin.x + visibleSize.width * 2.5,
        origin.y + visibleSize.height * 0.45));
    slide_layer->addChild(desert);
    //沙漠关卡统计
    if (UserDefault::getInstance()->getIntegerForKey("level_3") == 0) {
        auto level_3_lock = Sprite::create("/GameSelectionScene/themescene1-hd_10.PNG");
        level_3_lock->setPosition(Vec2(origin.x + visibleSize.width * 2.78,
            origin.y + visibleSize.height * 0.2));
        slide_layer->addChild(level_3_lock);
    }
    else {
        //待开发
    }

    /***********************************  滑动实现  ***********************************************/
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);//设置事件吞没
    listener->onTouchBegan = [slide_layer,evaluate, skyline, jungle, desert](Touch* touch, Event* event) {
        Vec2 pos = slide_layer->convertTouchToNodeSpace(touch);
        //若触摸起始点在每一个图形的选择范围内则事件吞没
        if ((pos.x > evaluate->getPositionX() - evaluate->getContentSize().width / 2 &&
            pos.x< evaluate->getPositionX() + evaluate->getContentSize().width / 2 &&
            pos.y>evaluate->getPositionY() - evaluate->getContentSize().height / 2 &&
            pos.y < evaluate->getPositionY() + evaluate->getContentSize().height / 2)
            ||
            (pos.x > skyline->getPositionX() - skyline->getContentSize().width / 2 &&
                pos.x< skyline->getPositionX() + skyline->getContentSize().width / 2 &&
                pos.y>skyline->getPositionY() - skyline->getContentSize().height / 2 &&
                pos.y < skyline->getPositionY() + skyline->getContentSize().height / 2)
            ||
            (pos.x > jungle->getPositionX() - jungle->getContentSize().width / 2 &&
                pos.x< jungle->getPositionX() + jungle->getContentSize().width / 2 &&
                pos.y>jungle->getPositionY() - jungle->getContentSize().height / 2 &&
                pos.y < jungle->getPositionY() + jungle->getContentSize().height / 2)
            ||
            (pos.x > desert->getPositionX() - desert->getContentSize().width / 2 &&
                pos.x< desert->getPositionX() + desert->getContentSize().width / 2 &&
                pos.y>desert->getPositionY() - desert->getContentSize().height / 2 &&
                pos.y < desert->getPositionY() + desert->getContentSize().height / 2)
            )
            return true;
        else {
            return false;
        }
    };
    listener->onTouchMoved = [slide_layer](Touch* touch, Event* event) {//实现屏幕随触摸移动
        float distance = touch->getLocation().x - touch->getPreviousLocation().x;
        slide_layer->setPositionX(slide_layer->getPositionX() + distance);
    };
    listener->onTouchEnded = [this, slide_layer, visibleSize, evaluate, skyline, jungle, desert](Touch* touch, Event* event) {
        float distance = touch->getLocation().x - touch->getStartLocation().x;//记录本次触摸的横向距离
        float page[4] = { visibleSize.width,0,-visibleSize.width,-2 * visibleSize.width };
        int n = find(page, 4, slide_layer->getPosition().x);
        if (distance > visibleSize.width / 6) {//若大于六分之一屏幕距离，则视翻页成功，向左一页
            if (slide_layer->getPosition().x > page[0]) {
                slide_layer->runAction(MoveTo::create(0.1, Vec2(page[0], 0)));
            }
            else if (slide_layer->getPosition().x < page[0]) {
                slide_layer->runAction(MoveTo::create(0.1, Vec2(page[n], 0)));
                page_sound_effect();
                Node* num_1 = this->getChildByTag(n);
                static_cast<Sprite*>(num_1)->setTexture("/GameSelectionScene/page_yes.png");
                Node* num_2 = this->getChildByTag(n + 1);
                static_cast<Sprite*>(num_2)->setTexture("/GameSelectionScene/page_no.png");
            }
        }
        else if (distance < -visibleSize.width / 6) {//视为向右移动一页
            if (slide_layer->getPosition().x < page[3]) {
                slide_layer->runAction(MoveTo::create(0.1, Vec2(page[3], 0)));
            }
            else if (slide_layer->getPosition().x > page[3]) {
                slide_layer->runAction(MoveTo::create(0.1, Vec2(page[n + 1], 0)));
                page_sound_effect();
                Node* num_1 = this->getChildByTag(n + 1);
                static_cast<Sprite*>(num_1)->setTexture("/GameSelectionScene/page_yes.png");
                Node* num_2 = this->getChildByTag(n);
                static_cast<Sprite*>(num_2)->setTexture("/GameSelectionScene/page_no.png");
            }
        }
        else {//若小于六分之一屏幕，视本次触摸为取消翻页或点击
            if (distance > 0) {
                slide_layer->runAction(MoveTo::create(0.1, Vec2(page[n + 1], 0)));
            }
            else if (distance < 0) {
                slide_layer->runAction(MoveTo::create(0.1, Vec2(page[n], 0)));
            }
            else {//若没有移动，视为点击，根据点击位置确定进入哪一个选项
                Vec2 pos = slide_layer->convertTouchToNodeSpace(touch);
                if (pos.x > evaluate->getPositionX() - evaluate->getContentSize().width / 2 &&
                    pos.x< evaluate->getPositionX() + evaluate->getContentSize().width / 2 &&
                    pos.y>evaluate->getPositionY() - evaluate->getContentSize().height / 2 &&
                    pos.y < evaluate->getPositionY() + evaluate->getContentSize().height / 2)  {
                    goto_evaluate(slide_layer);
                }
                else if (pos.x > skyline->getPositionX() - skyline->getContentSize().width / 2 &&
                    pos.x< skyline->getPositionX() + skyline->getContentSize().width / 2 &&
                    pos.y>skyline->getPositionY() - skyline->getContentSize().height / 2 &&
                    pos.y < skyline->getPositionY() + skyline->getContentSize().height / 2) {
                    goto_level_1(slide_layer);
                }
                else if
                    (pos.x > jungle->getPositionX() - jungle->getContentSize().width / 2 &&
                        pos.x< jungle->getPositionX() + jungle->getContentSize().width / 2 &&
                        pos.y>jungle->getPositionY() - jungle->getContentSize().height / 2 &&
                        pos.y < jungle->getPositionY() + jungle->getContentSize().height / 2) {
                    goto_level_2(slide_layer);
                }
                else if
                    (pos.x > desert->getPositionX() - desert->getContentSize().width / 2 &&
                        pos.x< desert->getPositionX() + desert->getContentSize().width / 2 &&
                        pos.y>desert->getPositionY() - desert->getContentSize().height / 2 &&
                        pos.y < desert->getPositionY() + desert->getContentSize().height / 2)
                {
                    goto_level_3(slide_layer);
                }
            }
        }
    };
    //将事件监听器加入事件分发器内
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, slide_layer);

}
//去评价界
void BigLevelLayer::goto_evaluate(Ref* psender)
{
    button_sound_effect();//播放音效
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /************************  纯色层  *****************************/
    auto evaluate_layer = LayerColor::create(Color4B::BLACK);
    evaluate_layer->setPosition(Vec2::ZERO);
    evaluate_layer->setOpacity(85);
    this->addChild(evaluate_layer, 1);
    /************************  事件监听器  *****************************/
    auto listener2 = EventListenerTouchOneByOne::create();
    listener2->setSwallowTouches(true);//设置吞没，以确保必须按按钮才能返回上一页
    listener2->onTouchBegan = [evaluate_layer](Touch* touch, Event* event) {
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, evaluate_layer);

    /******************  背景  ***************************/
    auto evaluate_image = Sprite::create("/GameSelectionScene/evaluate.png");
    evaluate_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    evaluate_layer->addChild(evaluate_image);
    /*******************  菜单  **************************/
    auto evaluate_menu = Menu::create();
    evaluate_menu->setPosition(Vec2::ZERO);
    evaluate_layer->addChild(evaluate_menu);
    //确认按钮
    auto ok_btn = MenuItemImage::create("/GameSelectionScene/close_evaluate_normal.png", "/GameSelectionScene/close_evaluate_selected.png");
    ok_btn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.25));
    ok_btn->setScale(1.4);
    ok_btn->setCallback([this, evaluate_layer](Ref* psender) {//按钮回调事件，返回上一级
        button_sound_effect();
        this->removeChild(evaluate_layer);
        });
    evaluate_menu->addChild(ok_btn);

}
//向左一页
void BigLevelLayer::page_left(Ref* psender)
{
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //记录每一页对应坐标
    float page[4] = { visibleSize.width,0,-visibleSize.width,-2 * visibleSize.width };
    Node* slide_layer = this->getChildByName("SlideLayer");
    int n = find(page, 4, slide_layer->getPositionX());
    //向左移动一页
    if (slide_layer->getPosition().x < page[0]) {
        slide_layer->runAction(MoveBy::create(0.1, Vec2(visibleSize.width, 0)));
        page_sound_effect();
        Node* num_1 = this->getChildByTag(n);
        static_cast<Sprite*>(num_1)->setTexture("/GameSelectionScene/page_yes.png");
        Node* num_2 = this->getChildByTag(n + 1);
        static_cast<Sprite*>(num_2)->setTexture("/GameSelectionScene/page_no.png");
    }

}
//向右一页
void BigLevelLayer::page_right(Ref* psender)
{
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //记录每一页坐标
    float page[4] = { visibleSize.width,0,-visibleSize.width,-2 * visibleSize.width };
    Node* slide_layer = this->getChildByName("SlideLayer");
    int n = find(page, 4, slide_layer->getPositionX());
    //向右移动一页
    if (slide_layer->getPosition().x > page[3]) {
        slide_layer->runAction(MoveBy::create(0.1, Vec2(-visibleSize.width, 0)));
            page_sound_effect();
                Node* num_1 = this->getChildByTag(n + 2);
                static_cast<Sprite*>(num_1)->setTexture("/GameSelectionScene/page_yes.png");
                Node* num_2 = this->getChildByTag(n + 1);
                static_cast<Sprite*>(num_2)->setTexture("/GameSelectionScene/page_no.png");
    }

}
//去天际
void BigLevelLayer::goto_level_1(Ref* psender)
{
    button_sound_effect();//播放音效
    auto level_1_layer = Level_1_Layer::createLayer();//创建层，并加入
    this->getParent()->addChild(level_1_layer, 1);
    this->removeFromParent();
}
//去丛林
void BigLevelLayer::goto_level_2(Ref* psender)
{
    button_sound_effect();//播放音效

    if (UserDefault::getInstance()->getIntegerForKey("level_2") == 0) {//若当前丛林未解锁，则上锁提示

        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        /*****************************  纯色层  ******************************************/
        auto black_layer = LayerColor::create(Color4B::BLACK);
        black_layer->setOpacity(85);

        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
            return true;
        };
        listener->setSwallowTouches(true);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
        /********************************  背景  *****************************************/
        auto level_2_lock = Sprite::create("/GameSelectionScene/level_2_lock.png");
        level_2_lock->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));
        level_2_lock->setScale(1.4);
        black_layer->addChild(level_2_lock);
        /********************************  按钮  ****************************************/
        auto menu = Menu::create();
        menu->setPosition(Vec2::ZERO);

        auto lock_btn = MenuItemImage::create("/GameSelectionScene/lock_btn_normal.png", "/GameSelectionScene/lock_btn_selected.png");
        lock_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.55,
            origin.y + visibleSize.height * 0.4));
        lock_btn->setCallback([this, black_layer](Ref* psender) {
            button_sound_effect();
            this->removeChild(black_layer);
            });
        lock_btn->setScale(1.4);
        menu->addChild(lock_btn);
        black_layer->addChild(menu);

        this->addChild(black_layer, 2);
    }
    else {
        ;//boss_pattern待开发
    }
}
//去沙漠
void BigLevelLayer::goto_level_3(Ref* psender)
{
    button_sound_effect();//播放音效

    if (UserDefault::getInstance()->getIntegerForKey("level_2") == 0) {//若当前沙漠未解锁，则上锁提示

        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        /*****************************  纯色层  ******************************************/
        auto black_layer = LayerColor::create(Color4B::BLACK);
        black_layer->setOpacity(85);

        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
            return true;
        };
        listener->setSwallowTouches(true);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
        /********************************  背景  *****************************************/
        auto level_3_lock = Sprite::create("/GameSelectionScene/level_3_lock.png");
        level_3_lock->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));
        level_3_lock->setScale(1.4);
        black_layer->addChild(level_3_lock);
        /********************************  按钮  ****************************************/
        auto menu = Menu::create();
        menu->setPosition(Vec2::ZERO);

        auto lock_btn = MenuItemImage::create("/GameSelectionScene/lock_btn_normal.png", "/GameSelectionScene/lock_btn_selected.png");
        lock_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.55,
            origin.y + visibleSize.height * 0.4));
        lock_btn->setCallback([this, black_layer](Ref* psender) {
            button_sound_effect();
            this->removeChild(black_layer);
            });
        lock_btn->setScale(1.4);
        menu->addChild(lock_btn);
        black_layer->addChild(menu);

        this->addChild(black_layer, 2);
    }
    else {
        ;//boss_pattern待开发
    }
}
/********************************  Level_1_Layer  *********************************/
cocos2d::Layer* Level_1_Layer::createLayer()
{
    return Level_1_Layer::create();
}
//初始化
bool Level_1_Layer::init()
{
    if (!Layer::init()) {
        return false;
    }
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /***********************  菜单  *************************/
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    //返回选大关
    auto return_btn = MenuItemImage::create("/GameSelectionScene/stages_bg-hd_41.PNG", "/GameSelectionScene/stages_bg-hd_40.PNG",
        CC_CALLBACK_1(Level_1_Layer::return_to_biglevel, this));
    return_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.2,
        origin.y + visibleSize.height * 0.95));
    menu->addChild(return_btn);
    /**********************  背景  **************************/
    auto bg_1 = Sprite::create("/GameSelectionScene/BG_Left.PNG");
    bg_1->setPosition(Vec2(origin.x + bg_1->getContentSize().width / 2,
        origin.y + bg_1->getContentSize().height / 2));
    this->addChild(bg_1);

    auto bg_2 = Sprite::create("/GameSelectionScene/BG_Right.PNG");
    bg_2->setPosition(Vec2(origin.x + +visibleSize.width - bg_2->getContentSize().width / 2,
        origin.y + bg_2->getContentSize().height / 2));
    this->addChild(bg_2);

    /***********************  滑动层  ***********************/
    create_slide_layer();

    return true;
}
//创建滑动层
void Level_1_Layer::create_slide_layer()
{
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /**********************  滑动层设计  ***********************/
    //创建一个滑动层
    auto slide_layer = Layer::create();
    slide_layer->setName("SlideLayer");
    this->addChild(slide_layer);

    //可动层  随触摸动画移动
    auto move_layer = Layer::create();
    move_layer->setName("MoveLayer");
    slide_layer->addChild(move_layer, 1);
    //不可动层  在触摸确定翻页后直接移动
    auto static_layer = Layer::create();
    static_layer->setName("StaticLayer");
    slide_layer->addChild(static_layer, 2);
    /*************************  关卡level_1_1  **************************************/
    //图  背景图需滑动，加入可动层
    auto level_1_1_image = Sprite::create("/GameSelectionScene/Level_1.PNG");
    level_1_1_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height *0.54));
    move_layer->addChild(level_1_1_image);
    //共几波  不需滑动，加入不可动层
    auto waves_1 = Sprite::create("/GameSelectionScene/total_waves.png");
    waves_1->setPosition(Vec2(origin.x + visibleSize.width * 0.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_1);
    auto waves_1_txt = Label::createWithTTF("15", "/fonts/Marker Felt.ttf", 24);
    waves_1_txt->setTextColor(Color4B::YELLOW);
    waves_1_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_1_txt);
    //炮台类型  不需滑动，加入不可动层
    //瓶子
    auto tower_1 = Sprite::create("/GameSelectionScene/Tower_1.PNG");
    tower_1->setPosition(Vec2(origin.x + visibleSize.width / 2 - tower_1->getContentSize().width / 2,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_1);
    //便便
    auto tower_2 = Sprite::create("/GameSelectionScene/Tower_2.PNG");
    tower_2->setPosition(Vec2(origin.x + visibleSize.width / 2 + tower_2->getContentSize().width / 2,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_2);
    //开始  不需移动，加入不可动层
    auto level_1_btn = Button::create("/GameSelectionScene/stages_bg-hd_30.PNG", "/GameSelectionScene/stages_bg-hd_28.PNG",
        "/GameSelectionScene/stages_bg-hd_39.PNG");
    level_1_btn->addTouchEventListener(CC_CALLBACK_2(Level_1_Layer::level_1_1, this));
    level_1_btn->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height * 0.1));
    static_layer->addChild(level_1_btn);

    /*************************  关卡level_1_2  **************************************/
    //图 可动层
    auto level_1_2_image = Sprite::create("/GameSelectionScene/Level_2.PNG");
    level_1_2_image->setPosition(Vec2(origin.x + visibleSize.width * 1.5,
        origin.y + visibleSize.height * 0.54));
    move_layer->addChild(level_1_2_image);
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 2) {//若未解锁，则渲染“锁”提示
        auto level_1_2_lock = Sprite::create("/GameSelectionScene/stages_bg-hd_31.PNG");
        level_1_2_lock->setPosition(Vec2(origin.x + visibleSize.width * 1.64,
            origin.y + visibleSize.height * 0.4));
        move_layer->addChild(level_1_2_lock);
    }
    //共几波 不可动层
    auto waves_2 = Sprite::create("/GameSelectionScene/total_waves.png");
    waves_2->setPosition(Vec2(origin.x + visibleSize.width * 1.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_2);
    auto waves_2_txt = Label::createWithTTF("15", "/fonts/Marker Felt.ttf", 24);
    waves_2_txt->setTextColor(Color4B::YELLOW);
    waves_2_txt->setPosition(Vec2(origin.x + visibleSize.width * 1.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_2_txt);
    //炮台类型 不可动层
    //瓶子
    auto tower_2_1 = Sprite::create("/GameSelectionScene/Tower_1.PNG");
    tower_2_1->setPosition(Vec2(origin.x + visibleSize.width * 1.5 - tower_2_1->getContentSize().width,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_2_1);
    //便便
    auto tower_2_2 = Sprite::create("/GameSelectionScene/Tower_2.PNG");
    tower_2_2->setPosition(Vec2(origin.x + visibleSize.width *1.5,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_2_2);
    //星星
    auto tower_2_3 = Sprite::create("/GameSelectionScene/Tower_4.PNG");
    tower_2_3->setPosition(Vec2(origin.x + visibleSize.width * 1.5 + tower_2_3->getContentSize().width,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_2_3);
    //开始  不可动层
    auto level_2_btn = Button::create("/GameSelectionScene/stages_bg-hd_30.PNG", "/GameSelectionScene/stages_bg-hd_28.PNG",
        "/GameSelectionScene/stages_bg-hd_39.PNG");
    level_2_btn->addTouchEventListener(CC_CALLBACK_2(Level_1_Layer::level_1_2, this));
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 2) {//若未解锁，则设置按钮为不可用
        level_2_btn->setEnabled(false);
    }
    level_2_btn->setPosition(Vec2(origin.x + visibleSize.width * 1.5,
        origin.y + visibleSize.height * 0.1));
    static_layer->addChild(level_2_btn);

    /*************************  关卡level_1_3  **************************************/
     //图 可动层
    auto level_1_3_image = Sprite::create("/GameSelectionScene/Level_3.PNG");
    level_1_3_image->setPosition(Vec2(origin.x + visibleSize.width * 2.5,
        origin.y + visibleSize.height * 0.54));
    move_layer->addChild(level_1_3_image);
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 3) {//若未解锁，则渲染“锁”提示
        auto level_1_3_lock = Sprite::create("/GameSelectionScene/stages_bg-hd_31.PNG");
        level_1_3_lock->setPosition(Vec2(origin.x + visibleSize.width * 2.64,
            origin.y + visibleSize.height * 0.4));
        move_layer->addChild(level_1_3_lock);
    }
    //共几波  不可动层
    auto waves_3 = Sprite::create("/GameSelectionScene/total_waves.png");
    waves_3->setPosition(Vec2(origin.x + visibleSize.width * 2.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_3);
    auto waves_3_txt = Label::createWithTTF("20", "/fonts/Marker Felt.ttf", 24);
    waves_3_txt->setTextColor(Color4B::YELLOW);
    waves_3_txt->setPosition(Vec2(origin.x + visibleSize.width * 2.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_3_txt);
    //炮台类型  不可动层
    //瓶子
    auto tower_3_1 = Sprite::create("/GameSelectionScene/Tower_1.PNG");
    tower_3_1->setPosition(Vec2(origin.x + visibleSize.width * 2.5 - tower_3_1->getContentSize().width,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_3_1);
    //便便
    auto tower_3_2 = Sprite::create("/GameSelectionScene/Tower_2.PNG");
    tower_3_2->setPosition(Vec2(origin.x + visibleSize.width * 2.5,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_3_2);
    //风扇
    auto tower_3_3 = Sprite::create("/GameSelectionScene/Tower_3.PNG");
    tower_3_3->setPosition(Vec2(origin.x + visibleSize.width * 2.5 + tower_3_3->getContentSize().width,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_3_3);
    //开始 不可动层
    auto level_3_btn = Button::create("/GameSelectionScene/stages_bg-hd_30.PNG", "/GameSelectionScene/stages_bg-hd_28.PNG",
        "/GameSelectionScene/stages_bg-hd_39.PNG");
    level_3_btn->addTouchEventListener(CC_CALLBACK_2(Level_1_Layer::level_1_3, this));
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 3) {//若未解锁，则设置按钮为不可用
        level_3_btn->setEnabled(false);
    }
    level_3_btn->setPosition(Vec2(origin.x + visibleSize.width * 2.5,
        origin.y + visibleSize.height * 0.1));
    static_layer->addChild(level_3_btn);


    /*************************  关卡level_1_4  **************************************/
    //图
    auto level_1_4_image = Sprite::create("/GameSelectionScene/Level_4.PNG");
    level_1_4_image->setPosition(Vec2(origin.x + visibleSize.width * 3.5,
        origin.y + visibleSize.height * 0.54));
    move_layer->addChild(level_1_4_image);
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 4) {//若未解锁，则渲染“锁”提示
        auto level_1_4_lock = Sprite::create("/GameSelectionScene/stages_bg-hd_31.PNG");
        level_1_4_lock->setPosition(Vec2(origin.x + visibleSize.width * 3.64,
            origin.y + visibleSize.height * 0.4));
        move_layer->addChild(level_1_4_lock);
    }
    //共几波
    auto waves_4 = Sprite::create("/GameSelectionScene/total_waves.png");
    waves_4->setPosition(Vec2(origin.x + visibleSize.width * 3.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_4);
    auto waves_4_txt = Label::createWithTTF("20", "/fonts/Marker Felt.ttf", 24);
    waves_4_txt->setTextColor(Color4B::YELLOW);
    waves_4_txt->setPosition(Vec2(origin.x + visibleSize.width * 3.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_4_txt);
    //炮台类型
    //便便
    auto tower_4_1 = Sprite::create("/GameSelectionScene/Tower_2.PNG");
    tower_4_1->setPosition(Vec2(origin.x + visibleSize.width * 3.5 - tower_4_1->getContentSize().width/2,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_4_1);
    //水晶塔
    auto tower_4_2 = Sprite::create("/GameSelectionScene/Tower_5.PNG");
    tower_4_2->setPosition(Vec2(origin.x + visibleSize.width * 3.5 + tower_4_2->getContentSize().width / 2,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_4_2);
    //开始
    auto level_4_btn = Button::create("/GameSelectionScene/stages_bg-hd_30.PNG", "/GameSelectionScene/stages_bg-hd_28.PNG",
        "/GameSelectionScene/stages_bg-hd_39.PNG");
    level_4_btn->addTouchEventListener(CC_CALLBACK_2(Level_1_Layer::level_1_4, this));
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 4) {
        level_4_btn->setEnabled(false);
    }
    level_4_btn->setPosition(Vec2(origin.x + visibleSize.width * 3.5,
        origin.y + visibleSize.height * 0.1));
    static_layer->addChild(level_4_btn);

    /*************************  关卡level_1_5  **************************************/
    //图
    auto level_1_5_image = Sprite::create("/GameSelectionScene/Level_5.PNG");
    level_1_5_image->setPosition(Vec2(origin.x + visibleSize.width * 4.5,
        origin.y + visibleSize.height * 0.54));
    move_layer->addChild(level_1_5_image);
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 5) {//若未解锁，则渲染“锁”提示
        auto level_1_5_lock = Sprite::create("/GameSelectionScene/stages_bg-hd_31.PNG");
        level_1_5_lock->setPosition(Vec2(origin.x + visibleSize.width * 4.64,
            origin.y + visibleSize.height * 0.4));
        move_layer->addChild(level_1_5_lock);
    }
    //共几波
    auto waves_5 = Sprite::create("/GameSelectionScene/total_waves.png");
    waves_5->setPosition(Vec2(origin.x + visibleSize.width * 4.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_5);
    auto waves_5_txt = Label::createWithTTF("20", "/fonts/Marker Felt.ttf", 24);
    waves_5_txt->setTextColor(Color4B::YELLOW);
    waves_5_txt->setPosition(Vec2(origin.x + visibleSize.width * 4.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_5_txt);
    //炮台类型
    //便便
    auto tower_5_1 = Sprite::create("/GameSelectionScene/Tower_2.PNG");
    tower_5_1->setPosition(Vec2(origin.x + visibleSize.width * 4.5 - tower_5_1->getContentSize().width / 2,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_5_1);
    //星星
    auto tower_5_2 = Sprite::create("/GameSelectionScene/Tower_4.PNG");
    tower_5_2->setPosition(Vec2(origin.x + visibleSize.width * 4.5 + tower_5_2->getContentSize().width / 2,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_5_2);
    //开始
    auto level_5_btn = Button::create("/GameSelectionScene/stages_bg-hd_30.PNG", "/GameSelectionScene/stages_bg-hd_28.PNG",
        "/GameSelectionScene/stages_bg-hd_39.PNG");
    level_5_btn->addTouchEventListener(CC_CALLBACK_2(Level_1_Layer::level_1_5, this));
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 5) {//若未解锁，则设置按钮为不可用
        level_5_btn->setEnabled(false);
    }
    level_5_btn->setPosition(Vec2(origin.x + visibleSize.width * 4.5,
        origin.y + visibleSize.height * 0.1));
    static_layer->addChild(level_5_btn);



    /***********************  滑动实现  *****************************/
    auto listener4 = EventListenerTouchOneByOne::create();
    listener4->onTouchBegan = [move_layer](Touch* touch, Event* event) {
        return true;
    };
    listener4->onTouchMoved = [move_layer](Touch* touch, Event* event) {//实现触摸滑动
        float distance = touch->getLocation().x - touch->getPreviousLocation().x;
        move_layer->setPositionX(move_layer->getPositionX() + distance);
    };
    listener4->onTouchEnded = [=](Touch* touch, Event* event) {
        //获取触摸移动横向距离
        float distance = touch->getLocation().x - touch->getStartLocation().x;
        //记录每一页坐标
        float page[5] = { 0,-visibleSize.width,-2 * visibleSize.width ,-3 * visibleSize.width ,-4 * visibleSize.width };
        int n = find(page, 5, move_layer->getPosition().x);

        if (distance > visibleSize.width / 6) {//若滑动大于六分之一屏幕，则视为滑动翻页
            if (move_layer->getPosition().x > page[0]) {
                move_layer->runAction(MoveTo::create(0.1, Vec2(page[0], 0)));
            }
            else if (move_layer->getPosition().x < page[0]) {
                move_layer->runAction(MoveTo::create(0.1, Vec2(page[n], 0)));
                static_layer->setPosition(Vec2(page[n], static_layer->getPositionY()));
                page_sound_effect();
            }
        }
        else if (distance < -visibleSize.width / 6) {
            if (move_layer->getPosition().x < page[4]) {
                move_layer->runAction(MoveTo::create(0.1, Vec2(page[4], 0)));
            }
            else if (move_layer->getPosition().x > page[4]) {
                move_layer->runAction(MoveTo::create(0.1, Vec2(page[n + 1], 0)));
                static_layer->setPosition(Vec2(page[n + 1], static_layer->getPositionY()));
                page_sound_effect();
            }
        }
        else {//若小于六分之一屏幕，则视为取消翻页或点击
            if (distance > 0) {//若取消翻页，则回到滑动前的页码
                move_layer->runAction(MoveTo::create(0.1, Vec2(page[n + 1], 0)));
                static_layer->setPosition(Vec2(page[n + 1], static_layer->getPositionY()));
            }
            else if (distance < 0) {
                move_layer->runAction(MoveTo::create(0.1, Vec2(page[n], 0)));
                static_layer->setPosition(Vec2(page[n], static_layer->getPositionY()));
            }
            else {//若点击，则根据鼠标位置，进行关卡选择
                Vec2 pos = move_layer->convertTouchToNodeSpace(touch);
                if (pos.x > level_1_1_image->getPositionX() - level_1_1_image->getContentSize().width / 2 &&
                    pos.x< level_1_1_image->getPositionX() + level_1_1_image->getContentSize().width / 2 &&
                    pos.y>level_1_1_image->getPositionY() - level_1_1_image->getContentSize().height / 2 &&
                    pos.y < level_1_1_image->getPositionY() + level_1_1_image->getContentSize().height / 2) {
                    level_1_1(slide_layer, Widget::TouchEventType::ENDED);
                }
                else if (pos.x > level_1_2_image->getPositionX() - level_1_2_image->getContentSize().width / 2 &&
                    pos.x< level_1_2_image->getPositionX() + level_1_2_image->getContentSize().width / 2 &&
                    pos.y>level_1_2_image->getPositionY() - level_1_2_image->getContentSize().height / 2 &&
                    pos.y < level_1_2_image->getPositionY() + level_1_2_image->getContentSize().height / 2) {
                    level_1_2(slide_layer, Widget::TouchEventType::ENDED);
                }
                else if
                    (pos.x > level_1_3_image->getPositionX() - level_1_3_image->getContentSize().width / 2 &&
                        pos.x< level_1_3_image->getPositionX() + level_1_3_image->getContentSize().width / 2 &&
                        pos.y>level_1_3_image->getPositionY() - level_1_3_image->getContentSize().height / 2 &&
                        pos.y < level_1_3_image->getPositionY() + level_1_3_image->getContentSize().height / 2) {
                    level_1_3(slide_layer, Widget::TouchEventType::ENDED);
                }
                else if
                    (pos.x > level_1_4_image->getPositionX() - level_1_4_image->getContentSize().width / 2 &&
                        pos.x< level_1_4_image->getPositionX() + level_1_4_image->getContentSize().width / 2 &&
                        pos.y>level_1_4_image->getPositionY() - level_1_4_image->getContentSize().height / 2 &&
                        pos.y < level_1_4_image->getPositionY() + level_1_4_image->getContentSize().height / 2)
                {
                    level_1_4(slide_layer, Widget::TouchEventType::ENDED);
                }
                else if (pos.x > level_1_5_image->getPositionX() - level_1_5_image->getContentSize().width / 2 &&
                    pos.x< level_1_5_image->getPositionX() + level_1_5_image->getContentSize().width / 2 &&
                    pos.y>level_1_5_image->getPositionY() - level_1_5_image->getContentSize().height / 2 &&
                    pos.y < level_1_5_image->getPositionY() + level_1_5_image->getContentSize().height / 2)
                {
                    level_1_5(slide_layer, Widget::TouchEventType::ENDED);
                }
            }
        }
    };
    //将事件监听器加入事件分发器
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener4, move_layer);
}
//回到选大关界面
void Level_1_Layer::return_to_biglevel(Ref* psender)
{
    button_sound_effect();//播放音效
    auto big_level_layer = BigLevelLayer::createLayer();//创建大关Layer
    this->getParent()->addChild(big_level_layer);//渲染
    this->removeFromParent();//移除当前Layer
}
//天际第1关
void Level_1_Layer::level_1_1(Ref* psender, Widget::TouchEventType type)
{
    //按钮回调函数
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::CANCELED:
            break;
        case Widget::TouchEventType::ENDED://当且仅当抬起时触发
            button_sound_effect();//播放音效
            level_selection = 1;
            auto game_scene = GameScene::createScene();
            Director::getInstance()->replaceScene(game_scene);
            break;
    }
}
//天际第2关
void Level_1_Layer::level_1_2(Ref* psender, Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::CANCELED:
            break;
        case Widget::TouchEventType::ENDED://当且仅当抬起时触发
            button_sound_effect();//播放音效

            if (UserDefault::getInstance()->getIntegerForKey("level_1") < 2) {//若当前关未解锁，弹出提示

                auto visibleSize = Director::getInstance()->getVisibleSize();
                Vec2 origin = Director::getInstance()->getVisibleOrigin();
                /*****************************  纯色层  ******************************************/
                auto black_layer = LayerColor::create(Color4B::BLACK);
                black_layer->setOpacity(85);

                auto listener = EventListenerTouchOneByOne::create();
                listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
                    return true;
                };
                listener->setSwallowTouches(true);
                Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
                /********************************  背景  *****************************************/
                auto lock = Sprite::create("/GameSelectionScene/lock_image.png");
                lock->setPosition(Vec2(origin.x + visibleSize.width / 2,
                    origin.y + visibleSize.height / 2));
                lock->setScale(1.4);
                black_layer->addChild(lock);
                /********************************  按钮  ****************************************/
                auto menu = Menu::create();
                menu->setPosition(Vec2::ZERO);

                auto lock_btn = MenuItemImage::create("/GameSelectionScene/lock_btn_normal.png", "/GameSelectionScene/lock_btn_selected.png");
                lock_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.55,
                    origin.y + visibleSize.height * 0.4));
                lock_btn->setCallback([this, black_layer](Ref* psender) {
                    button_sound_effect();
                    this->removeChild(black_layer);
                    });
                lock_btn->setScale(1.4);
                menu->addChild(lock_btn);
                black_layer->addChild(menu);

                this->addChild(black_layer, 2);
            }
            else {
                level_selection = 2;
                auto game_scene = GameScene::createScene();
                Director::getInstance()->replaceScene(game_scene);
            }
            break;
    }
}
//天际第3关
void Level_1_Layer::level_1_3(Ref* psender, Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::CANCELED:
            break;
        case Widget::TouchEventType::ENDED://当且仅当抬起时触发
            button_sound_effect();//播放音效

            if (UserDefault::getInstance()->getIntegerForKey("level_1") < 3) {//若未解锁，弹出提示

                auto visibleSize = Director::getInstance()->getVisibleSize();
                Vec2 origin = Director::getInstance()->getVisibleOrigin();
                /*****************************  纯色层  ******************************************/
                auto black_layer = LayerColor::create(Color4B::BLACK);
                black_layer->setOpacity(85);

                auto listener = EventListenerTouchOneByOne::create();
                listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
                    return true;
                };
                listener->setSwallowTouches(true);
                Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
                /********************************  背景  *****************************************/
                auto lock = Sprite::create("/GameSelectionScene/lock_image.png");
                lock->setPosition(Vec2(origin.x + visibleSize.width / 2,
                    origin.y + visibleSize.height / 2));
                lock->setScale(1.4);
                black_layer->addChild(lock);
                /********************************  按钮  ****************************************/
                auto menu = Menu::create();
                menu->setPosition(Vec2::ZERO);

                auto lock_btn = MenuItemImage::create("/GameSelectionScene/lock_btn_normal.png", "/GameSelectionScene/lock_btn_selected.png");
                lock_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.55,
                    origin.y + visibleSize.height * 0.4));
                lock_btn->setCallback([this, black_layer](Ref* psender) {
                    button_sound_effect();
                    this->removeChild(black_layer);
                    });
                lock_btn->setScale(1.4);
                menu->addChild(lock_btn);
                black_layer->addChild(menu);

                this->addChild(black_layer, 2);
            }
            else {
                ;//level_1_3待开发
            }
            break;
    }
}
//天际第4关
void Level_1_Layer::level_1_4(Ref* psender, Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::CANCELED:
            break;
        case Widget::TouchEventType::ENDED://当且仅当抬起时触发
            button_sound_effect();//播放音效

            if (UserDefault::getInstance()->getIntegerForKey("level_1") < 4) {//若未解锁，弹出提示

                auto visibleSize = Director::getInstance()->getVisibleSize();
                Vec2 origin = Director::getInstance()->getVisibleOrigin();
                /*****************************  纯色层  ******************************************/
                auto black_layer = LayerColor::create(Color4B::BLACK);
                black_layer->setOpacity(85);

                auto listener = EventListenerTouchOneByOne::create();
                listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
                    return true;
                };
                listener->setSwallowTouches(true);
                Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
                /********************************  背景  *****************************************/
                auto lock = Sprite::create("/GameSelectionScene/lock_image.png");
                lock->setPosition(Vec2(origin.x + visibleSize.width / 2,
                    origin.y + visibleSize.height / 2));
                lock->setScale(1.4);
                black_layer->addChild(lock);
                /********************************  按钮  ****************************************/
                auto menu = Menu::create();
                menu->setPosition(Vec2::ZERO);

                auto lock_btn = MenuItemImage::create("/GameSelectionScene/lock_btn_normal.png", "/GameSelectionScene/lock_btn_selected.png");
                lock_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.55,
                    origin.y + visibleSize.height * 0.4));
                lock_btn->setCallback([this, black_layer](Ref* psender) {
                    button_sound_effect();
                    this->removeChild(black_layer);
                    });
                lock_btn->setScale(1.4);
                menu->addChild(lock_btn);
                black_layer->addChild(menu);

                this->addChild(black_layer, 2);
            }
            else {
                ;//level_1_4待开发
            }
            break;
    }
}
//天际第5关
void Level_1_Layer::level_1_5(Ref* psender, Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::CANCELED:
            break;
        case Widget::TouchEventType::ENDED://当且仅当抬起时触发
            button_sound_effect();//播放音效

            if (UserDefault::getInstance()->getIntegerForKey("level_1") < 5) {//若未解锁，弹出提示

                auto visibleSize = Director::getInstance()->getVisibleSize();
                Vec2 origin = Director::getInstance()->getVisibleOrigin();
                /*****************************  纯色层  ******************************************/
                auto black_layer = LayerColor::create(Color4B::BLACK);
                black_layer->setOpacity(85);

                auto listener = EventListenerTouchOneByOne::create();
                listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
                    return true;
                };
                listener->setSwallowTouches(true);
                Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
                /********************************  背景  *****************************************/
                auto lock = Sprite::create("/GameSelectionScene/lock_image.png");
                lock->setPosition(Vec2(origin.x + visibleSize.width / 2,
                    origin.y + visibleSize.height / 2));
                lock->setScale(1.4);
                black_layer->addChild(lock);
                /********************************  按钮  ****************************************/
                auto menu = Menu::create();
                menu->setPosition(Vec2::ZERO);

                auto lock_btn = MenuItemImage::create("/GameSelectionScene/lock_btn_normal.png", "/GameSelectionScene/lock_btn_selected.png");
                lock_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.55,
                    origin.y + visibleSize.height * 0.4));
                lock_btn->setCallback([this, black_layer](Ref* psender) {
                    button_sound_effect();
                    this->removeChild(black_layer);
                    });
                lock_btn->setScale(1.4);
                menu->addChild(lock_btn);
                black_layer->addChild(menu);

                this->addChild(black_layer, 2);
            }
            else {
                ;//level_1_5待开发
            }
            break;
    }
}
