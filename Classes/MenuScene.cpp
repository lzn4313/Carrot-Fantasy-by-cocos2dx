#include "MenuScene.h"
#include "OptionsScene.h"
#include "HelperScene.h"
#include "GameSelectionScene.h"
#include"sound&music.h"
#include"GameData.h"
USING_NS_CC;
/*菜单场景*/
Scene* MenuScene::createScene()
{
    return MenuScene::create();
}
/*错误处理*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}
/*初始化*/
bool MenuScene::init()
{
    /*初始化场景*/
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
;
    /*****************************************背景图**************************************************/
    auto background_image = Sprite::create("/MenuScene/MainBG.PNG");
    if (background_image == nullptr)
    {
        problemLoading("'MainBG.PNG'");
    }
    else
    {
        background_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));

        this->addChild(background_image);
    }
    /******************************************云*******************************************************/
    auto cloud = Sprite::create();
    cloud->setName("Cloud");
    //大云
    auto cloud1 = Sprite::create("/MenuScene/Cloud.PNG");
    if (cloud1 == nullptr)
    {
        problemLoading("'Cloud.PNG'");
    }
    else
    {
        cloud1->setPosition(Vec2(origin.x - cloud1->getContentSize().width,
            origin.y + visibleSize.height * 0.85));
        cloud1->setOpacity(95);
        //添加动画
        auto cloud1_moveto_1 = MoveTo::create(20, Vec2(origin.x + visibleSize.width + cloud1->getContentSize().width, origin.y + visibleSize.height * 0.85));
        auto cloud1_moveto_2 = MoveTo::create(20, Vec2(origin.x - cloud1->getContentSize().width, origin.y + visibleSize.height * 0.85));
        auto cloud1_sequence = Sequence::create(cloud1_moveto_1, DelayTime::create(5), cloud1_moveto_2, DelayTime::create(5),nullptr);
        cloud1->runAction(RepeatForever::create(cloud1_sequence));
        cloud->addChild(cloud1);
    }
    //小云
    auto cloud2 = Sprite::create("/MenuScene/Cloud2.PNG");
    if (cloud2 == nullptr)
    {
        problemLoading("'Cloud.PNG'");
    }
    else
    {
        cloud2->setPosition(Vec2(origin.x + visibleSize.width + cloud2->getContentSize().width,
            origin.y + visibleSize.height * 0.8));
        cloud2->setScale(2);
        cloud2->setOpacity(95);
        //添加动画
        auto cloud2_moveto_1 = MoveTo::create(20, Vec2(origin.x - cloud2->getContentSize().width, origin.y + visibleSize.height * 0.85));
        auto cloud2_moveto_2 = MoveTo::create(20, Vec2(origin.x + visibleSize.width + cloud2->getContentSize().width, origin.y + visibleSize.height * 0.85));
        auto cloud2_sequence = Sequence::create(cloud2_moveto_1, DelayTime::create(5), cloud2_moveto_2, DelayTime::create(5),nullptr);
        cloud2->runAction(RepeatForever::create(cloud2_sequence));
        cloud->addChild(cloud2);
    }

    this->addChild(cloud);
    /*****************************************************添加怪物图形****************************************************/
    auto monster = Sprite::create("/MenuScene/FlyMonster.PNG");
    if (monster == nullptr) {
        problemLoading("'FlyMonster.PNG'");
    }
    else {
        monster->setPosition(Vec2(origin.x + visibleSize.width / 4,
            origin.y + visibleSize.height * 0.8));
        //添加动作
        auto monster_moveby_down = MoveBy::create(1.0f, Vec2(0, -monster->getContentSize().height / 4));
        auto monster_moveby_up = MoveBy::create(1.0f, Vec2(0, monster->getContentSize().height / 4));
        auto monster_sequence = Sequence::createWithTwoActions(monster_moveby_down, monster_moveby_up);
        monster->runAction(RepeatForever::create(monster_sequence));
        this->addChild(monster);
    }
    /****************************************************添加萝卜图形*****************************************************/
    auto carrot = Sprite::create();
    carrot->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 4));
    //1,添加萝卜叶子
    auto carrot_leaf1 = Sprite::create("/MenuScene/Leaf1.PNG");
    if (carrot_leaf1 == nullptr)
    {
        problemLoading("'Leaf1.PNG'");
    }
    else
    {
        carrot_leaf1->setPosition(Vec2(origin.x - carrot_leaf1->getContentSize().width / 2,
            origin.y + visibleSize.height / 4 + carrot_leaf1->getContentSize().height * 1.2));
        carrot->addChild(carrot_leaf1);
    }

    auto carrot_leaf2 = Sprite::create("/MenuScene/Leaf2.PNG");
    if (carrot_leaf2 == nullptr)
    {
        problemLoading("'Leaf2.PNG'");
    }
    else
    {
        carrot_leaf2->setPosition(Vec2(origin.x + carrot_leaf2->getContentSize().width*0.6,
            origin.y + visibleSize.height / 4 + carrot_leaf2->getContentSize().height * 1.3));
        carrot_leaf2->setName("Leaf2");
        carrot->addChild(carrot_leaf2);
    }

    auto carrot_leaf3 = Sprite::create("/MenuScene/Leaf3.PNG");
    if (carrot_leaf3 == nullptr)
    {
        problemLoading("'Leaf3.PNG'");
    }
    else
    {
        carrot_leaf3->setPosition(Vec2(origin.x,
            origin.y + visibleSize.height / 4 + carrot_leaf3->getContentSize().height * 1.1));
        carrot_leaf3->setName("Leaf3");
        carrot->addChild(carrot_leaf3);
    }

    //2,添加萝卜主体
    auto carrot_body = Sprite::create("/MenuScene/CarrotBody.PNG");
    if (carrot_body == nullptr)
    {
        problemLoading("'CarrotBody.PNG'");
    }
    else
    {
        carrot_body->setPosition(Vec2(origin.x,
            origin.y + visibleSize.height / 4 + carrot_body->getContentSize().height / 4));

        carrot->addChild(carrot_body);
    }

    this->addChild(carrot);
    //萝卜动画添加
    carrot->setScale(0.1);
    auto carrot_start_scale = ScaleTo::create(0.3, 1);
    carrot->runAction(carrot_start_scale);

    auto carrot_leaf2_sequence = Sequence::create(DelayTime::create(5), RotateBy::create(0.2, 30), RotateBy::create(0.2, -30), 
        RotateBy::create(0.2, 30),RotateBy::create(0.2, -30), DelayTime::create(5), nullptr);
    carrot_leaf2->runAction(RepeatForever::create(carrot_leaf2_sequence));

    auto carrot_leaf3_sequence = Sequence::create(DelayTime::create(7), RotateBy::create(0.2, 30), RotateBy::create(0.2, -30),
        RotateBy::create(0.2, 30), RotateBy::create(0.2, -30), DelayTime::create(3), nullptr);
    carrot_leaf3->runAction(RepeatForever::create(carrot_leaf3_sequence));
    /*************************************************************添加保卫萝卜标题******************************************************************/
    auto title = Sprite::create("/MenuScene/MainTitle.PNG");
    if (title == nullptr) {
        problemLoading("'MainTitle.PNG'");
    }
    else {
        title->setPosition(Vec2(origin.x + visibleSize.width / 2 + title->getContentSize().width / 20,
            origin.y + visibleSize.height / 2 - title->getContentSize().height / 7));
        this->addChild(title);
    }
    /*****************************************************************菜单界面************************************************************************/
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    //退出游戏按钮
    auto close_item = MenuItemFont::create("EXIT", CC_CALLBACK_1(MenuScene::close_game, this));
    if (close_item == nullptr) {
        problemLoading("'EXIT'");
    }
    else {
        close_item->setPosition(Vec2(origin.x + visibleSize.width - close_item->getContentSize().width * 0.6,
            origin.y + visibleSize.height - close_item->getContentSize().height / 2));
        menu->addChild(close_item);
    }
    //设置按钮
    auto options_item = MenuItemImage::create("/MenuScene/Btn_Set.PNG", "/MenuScene/Btn_SetLight.PNG", CC_CALLBACK_1(MenuScene::goto_options, this));
    if (options_item == nullptr) {
        problemLoading("'options_item'");
    }
    else {
        options_item->setPosition(Vec2(origin.x + visibleSize.width * 0.2,
            origin.y + visibleSize.height / 3));
        menu->addChild(options_item);
    }
    //帮助按钮
    auto helper_item = MenuItemImage::create("/MenuScene/Btn_Help.PNG", "/MenuScene/Btn_HelpLight.PNG", CC_CALLBACK_1(MenuScene::goto_helper, this));
    if (helper_item == nullptr) {
        problemLoading("'helper_item'");
    }
    else {
        helper_item->setPosition(Vec2(origin.x + visibleSize.width * 0.8,
            origin.y + visibleSize.height / 3));
        menu->addChild(helper_item);
    }
    //冒险模式
    auto adventure_item = MenuItemImage::create("/MenuScene/Btn_NormalModle.PNG", "/MenuScene/Btn_NormalModleLight.PNG", CC_CALLBACK_1(MenuScene::goto_adventure, this));
    if (adventure_item == nullptr) {
        problemLoading("'adventure_item'");
    }
    else {
        adventure_item->setScale(0.9f);
        adventure_item->setPosition(Vec2(origin.x + visibleSize.width / 2 - adventure_item->getContentSize().width,
            origin.y + visibleSize.height / 8));
        menu->addChild(adventure_item);
    }
    //BOSS模式
    auto boss_item = MenuItemImage::create("/MenuScene/Btn_Boss.PNG", "/MenuScene/Btn_BossLight.PNG", CC_CALLBACK_1(MenuScene::goto_boss, this));
    if (boss_item == nullptr) {
        problemLoading("'boss_item'");
    }
    else {
        boss_item->setScale(0.9f);
        boss_item->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 8));
        menu->addChild(boss_item);
        if (UserDefault::getInstance()->getIntegerForKey("if_boss_lock") == 1) {
            auto boss_lock = Sprite::create("/MenuScene/lock.png");
            if (boss_lock == nullptr) {
                problemLoading("'lock.png'");
            }
            else {
                boss_lock->setName("boss_lock");
                boss_lock->setScale(1.4);
                boss_lock->setPosition(Vec2(origin.x + visibleSize.width / 2 + boss_item->getContentSize().width * 0.41,
                    origin.y + visibleSize.height / 8 - boss_item->getContentSize().height / 5));
                this->addChild(boss_lock,1);
            }
        }
    }
    //怪物巢
    auto nest_item = MenuItemImage::create("/MenuScene/Btn_MonsterNest.PNG", "/MenuScene/Btn_MonsterNestLight.PNG", CC_CALLBACK_1(MenuScene::goto_nest, this));
    if (nest_item == nullptr) {
        problemLoading("'nest_item'");
    }
    else {
        nest_item->setScale(0.9f);
        nest_item->setPosition(Vec2(origin.x + visibleSize.width / 2 + nest_item->getContentSize().width,
            origin.y + visibleSize.height / 8));
        menu->addChild(nest_item);
        if (UserDefault::getInstance()->getIntegerForKey("if_nest_lock") == 1) {
            auto nest_lock = Sprite::create("/MenuScene/lock.png");
            if (nest_lock == nullptr) {
                problemLoading("'lock.png'");
            }
            else {
                nest_lock->setName("nest_lock");
                nest_lock->setScale(1.4);
                nest_lock->setPosition(Vec2(origin.x + visibleSize.width / 2 + nest_item->getContentSize().width * 1.44,
                    origin.y + visibleSize.height / 8 - nest_item->getContentSize().height / 5));
                this->addChild(nest_lock,1);
            }
        }
    }
    this->addChild(menu);

    return true;
}

