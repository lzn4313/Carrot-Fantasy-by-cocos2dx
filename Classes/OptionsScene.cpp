#include "MenuScene.h"
#include "OptionsScene.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include "sound&music.h"
#include"GameData.h"
#include<string>
USING_NS_CC;
using namespace cocos2d::ui;
/*错误处理*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}
/**********************   OptionsScene类   ***********************************/
Scene* OptionsScene::createScene()
{
    return OptionsScene::create();
}
bool OptionsScene::init()
{
    /*初始化场景*/
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /**********************  选项层  ***********************/
    auto set_layer = SetLayer::createLayer();
    set_layer->setName("SetLayer");
    this->addChild(set_layer, 0);
    /********************************  主菜单  ************************************/
    auto menu_all = Menu::create();
    menu_all->setPosition(Vec2::ZERO);

    auto home = MenuItemImage::create("/OptionsScene/Btn_Return.PNG", "/OptionsScene/Btn_ReturnLight.PNG", CC_CALLBACK_1(OptionsScene::goto_menu, this));
    home->setPosition(Vec2(origin.x + visibleSize.width * 0.1,
        origin.y + visibleSize.height * 0.9));
    menu_all->addChild(home);

    this->addChild(menu_all, 1);
    /*********************************  切换选项卡  ************************************/
    //set选项卡
    auto set_btn = ui::Button::create("/OptionsScene/setting02-hd_45_normal.PNG", "/OptionsScene/setting02-hd_45_normal.PNG", "/OptionsScene/setting02-hd_45.PNG");
    set_btn->setName("SetBtn");
    set_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.3,
        origin.y + visibleSize.height * 0.925));
    set_btn->setContentSize(Size(set_btn->getContentSize().width * 2, set_btn->getContentSize().height));
    set_btn->addTouchEventListener(CC_CALLBACK_2(OptionsScene::goto_set, this));
    set_btn->setEnabled(false);
    this->addChild(set_btn,1);
    //statistics选项卡
    auto statistics_btn = ui::Button::create("/OptionsScene/setting02-hd_43_normal.PNG", "/OptionsScene/setting02-hd_43_normal.PNG", "/OptionsScene/setting02-hd_43.PNG");
    statistics_btn->setName("StatisticsBtn");
    statistics_btn->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height * 0.925));
    statistics_btn->setScale(1.4);
    statistics_btn->addTouchEventListener(CC_CALLBACK_2(OptionsScene::goto_statistics, this));
    this->addChild(statistics_btn,1);
    //person选项卡
    auto person_btn = ui::Button::create("/OptionsScene/setting02-hd_48_normal.PNG", "/OptionsScene/setting02-hd_48_normal.PNG", "/OptionsScene/setting02-hd_48.PNG");
    person_btn->setName("PersonBtn");
    person_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.7,
        origin.y + visibleSize.height * 0.925));
    person_btn->setScale(1.4);
    person_btn->addTouchEventListener(CC_CALLBACK_2(OptionsScene::goto_person, this));
    this->addChild(person_btn,1);
 
    return true;
}
void OptionsScene::goto_menu(Ref* psender)
{
    button_sound_effect();
    auto menu_scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInB::create(0.3, menu_scene));

}
void OptionsScene::goto_set(Ref* psender, Widget::TouchEventType type)//设置仅选项层可见
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::CANCELED:
            break;
        case Widget::TouchEventType::ENDED:
            button_sound_effect();
            auto visibleSize = Director::getInstance()->getVisibleSize();
            Vec2 origin = Director::getInstance()->getVisibleOrigin();

            if (this->getChildByName("StatisticsLayer") != nullptr) {
                this->removeChildByName("StatisticsLayer");
            }
            if (this->getChildByName("PersonLayer") != nullptr) {
                this->removeChildByName("PersonLayer");
            }
            auto set_layer = SetLayer::createLayer();
            set_layer->setName("SetLayer");
            this->addChild(set_layer, 0);

            Node* set_btn = this->getChildByName("SetBtn");
            static_cast<ui::Button*>(set_btn)->setEnabled(false);
            set_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.3,
                origin.y + visibleSize.height * 0.925));
            set_btn->setScale(1);

            Node* statistics_btn = this->getChildByName("StatisticsBtn");
            static_cast<ui::Button*>(statistics_btn)->setEnabled(true);
            statistics_btn->setPosition(Vec2(origin.x + visibleSize.width / 2,
                origin.y + visibleSize.height * 0.925));
            statistics_btn->setScale(1.4);

            Node* person_btn = this->getChildByName("PersonBtn");
            static_cast<ui::Button*>(person_btn)->setEnabled(true);
            person_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.7,
                origin.y + visibleSize.height * 0.925));
            person_btn->setScale(1.4);

            break;
    }
}
void OptionsScene::goto_statistics(Ref* psender, Widget::TouchEventType type)//设置仅统计层可见
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::CANCELED:
            break;
        case Widget::TouchEventType::ENDED:

            button_sound_effect();
            auto visibleSize = Director::getInstance()->getVisibleSize();
            Vec2 origin = Director::getInstance()->getVisibleOrigin();

            if (this->getChildByName("SetLayer") != nullptr) {
                this->removeChildByName("SetLayer");
            }
            if (this->getChildByName("PersonLayer") != nullptr) {
                this->removeChildByName("PersonLayer");
            }
            auto statistics_layer = StatisticsLayer::createLayer();
            if (statistics_layer == nullptr) {
                problemLoading("'statistics_layer'");
            }
            statistics_layer->setName("StatisticsLayer");
            this->addChild(statistics_layer, 0);

            Node* set_btn = this->getChildByName("SetBtn");
            static_cast<ui::Button*>(set_btn)->setEnabled(true);
            set_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.3,
                origin.y + visibleSize.height * 0.93));
            set_btn->setScale(1.4);

            Node* statistics_btn = this->getChildByName("StatisticsBtn");
            static_cast<ui::Button*>(statistics_btn)->setEnabled(false);
            statistics_btn->setPosition(Vec2(origin.x + visibleSize.width / 2,
                origin.y + visibleSize.height * 0.925));
            statistics_btn->setScale(1);

            Node* person_btn = this->getChildByName("PersonBtn");
            static_cast<ui::Button*>(person_btn)->setEnabled(true);
            person_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.7,
                origin.y + visibleSize.height * 0.925));
            person_btn->setScale(1.4);

            break;
    }
}
void OptionsScene::goto_person(Ref* psender, Widget::TouchEventType type)//设置仅人员层可见
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::CANCELED:
            break;
        case Widget::TouchEventType::ENDED:

            button_sound_effect();
            auto visibleSize = Director::getInstance()->getVisibleSize();
            Vec2 origin = Director::getInstance()->getVisibleOrigin();

            if (this->getChildByName("SetLayer") != nullptr) {
                this->removeChildByName("SetLayer");
            }
            if (this->getChildByName("StatisticsLayer") != nullptr) {
                this->removeChildByName("StatisticsLayer");
            }
            auto person_layer = PersonLayer::createLayer();
            person_layer->setName("PersonLayer");
            this->addChild(person_layer, 0);


            Node* set_btn = this->getChildByName("SetBtn");
            static_cast<ui::Button*>(set_btn)->setEnabled(true);
            set_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.3,
                origin.y + visibleSize.height * 0.93));
            set_btn->setScale(1.4);

            Node* statistics_btn = this->getChildByName("StatisticsBtn");
            static_cast<ui::Button*>(statistics_btn)->setEnabled(true);
            statistics_btn->setPosition(Vec2(origin.x + visibleSize.width / 2,
                origin.y + visibleSize.height * 0.925));
            statistics_btn->setScale(1.4);
            statistics_btn->setScale(1.4);

            Node* person_btn = this->getChildByName("PersonBtn");
            static_cast<ui::Button*>(person_btn)->setEnabled(false);
            person_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.7,
                origin.y + visibleSize.height * 0.925));
            person_btn->setScale(1);

            break;
    }
}
/**************************   SetLayer类   ******************************/
cocos2d::Layer* SetLayer::createLayer()
{
    return SetLayer::create();
}
bool SetLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto set = Sprite::create("/OptionsScene/SettingBG1.PNG");
    if (set == nullptr)
    {
        problemLoading("'SettingBG1.PNG'");
    }
    else
    {
        set->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));

        this->addChild(set);
    }
    //其他背景
    auto sound_txt = Sprite::create("/OptionsScene/setting02-hd_0.PNG");
    if (sound_txt == nullptr) {
        problemLoading("'setting02-hd_0.PNG'");
    }
    else {
        sound_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.4,
            origin.y + visibleSize.height * 0.7));
        this->addChild(sound_txt);
    }

    auto bgmusic_txt = Sprite::create("/OptionsScene/setting02-hd_2.PNG");
    if (bgmusic_txt == nullptr) {
        problemLoading("'setting02-hd_2.PNG'");
    }
    else {
        bgmusic_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.6,
            origin.y + visibleSize.height * 0.7));
        this->addChild(bgmusic_txt);
    }

    auto appeal_txt = Sprite::create("/OptionsScene/setting02-hd_7.PNG");
    if (appeal_txt == nullptr) {
        problemLoading("'setting02-hd_7.PNG'");
    }
    else {
        appeal_txt->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));
        this->addChild(appeal_txt);
    }

    auto weibo_image = Sprite::create("/OptionsScene/setting02-hd_12.PNG");
    if (weibo_image == nullptr) {
        problemLoading("'setting02-hd_12.PNG'");
    }
    else {
        weibo_image->setPosition(Vec2(origin.x + visibleSize.width * 0.4,
            origin.y + visibleSize.height * 0.35));
        weibo_image->setScale(2);
        this->addChild(weibo_image);
    }

    auto wechat_image = Sprite::create("/OptionsScene/setting02-hd_16.PNG");
    if (wechat_image == nullptr) {
        problemLoading("'setting02-hd_16.PNG'");
    }
    else {
        wechat_image->setPosition(Vec2(origin.x + visibleSize.width * 0.6,
            origin.y + visibleSize.height * 0.35));
        wechat_image->setScale(2);
        this->addChild(wechat_image);
    }
    /*********************************  选项层菜单  **************************************/
    auto set_menu = Menu::create();
    set_menu->setPosition(Vec2::ZERO);
    //音效toggle
    auto sound_on_sprite = Sprite::create("/OptionsScene/setting02-hd_6.PNG");
    auto sound_on = MenuItemSprite::create(sound_on_sprite, sound_on_sprite);
    auto sound_off_sprite = Sprite::create("/OptionsScene/setting02-hd_11.PNG");
    auto sound_off = MenuItemSprite::create(sound_off_sprite, sound_off_sprite);
    MenuItemToggle* sound_toggle; 
    if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
        sound_toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SetLayer::close_sound, this), sound_on, sound_off, NULL);
    }
    else {
        sound_toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SetLayer::close_sound, this), sound_off, sound_on, NULL);
    }
    sound_toggle->setPosition(Vec2(origin.x + visibleSize.width * 0.4,
        origin.y + visibleSize.height * 0.6));
    set_menu->addChild(sound_toggle);
    ////背景音乐toggle
    auto bgmusic_on_sprite = Sprite::create("/OptionsScene/setting02-hd_15.PNG");
    auto bgmusic_on = MenuItemSprite::create(bgmusic_on_sprite, bgmusic_on_sprite);
    auto bgmusic_off_sprite = Sprite::create("/OptionsScene/setting02-hd_21.PNG");
    auto bgmusic_off = MenuItemSprite::create(bgmusic_off_sprite, bgmusic_off_sprite);
    MenuItemToggle* bgmusic_toggle;
    if (UserDefault::getInstance()->getIntegerForKey("bg_music") == 1) {
        bgmusic_toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SetLayer::close_bgmusic, this), bgmusic_on, bgmusic_off, NULL);
    }
    else {
        bgmusic_toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SetLayer::close_bgmusic, this), bgmusic_off, bgmusic_on, NULL);
    }
    bgmusic_toggle->setPosition(Vec2(origin.x + visibleSize.width * 0.6,
        origin.y + visibleSize.height * 0.6));
    set_menu->addChild(bgmusic_toggle);
    //重置游戏
    auto reset_game = MenuItemImage::create("/OptionsScene/setting02-hd_55.PNG", "/OptionsScene/setting02-hd_54.PNG", CC_CALLBACK_1(SetLayer::reset_game, this));
    reset_game->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height * 0.15));
    set_menu->addChild(reset_game);

    this->addChild(set_menu);
    this->setVisible(true);


    return true;
}
void SetLayer::close_sound(Ref* psender)
{
    button_sound_effect();
    if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 0) {
        UserDefault::getInstance()->setIntegerForKey("sound_effect", 1);
    }
    else if(UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1){
        UserDefault::getInstance()->setIntegerForKey("sound_effect", 0);
    }
}
void SetLayer::close_bgmusic(Ref* psender)
{
    button_sound_effect();
    if (UserDefault::getInstance()->getIntegerForKey("bg_music") == 0) {
        UserDefault::getInstance()->setIntegerForKey("bg_music", 1);
        AudioEngine::play2d("/sound/CarrotFantasy.mp3", true, 0.5);
    }
    else if (UserDefault::getInstance()->getIntegerForKey("bg_music") == 1) {
        UserDefault::getInstance()->setIntegerForKey("bg_music", 0);
        AudioEngine::stopAll();
    }
}
void SetLayer::reset_game(Ref* psender)
{
    button_sound_effect();

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
    auto reset_image = Sprite::create("/OptionsScene/reset_image.png");
    reset_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    reset_image->setScale(1.4);
    black_layer->addChild(reset_image);
    /********************************  按钮  ****************************************/
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);

    auto reset_yes_btn = MenuItemImage::create("/OptionsScene/reset_yes_normal.png", "/OptionsScene/reset_yes_selected.png");
    reset_yes_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.35,
        origin.y + visibleSize.height * 0.5));
    reset_yes_btn->setCallback([this, black_layer](Ref* psender) {
        reset_data();
        button_sound_effect();
        this->getParent()->removeChild(black_layer);
        });
    reset_yes_btn->setScale(1.4);
    menu->addChild(reset_yes_btn);

    auto reset_no_btn = MenuItemImage::create("/OptionsScene/reset_no_normal.png", "/OptionsScene/reset_no_selected.png");
    reset_no_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.65,
        origin.y + visibleSize.height * 0.5));
    reset_no_btn->setCallback([this, black_layer](Ref* psender) {
        button_sound_effect();
        this->getParent()->removeChild(black_layer);
        });
    reset_no_btn->setScale(1.4);
    menu->addChild(reset_no_btn);
    black_layer->addChild(menu);

    this->getParent()->addChild(black_layer, 2);

}
/*************************   StatisticsLayer类  ****************************/
cocos2d::Layer* StatisticsLayer::createLayer()
{
    return StatisticsLayer::create();
}
bool StatisticsLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //背景图
    auto statistics = Sprite::create("/OptionsScene/SettingBG2.PNG");
    if (statistics == nullptr)
    {
        problemLoading("'SettingBG2.PNG'");
    }
    else
    {
        statistics->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));

        this->addChild(statistics);
        //其他背景
        auto bg1 = Sprite::create("/OptionsScene/setting02-hd_22.PNG");
        if (bg1 == nullptr) {
            problemLoading("'setting02-hd_22.PNG'");
        }
        else {
            bg1->setPosition(Vec2(origin.x + visibleSize.width * 0.5,
                origin.y + visibleSize.height * 0.68));
            this->addChild(bg1);

            auto statistics_txt_1 = Sprite::create("/OptionsScene/setting02-hd_23.PNG");
            statistics_txt_1->setPosition(Vec2(origin.x + visibleSize.width * 0.823,
                origin.y + visibleSize.height * 0.68));
            this->addChild(statistics_txt_1);
            string adventure_statistics = std::to_string(UserDefault::getInstance()->getIntegerForKey("adventure_statistics"));
            auto adventure_statistics_label = Label::createWithTTF(adventure_statistics, "fonts/Marker Felt.ttf", 28);
            adventure_statistics_label->setAlignment(TextHAlignment::RIGHT);
            adventure_statistics_label->setAnchorPoint(Vec2(1, 0.5));
            adventure_statistics_label->setPosition(Vec2(origin.x + visibleSize.width * 0.77,
                origin.y + visibleSize.height * 0.68));
            this->addChild(adventure_statistics_label);
        }
        auto bg2 = Sprite::create("/OptionsScene/setting02-hd_27.PNG");
        if (bg2 == nullptr) {
            problemLoading("'setting02-hd_27.PNG'");
        }
        else {
            bg2->setPosition(Vec2(origin.x + visibleSize.width * 0.5,
                origin.y + visibleSize.height * 0.58));
            this->addChild(bg2);

            auto statistics_txt_2 = Sprite::create("/OptionsScene/setting02-hd_23.PNG");
            statistics_txt_2->setPosition(Vec2(origin.x + visibleSize.width * 0.823,
                origin.y + visibleSize.height * 0.58));
            this->addChild(statistics_txt_2);

            string hide_statistics = std::to_string(UserDefault::getInstance()->getIntegerForKey("hide_statistics"));
            auto hide_statistics_label = Label::createWithTTF(hide_statistics, "fonts/Marker Felt.ttf", 28);
            hide_statistics_label->setAlignment(TextHAlignment::RIGHT);
            hide_statistics_label->setAnchorPoint(Vec2(1, 0.5));
            hide_statistics_label->setPosition(Vec2(origin.x + visibleSize.width * 0.77,
                origin.y + visibleSize.height * 0.58));
            this->addChild(hide_statistics_label);
        }
        auto bg3 = Sprite::create("/OptionsScene/setting02-hd_31.PNG");
        if (bg3 == nullptr) {
            problemLoading("'setting02-hd_31.PNG'");
        }
        else {
            bg3->setPosition(Vec2(origin.x + visibleSize.width * 0.51,
                origin.y + visibleSize.height * 0.49));
            this->addChild(bg3);

            auto statistics_txt_3 = Sprite::create("/OptionsScene/setting02-hd_23.PNG");
            statistics_txt_3->setPosition(Vec2(origin.x + visibleSize.width * 0.823,
                origin.y + visibleSize.height * 0.49));
            this->addChild(statistics_txt_3);

            string bosspattern_statistics = std::to_string(UserDefault::getInstance()->getIntegerForKey("bosspattern_statistics"));
            auto bosspattern_statistics_label = Label::createWithTTF(bosspattern_statistics, "fonts/Marker Felt.ttf", 28);
            bosspattern_statistics_label->setAlignment(TextHAlignment::RIGHT);
            bosspattern_statistics_label->setAnchorPoint(Vec2(1, 0.5));
            bosspattern_statistics_label->setPosition(Vec2(origin.x + visibleSize.width * 0.77,
                origin.y + visibleSize.height * 0.49));
            this->addChild(bosspattern_statistics_label);
        }
        auto bg4 = Sprite::create("/OptionsScene/setting02-hd_35.PNG");
        if (bg4 == nullptr) {
            problemLoading("'setting02-hd_35.PNG'");
        }
        else {
            bg4->setPosition(Vec2(origin.x + visibleSize.width * 0.485,
                origin.y + visibleSize.height * 0.41));
            this->addChild(bg4);

            string money_statistics = std::to_string(UserDefault::getInstance()->getIntegerForKey("money_statistics"));
            auto money_statistics_label = Label::createWithTTF(money_statistics, "fonts/Marker Felt.ttf", 28);
            money_statistics_label->setAlignment(TextHAlignment::RIGHT);
            money_statistics_label->setAnchorPoint(Vec2(1, 0.5));
            money_statistics_label->setPosition(Vec2(origin.x + visibleSize.width * 0.85,
                origin.y + visibleSize.height * 0.41));
            this->addChild(money_statistics_label);
        }
        auto bg5 = Sprite::create("/OptionsScene/setting02-hd_38.PNG");
        if (bg5 == nullptr) {
            problemLoading("'setting02-hd_38.PNG'");
        }
        else {
            bg5->setPosition(Vec2(origin.x + visibleSize.width * 0.523,
                origin.y + visibleSize.height * 0.32));
            this->addChild(bg5);

            string monster_statistics = std::to_string(UserDefault::getInstance()->getIntegerForKey("monster_statistics"));
            auto monster_statistics_label = Label::createWithTTF(monster_statistics, "fonts/Marker Felt.ttf", 28);
            monster_statistics_label->setAlignment(TextHAlignment::RIGHT);
            monster_statistics_label->setAnchorPoint(Vec2(1, 0.5));
            monster_statistics_label->setPosition(Vec2(origin.x + visibleSize.width * 0.85,
                origin.y + visibleSize.height * 0.32));
            this->addChild(monster_statistics_label);
        }
        auto bg6 = Sprite::create("/OptionsScene/setting02-hd_42.PNG");
        if (bg6 == nullptr) {
            problemLoading("'setting02-hd_42.PNG'");
        }
        else {
            bg6->setPosition(Vec2(origin.x + visibleSize.width * 0.534,
                origin.y + visibleSize.height * 0.23));
            this->addChild(bg6);

            string boss_statistics = std::to_string(UserDefault::getInstance()->getIntegerForKey("boss_statistics"));
            auto boss_statistics_label = Label::createWithTTF(boss_statistics, "fonts/Marker Felt.ttf", 28);
            boss_statistics_label->setAlignment(TextHAlignment::RIGHT);
            boss_statistics_label->setAnchorPoint(Vec2(1, 0.5));
            boss_statistics_label->setPosition(Vec2(origin.x + visibleSize.width * 0.85,
                origin.y + visibleSize.height * 0.23));
            this->addChild(boss_statistics_label);
        }
        auto bg7 = Sprite::create("/OptionsScene/setting02-hd_44.PNG");
        if (bg7 == nullptr) {
            problemLoading("'setting02-hd_44.PNG'");
        }
        else {
            bg7->setPosition(Vec2(origin.x + visibleSize.width * 0.523,
                origin.y + visibleSize.height * 0.14));
            this->addChild(bg7);

            string damage_statistics = std::to_string(UserDefault::getInstance()->getIntegerForKey("damage_statistics"));
            auto damage_statistics_label = Label::createWithTTF(damage_statistics, "fonts/Marker Felt.ttf", 28);
            damage_statistics_label->setAlignment(TextHAlignment::RIGHT);
            damage_statistics_label->setAnchorPoint(Vec2(1, 0.5));
            damage_statistics_label->setPosition(Vec2(origin.x + visibleSize.width * 0.85,
                origin.y + visibleSize.height * 0.14));
            this->addChild(damage_statistics_label);
        }
    }
    return true;
}
/*************************  PersonLayer类  ********************************/
cocos2d::Layer* PersonLayer::createLayer()
{
    return PersonLayer::create();
}
bool PersonLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //背景
    auto person = Sprite::create("/OptionsScene/SettingBG3.PNG");
    if (person == nullptr)
    {
        problemLoading("'SettingBG3.PNG'");
    }
    else
    {
        person->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));

        this->addChild(person);
    }

    return true;
}
