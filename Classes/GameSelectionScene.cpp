#include "GameSelectionScene.h"
#include "MenuScene.h"
#include "OptionsScene.h"
#include "HelperScene.h"
#include "sound&music.h"
#include "GameData.h"
USING_NS_CC;

/*******************************  错误处理  ************************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}
/*******************************  工具函数  **************************************/
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
    help_btn->setCallback([](Ref* psender) {
        button_sound_effect();
        auto helper_scene = HelperScene::createScene();
        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.2, helper_scene));
        });
    help_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.8,
        origin.y + visibleSize.height * 0.95));
    menu->addChild(help_btn);

    this->addChild(menu);
    /*************************  biglevel  ****************************/
    auto biglevel = BigLevelLayer::createLayer();
    this->addChild(biglevel);


    return true;
}

/*******************************  BigLevelLayer  ******************************/
cocos2d::Layer* BigLevelLayer::createLayer()
{
	return BigLevelLayer::create();
}
bool BigLevelLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

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
    create_slide_layer();
    Node* node = this->getChildByName("SlideLayer");
    Layer* slide_layer = static_cast<Layer*>(node);
    /***************************  菜单层  *********************************/
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0);
    //返回主菜单
    auto home_btn = MenuItemImage::create("/GameSelectionScene/themescene1-hd_8.PNG", "/GameSelectionScene/themescene1-hd_17.PNG");
    home_btn->setCallback([](Ref* psender) {
        button_sound_effect();
        auto menu_scene = MenuScene::createScene();
        Director::getInstance()->replaceScene(TransitionFlipAngular::create(0.2, menu_scene));
        });
    home_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.2,
        origin.y + visibleSize.height * 0.95));
    menu->addChild(home_btn);
    //向左翻页
    auto left_btn = MenuItemImage::create("/GameSelectionScene/themescene1-hd_32.PNG", "/GameSelectionScene/themescene1-hd_31.PNG",
        CC_CALLBACK_1(BigLevelLayer::page_left, this));
    left_btn->setPosition(Vec2(origin.x + visibleSize.width *0.1,
        origin.y + visibleSize.height / 2));
    menu->addChild(left_btn);
    //向右翻页
    auto right_btn = MenuItemImage::create("/GameSelectionScene/themescene1-hd_26.PNG", "/GameSelectionScene/themescene1-hd_25.PNG",
        CC_CALLBACK_1(BigLevelLayer::page_right, this));
    right_btn->setPosition(Vec2(origin.x + visibleSize.width *0.9,
        origin.y + visibleSize.height / 2));
    menu->addChild(right_btn);
    /***********************************  滑动实现  ***********************************************/
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [slide_layer,listener](Touch* touch, Event* event) {
        return true;
    };
    listener->onTouchMoved = [slide_layer,listener](Touch* touch, Event* event) {
        float distance = touch->getLocation().x - touch->getPreviousLocation().x;
        slide_layer->setPositionX(slide_layer->getPositionX() + distance);
    };
    listener->onTouchEnded = [this, slide_layer, visibleSize](Touch* touch, Event* event) {
        float distance = touch->getLocation().x - touch->getStartLocation().x;
        float page[4] = { visibleSize.width,0,-visibleSize.width,-2 * visibleSize.width };
        int n = find(page, 4, slide_layer->getPosition().x);
        if (distance > visibleSize.width / 6) {
            if (slide_layer->getPosition().x > page[0]) {
                slide_layer->runAction(MoveTo::create(0.1, Vec2(page[0], 0)));
            }
            else if(slide_layer->getPosition().x < page[0]){
                slide_layer->runAction(MoveTo::create(0.1, Vec2(page[n], 0)));
                page_sound_effect();
                Node* num_1 = this->getChildByTag(n);
                static_cast<Sprite*>(num_1)->setTexture("/GameSelectionScene/page_yes.png");
                Node* num_2 = this->getChildByTag(n + 1);
                static_cast<Sprite*>(num_2)->setTexture("/GameSelectionScene/page_no.png");
            }
        }
        else if (distance < -visibleSize.width / 6) {
            if (slide_layer->getPosition().x < page[3]) {
                slide_layer->runAction(MoveTo::create(0.1, Vec2(page[3], 0)));
            }
            else if (slide_layer->getPosition().x > page[3]){
                slide_layer->runAction(MoveTo::create(0.1, Vec2(page[n + 1], 0)));
                page_sound_effect();
                Node* num_1 = this->getChildByTag(n + 1);
                static_cast<Sprite*>(num_1)->setTexture("/GameSelectionScene/page_yes.png");
                Node* num_2 = this->getChildByTag(n);
                static_cast<Sprite*>(num_2)->setTexture("/GameSelectionScene/page_no.png");
            }
        }
        else {
            if (distance > 0) {
                log("0");
                slide_layer->runAction(MoveTo::create(0.1, Vec2(page[n + 1], 0)));
            }
            else if (distance < 0) {
                log("1");
                slide_layer->runAction(MoveTo::create(0.1, Vec2(page[n], 0)));
            }
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, menu);
	return true;
}