void MenuScene::close_game(Ref* psender) {

    AudioEngine::end();
    Director::getInstance()->end();

    exit(0);
}

void  MenuScene::goto_options(Ref* pSender) {
    button_sound_effect();
    auto options_scene = OptionsScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInT::create(0.2, options_scene));//以从上向下滑动方式切换
}

void  MenuScene::goto_helper(Ref* pSender) {
    button_sound_effect();
    auto helper_scene = HelperScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInB::create(0.2, helper_scene));
}

void  MenuScene::goto_adventure(Ref* psender) {
    button_sound_effect();
    auto gameselection_scene = GameSelectionScene::createScene();
    Director::getInstance()->replaceScene(TransitionFlipAngular::create(0.2, gameselection_scene));
}

void  MenuScene::goto_boss(Ref* psender) {
    button_sound_effect();
    if (UserDefault::getInstance()->getIntegerForKey("if_boss_lock") == 1) {

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
        auto boss_lock_image = Sprite::create("/MenuScene/boss_lock_image.png");
        boss_lock_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));
        boss_lock_image->setScale(1.4);
        black_layer->addChild(boss_lock_image);
        /********************************  按钮  ****************************************/
        auto menu = Menu::create();
        menu->setPosition(Vec2::ZERO);

        auto lock_btn = MenuItemImage::create("/MenuScene/lock_btn_normal.png", "/MenuScene/lock_btn_selected.png");
        lock_btn->setPosition(Vec2(origin.x + visibleSize.width *0.55,
            origin.y + visibleSize.height * 0.4));
        lock_btn->setCallback([this,black_layer](Ref* psender) {
            button_sound_effect();
            this->removeChild(black_layer);
        });
        lock_btn->setScale(1.4);
        menu->addChild(lock_btn);
        black_layer->addChild(menu);

        this->addChild(black_layer,2);
    }
    else {
        ;//boss_pattern待开发
    }
}

void  MenuScene::goto_nest(Ref* psender) {
    button_sound_effect();
    if (UserDefault::getInstance()->getIntegerForKey("if_nest_lock") == 1) {

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
        auto boss_lock_image = Sprite::create("/MenuScene/nest_lock_image.png");
        boss_lock_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));
        boss_lock_image->setScale(1.4);
        black_layer->addChild(boss_lock_image);
        /********************************  按钮  ****************************************/
        auto menu = Menu::create();
        menu->setPosition(Vec2::ZERO);

        auto lock_btn = MenuItemImage::create("/MenuScene/lock_btn_normal.png", "/MenuScene/lock_btn_selected.png");
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
        ;//nest_pattern待开发
    }
}