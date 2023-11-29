#include "MenuScene.h"
#include "OptionsScene.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include "sound&music.h"
USING_NS_CC;
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
    this->addChild(set_layer);
    /*****************  统计界面  ******************/
    auto statistics_layer = StatisticsLayer::createLayer();
    statistics_layer->setName("StatisticsLayer");
    this->addChild(statistics_layer);
    /****************  开发人员界面  ***************/
    auto person_layer = PersonLayer::createLayer();
    person_layer->setName("PersonLayer");
    this->addChild(person_layer);
    /********************************  主菜单  ************************************/
    auto menu_all = Menu::create();
    menu_all->setPosition(Vec2::ZERO);

    auto home = MenuItemImage::create("/OptionsScene/Btn_Return.PNG", "/OptionsScene/Btn_ReturnLight.PNG", CC_CALLBACK_1(OptionsScene::goto_menu, this));
    home->setPosition(Vec2(origin.x + visibleSize.width * 0.1,
        origin.y + visibleSize.height * 0.9));
    menu_all->addChild(home);

    this->addChild(menu_all);
    /*********************************  切换选项卡  ************************************/
    //set选项卡
    auto set_btn = ui::Button::create("/OptionsScene/setting02-hd_45_normal.PNG", "/OptionsScene/setting02-hd_45_normal.PNG", "/OptionsScene/setting02-hd_45.PNG");
    set_btn->setName("SetBtn");
    set_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.3,
        origin.y + visibleSize.height * 0.925));
    set_btn->setContentSize(Size(set_btn->getContentSize().width * 2, set_btn->getContentSize().height));
    set_btn->addTouchEventListener(CC_CALLBACK_1(OptionsScene::goto_set, this));
    set_btn->setEnabled(false);
    this->addChild(set_btn);
    //statistics选项卡
    auto statistics_btn = ui::Button::create("/OptionsScene/setting02-hd_43_normal.PNG", "/OptionsScene/setting02-hd_43_normal.PNG", "/OptionsScene/setting02-hd_43.PNG");
    statistics_btn->setName("StatisticsBtn");
    statistics_btn->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height * 0.925));
    statistics_btn->setScale(1.4);
    statistics_btn->addTouchEventListener(CC_CALLBACK_1(OptionsScene::goto_statistics, this));
    this->addChild(statistics_btn);
    //person选项卡
    auto person_btn = ui::Button::create("/OptionsScene/setting02-hd_48_normal.PNG", "/OptionsScene/setting02-hd_48_normal.PNG", "/OptionsScene/setting02-hd_48.PNG");
    person_btn->setName("PersonBtn");
    person_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.7,
        origin.y + visibleSize.height * 0.925));
    person_btn->setScale(1.4);
    person_btn->addTouchEventListener(CC_CALLBACK_1(OptionsScene::goto_person, this));
    this->addChild(person_btn);

    return true;
}
void OptionsScene::goto_menu(Ref* psender)
{
    auto menu_scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInB::create(0.3, menu_scene));

}
void OptionsScene::goto_set(Ref* psender)//设置仅选项层可见
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Node* set = this->getChildByName("SetLayer");
    Node* statistics = this->getChildByName("StatisticsLayer");
    Node* person = this->getChildByName("PersonLayer");

    set->setVisible(true);
    statistics->setVisible(false);
    person->setVisible(false);

    Node* set_btn = this->getChildByName("SetBtn");
    static_cast<ui::Button*>(set_btn)->setEnabled(false);
    set_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.3,
        origin.y + visibleSize.height * 0.925));
    set_btn->setScale(1);

    Node* statistics_btn =this->getChildByName("StatisticsBtn");
    static_cast<ui::Button*>(statistics_btn)->setEnabled(true);
    statistics_btn->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height * 0.925));
    statistics_btn->setScale(1.4);

    Node* person_btn = this->getChildByName("PersonBtn");
    static_cast<ui::Button*>(person_btn)->setEnabled(true);
    person_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.7,
        origin.y + visibleSize.height * 0.925));
    person_btn->setScale(1.4);
}
void OptionsScene::goto_statistics(Ref* psender)//设置仅统计层可见
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Node* set = this->getChildByName("SetLayer");
    Node* statistics = this->getChildByName("StatisticsLayer");
    Node* person = this->getChildByName("PersonLayer");

    set->setVisible(false);
    statistics->setVisible(true);
    person->setVisible(false);

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
}
void OptionsScene::goto_person(Ref* psender)//设置仅人员层可见
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Node* set = this->getChildByName("SetLayer");
    Node* statistics = this->getChildByName("StatisticsLayer");
    Node* person = this->getChildByName("PersonLayer");

    set->setVisible(false);
    statistics->setVisible(false);
    person->setVisible(true);

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
    if (sound_effect==1) {
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
    if (AudioEngine::getState(bg_music_id) == AudioEngine::AudioState(1)) {
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
    if (sound_effect == 1) {
        sound_effect = 0;
    }
    else {
        sound_effect = 1;
    }
}
void SetLayer::close_bgmusic(Ref* psender)
{
    auto state = AudioEngine::getState(bg_music_id);
    if (AudioEngine::getState(bg_music_id) == AudioEngine::AudioState(1)) {
        AudioEngine::pause(bg_music_id);
    }
    else if (AudioEngine::getState(bg_music_id) == AudioEngine::AudioState(2)) {
        AudioEngine::resume(bg_music_id);
    }
}
void SetLayer::reset_game(Ref* psender)
{
    //待实现
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
    auto statics = Sprite::create("/OptionsScene/SettingBG2.PNG");
    if (statics == nullptr)
    {
        problemLoading("'SettingBG2.PNG'");
    }
    else
    {
        statics->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));

        this->addChild(statics);
    }
    //其他背景
    auto bg1 = Sprite::create("/OptionsScene/setting02-hd_22.PNG");
    if (bg1 == nullptr) {
        problemLoading("'setting02-hd_22.PNG'");
    }
    else {
        bg1->setPosition(Vec2(origin.x + visibleSize.width * 0.5,
            origin.y + visibleSize.height * 0.68));
        this->addChild(bg1);
    }
    auto bg2 = Sprite::create("/OptionsScene/setting02-hd_27.PNG");
    if (bg2 == nullptr) {
        problemLoading("'setting02-hd_27.PNG'");
    }
    else {
        bg2->setPosition(Vec2(origin.x + visibleSize.width * 0.5,
            origin.y + visibleSize.height * 0.58));
        this->addChild(bg2);
    }
    auto bg3 = Sprite::create("/OptionsScene/setting02-hd_31.PNG");
    if (bg3 == nullptr) {
        problemLoading("'setting02-hd_31.PNG'");
    }
    else {
        bg3->setPosition(Vec2(origin.x + visibleSize.width * 0.51,
            origin.y + visibleSize.height * 0.49));
        this->addChild(bg3);
    }
    auto bg4 = Sprite::create("/OptionsScene/setting02-hd_35.PNG");
    if (bg4 == nullptr) {
        problemLoading("'setting02-hd_35.PNG'");
    }
    else {
        bg4->setPosition(Vec2(origin.x + visibleSize.width * 0.485,
            origin.y + visibleSize.height * 0.41));
        this->addChild(bg4);
    }
    auto bg5 = Sprite::create("/OptionsScene/setting02-hd_38.PNG");
    if (bg5 == nullptr) {
        problemLoading("'setting02-hd_38.PNG'");
    }
    else {
        bg5->setPosition(Vec2(origin.x + visibleSize.width * 0.523,
            origin.y + visibleSize.height * 0.32));
        this->addChild(bg5);
    }
    auto bg6 = Sprite::create("/OptionsScene/setting02-hd_42.PNG");
    if (bg6 == nullptr) {
        problemLoading("'setting02-hd_42.PNG'");
    }
    else {
        bg6->setPosition(Vec2(origin.x + visibleSize.width * 0.534,
            origin.y + visibleSize.height * 0.23));
        this->addChild(bg6);
    }
    auto bg7 = Sprite::create("/OptionsScene/setting02-hd_44.PNG");
    if (bg7 == nullptr) {
        problemLoading("'setting02-hd_44.PNG'");
    }
    else {
        bg7->setPosition(Vec2(origin.x + visibleSize.width * 0.523,
            origin.y + visibleSize.height * 0.14));
        this->addChild(bg7);
    }

    this->setVisible(false);


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

    this->setVisible(false);
    return true;
}