void BigLevelLayer::create_slide_layer()
{
    auto slide_layer = Layer::create();
    slide_layer->setName("SlideLayer");
    this->addChild(slide_layer, 1);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*******************************  滑动层  ************************************/
    auto slide_layer_menu = Menu::create();
    slide_layer_menu->setPosition(Vec2::ZERO);
    slide_layer->addChild(slide_layer_menu,0);

    //evaluate
    auto evaluate = MenuItemImage::create("/GameSelectionScene/themescene1-hd.png", "/GameSelectionScene/themescene1-hd.png",
        CC_CALLBACK_1(BigLevelLayer::goto_evaluate,this));
    evaluate->setPosition(Vec2(origin.x + visibleSize.width * (-0.5),
        origin.y + visibleSize.height / 2));
    slide_layer_menu->addChild(evaluate, 0);
    //天际
    auto skyline = MenuItemImage::create("/GameSelectionScene/themescene2-hd.pvr_2.PNG", "/GameSelectionScene/themescene2-hd.pvr_2.PNG",
        CC_CALLBACK_1(BigLevelLayer::goto_level_1, this));
    skyline->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height * 0.45));
    slide_layer_menu->addChild(skyline);
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
    auto jungle = MenuItemImage::create("/GameSelectionScene/themescene2-hd.pvr_0.PNG", "/GameSelectionScene/themescene2-hd.pvr_0.PNG",
        CC_CALLBACK_1(BigLevelLayer::goto_level_2, this));
    jungle->setPosition(Vec2(origin.x + visibleSize.width *1.5,
        origin.y + visibleSize.height * 0.45));
    slide_layer_menu->addChild(jungle);
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
    auto desert = MenuItemImage::create("/GameSelectionScene/themescene2-hd.pvr_1.PNG", "/GameSelectionScene/themescene2-hd.pvr_1.PNG",
        CC_CALLBACK_1(BigLevelLayer::goto_level_3, this));
    desert->setPosition(Vec2(origin.x + visibleSize.width * 2.5,
        origin.y + visibleSize.height * 0.45));
    slide_layer_menu->addChild(desert);
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
}

void BigLevelLayer::goto_evaluate(Ref* psender)
{
    button_sound_effect();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

        auto evaluate_layer = LayerColor::create(Color4B::BLACK);
        evaluate_layer->setPosition(Vec2::ZERO);
        evaluate_layer->setOpacity(85);
        this->addChild(evaluate_layer, 1);

        auto listener2 = EventListenerTouchOneByOne::create();
        listener2->setSwallowTouches(true);
        listener2->onTouchBegan = [evaluate_layer](Touch* touch, Event* event) {
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, evaluate_layer);


        auto evaluate_image = Sprite::create("/GameSelectionScene/evaluate.png");
        evaluate_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));
        evaluate_layer->addChild(evaluate_image);

        auto evaluate_menu = Menu::create();
        evaluate_menu->setPosition(Vec2::ZERO);
        evaluate_layer->addChild(evaluate_menu);

        auto ok_btn = MenuItemImage::create("/GameSelectionScene/close_evaluate_normal.png", "/GameSelectionScene/close_evaluate_selected.png");
        ok_btn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.25));
        ok_btn->setScale(1.4);
        ok_btn->setCallback([this,evaluate_layer](Ref* psender) {
            button_sound_effect();
            this->removeChild(evaluate_layer);
            });
        evaluate_menu->addChild(ok_btn);

}

void BigLevelLayer::page_left(Ref* psender)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    float page[4] = { visibleSize.width,0,-visibleSize.width,-2 * visibleSize.width };
    Node* slide_layer = this->getChildByName("SlideLayer");
    int n = find(page, 4, slide_layer->getPositionX());

    if (slide_layer->getPosition().x < page[0]) {
        slide_layer->runAction(MoveBy::create(0.1, Vec2(visibleSize.width, 0)));
        page_sound_effect();
        Node* num_1 = this->getChildByTag(n);
        static_cast<Sprite*>(num_1)->setTexture("/GameSelectionScene/page_yes.png");
        Node* num_2 = this->getChildByTag(n + 1);
        static_cast<Sprite*>(num_2)->setTexture("/GameSelectionScene/page_no.png");
    }

}

void BigLevelLayer::page_right(Ref* psender)
{
    log("page_right");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    float page[4] = { visibleSize.width,0,-visibleSize.width,-2 * visibleSize.width };
    Node* slide_layer = this->getChildByName("SlideLayer");
    int n = find(page, 4, slide_layer->getPositionX());

    if (slide_layer->getPosition().x > page[3]) {
        slide_layer->runAction(MoveBy::create(0.1, Vec2(-visibleSize.width, 0)));
            page_sound_effect();
                Node* num_1 = this->getChildByTag(n + 2);
                static_cast<Sprite*>(num_1)->setTexture("/GameSelectionScene/page_yes.png");
                Node* num_2 = this->getChildByTag(n + 1);
                static_cast<Sprite*>(num_2)->setTexture("/GameSelectionScene/page_no.png");
    }

}

void BigLevelLayer::goto_level_1(Ref* psender)
{
    log("aaaa");
}

void BigLevelLayer::goto_level_2(Ref* psender)
{
    button_sound_effect();
    if (UserDefault::getInstance()->getIntegerForKey("level_2") == 0) {

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
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, black_layer);
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

void BigLevelLayer::goto_level_3(Ref* psender)
{
    button_sound_effect();
    if (UserDefault::getInstance()->getIntegerForKey("level_2") == 0) {

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
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, black_layer);
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
