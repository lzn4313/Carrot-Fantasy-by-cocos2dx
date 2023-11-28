#include "MenuScene.h"
#include "OptionsScene.h"

USING_NS_CC;
/*错误处理*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}
/**********************OptionsScene类***********************************/

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

    /******************************************************选项层********************************************************************/
    auto set_layer = Layer::create();
    set_layer->setName("SetLayer");
    //背景
    auto set = Sprite::create("/OptionsScene/SettingBG1.PNG");
    if (set == nullptr)
    {
        problemLoading("'SettingBG1.PNG'");
    }
    else
    {
        set->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));

        set_layer->addChild(set);
    }

    set_layer->setVisible(true);
    //选项层下的set_title
    auto set_set_title = Sprite::create("/OptionsScene/setting02-hd_45.PNG");
    if (set_set_title == nullptr) {
        problemLoading("'setting02-hd_45.PNG'");
    }
    else {
        set_set_title->setPosition(Vec2(origin.x + visibleSize.width * 0.3,
            origin.y + visibleSize.height * 0.925));
        set_layer->addChild(set_set_title);
    }
    //其他背景
    auto sound_txt = Sprite::create("/OptionsScene/setting02-hd_0.PNG");
    if (sound_txt == nullptr) {
        problemLoading("'setting02-hd_0.PNG'");
    }
    else {
        sound_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.4,
            origin.y + visibleSize.height * 0.7));
        set_layer->addChild(sound_txt);
    }

    auto bgmusic_txt = Sprite::create("/OptionsScene/setting02-hd_2.PNG");
    if (bgmusic_txt == nullptr) {
        problemLoading("'setting02-hd_2.PNG'");
    }
    else {
        bgmusic_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.6,
            origin.y + visibleSize.height * 0.7));
        set_layer->addChild(bgmusic_txt);
    }

    auto appeal_txt = Sprite::create("/OptionsScene/setting02-hd_7.PNG");
    if (appeal_txt == nullptr) {
        problemLoading("'setting02-hd_7.PNG'");
    }
    else {
        appeal_txt->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));
        set_layer->addChild(appeal_txt);
    }

    auto weibo_image = Sprite::create("/OptionsScene/setting02-hd_12.PNG");
    if (weibo_image == nullptr) {
        problemLoading("'setting02-hd_12.PNG'");
    }
    else {
        weibo_image->setPosition(Vec2(origin.x + visibleSize.width * 0.4,
            origin.y + visibleSize.height * 0.35));
        weibo_image->setScale(2);
        set_layer->addChild(weibo_image);
    }

    auto wechat_image = Sprite::create("/OptionsScene/setting02-hd_16.PNG");
    if (wechat_image == nullptr) {
        problemLoading("'setting02-hd_16.PNG'");
    }
    else {
        wechat_image->setPosition(Vec2(origin.x + visibleSize.width * 0.6,
            origin.y + visibleSize.height * 0.35));
        wechat_image->setScale(2);
        set_layer->addChild(wechat_image);
    }
    //setmenu
    auto set_menu = Menu::create();
    set_menu->setPosition(Vec2::ZERO);

    //选项层下的statistics_title
    auto set_statistics_title = MenuItemImage::create("/OptionsScene/setting02-hd_43_normal.PNG",
        "/OptionsScene/setting02-hd_43_normal.PNG", CC_CALLBACK_1(OptionsScene::goto_statistics, this));
    set_statistics_title->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height * 0.935));
    set_statistics_title->setScale(1.4);
    set_menu->addChild(set_statistics_title);
    //选项层下的person_title
    auto set_person_title = MenuItemImage::create("/OptionsScene/setting02-hd_48_normal.PNG",
        "/OptionsScene/setting02-hd_48_normal.PNG", CC_CALLBACK_1(OptionsScene::goto_person, this));
    set_person_title->setPosition(Vec2(origin.x + visibleSize.width * 0.7,
        origin.y + visibleSize.height * 0.925));
    set_person_title->setScale(1.4);
    set_menu->addChild(set_person_title);
    //音效toggle
    auto sound_on_sprite = Sprite::create("/OptionsScene/setting02-hd_6.PNG");
    auto sound_on = MenuItemSprite::create(sound_on_sprite, sound_on_sprite);
    auto sound_off_sprite = Sprite::create("/OptionsScene/setting02-hd_11.PNG");
    auto sound_off = MenuItemSprite::create(sound_off_sprite, sound_off_sprite);
    auto sound_toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(OptionsScene::close_sound, this), sound_on, sound_off, NULL);
    
    sound_toggle->setPosition(Vec2(origin.x + visibleSize.width * 0.4,
        origin.y + visibleSize.height * 0.6));
    set_menu->addChild(sound_toggle);
    ////背景音乐toggle
    auto bgmusic_on_sprite = Sprite::create("/OptionsScene/setting02-hd_15.PNG");
    auto bgmusic_on = MenuItemSprite::create(bgmusic_on_sprite, bgmusic_on_sprite);
    auto bgmusic_off_sprite = Sprite::create("/OptionsScene/setting02-hd_21.PNG");
    auto bgmusic_off = MenuItemSprite::create(bgmusic_off_sprite, bgmusic_off_sprite);
    auto bgmusic_toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(OptionsScene::close_bgmusic, this), bgmusic_on, bgmusic_off, NULL);

    bgmusic_toggle->setPosition(Vec2(origin.x + visibleSize.width * 0.6,
        origin.y + visibleSize.height * 0.6));
    set_menu->addChild(bgmusic_toggle);
    //重置游戏
    auto reset_game = MenuItemImage::create("/OptionsScene/setting02-hd_55.PNG", "/OptionsScene/setting02-hd_54.PNG", CC_CALLBACK_1(OptionsScene::reset_game, this));

    reset_game->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height * 0.15));
    set_menu->addChild(reset_game);

    set_layer->addChild(set_menu);
    this->addChild(set_layer);
    set_layer->setVisible(true);
    /**********************************************************统计界面************************************************************/
    auto statistics_layer = Layer::create();
    statistics_layer->setName("StatisticsLayer");
    //背景
    auto statics = Sprite::create("/OptionsScene/SettingBG2.PNG");
    if (statics == nullptr)
    {
        problemLoading("'SettingBG2.PNG'");
    }
    else
    {
        statics->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));

        statistics_layer->addChild(statics);
    }
    
    //统计层下的statistics_title
    auto statistics_statistics_title = Sprite::create("/OptionsScene/setting02-hd_43.PNG");
    if (statistics_statistics_title == nullptr) {
        problemLoading("'setting02-hd_43.PNG'");
    }
    else {
        statistics_statistics_title->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height * 0.925));
        statistics_layer->addChild(statistics_statistics_title);
    }
    //其他背景
    auto bg1 = Sprite::create("/OptionsScene/setting02-hd_22.PNG");
    if (bg1 == nullptr) {
        problemLoading("'setting02-hd_22.PNG'");
    }
    else {
        bg1->setPosition(Vec2(origin.x + visibleSize.width * 0.5,
            origin.y + visibleSize.height * 0.68));
        statistics_layer->addChild(bg1);
    }
    auto bg2 = Sprite::create("/OptionsScene/setting02-hd_27.PNG");
    if (bg2 == nullptr) {
        problemLoading("'setting02-hd_27.PNG'");
    }
    else {
        bg2->setPosition(Vec2(origin.x + visibleSize.width * 0.5,
            origin.y + visibleSize.height * 0.58));
        statistics_layer->addChild(bg2);
    }  
    auto bg3 = Sprite::create("/OptionsScene/setting02-hd_31.PNG");
    if (bg3 == nullptr) {
        problemLoading("'setting02-hd_31.PNG'");
    }
    else {
        bg3->setPosition(Vec2(origin.x + visibleSize.width * 0.51,
            origin.y + visibleSize.height * 0.49));
        statistics_layer->addChild(bg3);
    }    
    auto bg4 = Sprite::create("/OptionsScene/setting02-hd_35.PNG");
    if (bg4 == nullptr) {
        problemLoading("'setting02-hd_35.PNG'");
    }
    else {
        bg4->setPosition(Vec2(origin.x + visibleSize.width * 0.485,
            origin.y + visibleSize.height * 0.41));
        statistics_layer->addChild(bg4);
    }  
    auto bg5 = Sprite::create("/OptionsScene/setting02-hd_38.PNG");
    if (bg5 == nullptr) {
        problemLoading("'setting02-hd_38.PNG'");
    }
    else {
        bg5->setPosition(Vec2(origin.x + visibleSize.width * 0.523,
            origin.y + visibleSize.height * 0.32));
        statistics_layer->addChild(bg5);
    } 
    auto bg6 = Sprite::create("/OptionsScene/setting02-hd_42.PNG");
    if (bg6 == nullptr) {
        problemLoading("'setting02-hd_42.PNG'");
    }
    else {
        bg6->setPosition(Vec2(origin.x + visibleSize.width * 0.534,
            origin.y + visibleSize.height * 0.23));
        statistics_layer->addChild(bg6);
    } 
    auto bg7 = Sprite::create("/OptionsScene/setting02-hd_44.PNG");
    if (bg7 == nullptr) {
        problemLoading("'setting02-hd_44.PNG'");
    }
    else {
        bg7->setPosition(Vec2(origin.x + visibleSize.width * 0.523,
            origin.y + visibleSize.height * 0.14));
        statistics_layer->addChild(bg7);
    }
    //statistics_menu
    auto statistics_menu = Menu::create();
    statistics_menu->setPosition(Vec2::ZERO);

    //统计层下的set_title
    auto statistics_set_title = MenuItemImage::create("/OptionsScene/setting02-hd_45_normal.PNG",
        "/OptionsScene/setting02-hd_45_normal.PNG", CC_CALLBACK_1(OptionsScene::goto_set, this));
    statistics_set_title->setPosition(Vec2(origin.x + visibleSize.width * 0.3,
        origin.y + visibleSize.height * 0.93));
    statistics_set_title->setScale(1.4);
    statistics_menu->addChild(statistics_set_title);
    //统计层下的person_title
    auto statistics_person_title = MenuItemImage::create("/OptionsScene/setting02-hd_48_normal.PNG",
        "/OptionsScene/setting02-hd_48_normal.PNG", CC_CALLBACK_1(OptionsScene::goto_person, this));
    statistics_person_title->setPosition(Vec2(origin.x + visibleSize.width * 0.7,
        origin.y + visibleSize.height * 0.925));
    statistics_person_title->setScale(1.4);
    statistics_menu->addChild(statistics_person_title);

    statistics_layer->addChild(statistics_menu);
    statistics_layer->setVisible(false);
    this->addChild(statistics_layer);

    /*******************************************************开发人员界面**********************************************************/
    auto person_layer = Layer::create();
    person_layer->setName("PersonLayer");
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

        person_layer->addChild(person);
    }

    //人员层下的person_title
    auto  person_person_title = Sprite::create("/OptionsScene/setting02-hd_48.PNG");
    if (person_person_title == nullptr) {
        problemLoading("'setting02-hd_48.PNG'");
    }
    else {
        person_person_title->setPosition(Vec2(origin.x + visibleSize.width * 0.7,
            origin.y + visibleSize.height * 0.925));
        person_layer->addChild(person_person_title);
    }
    //person_menu
    auto person_menu = Menu::create();
    person_menu->setPosition(Vec2::ZERO);

    //人员层下的set_title
    auto person_set_title = MenuItemImage::create("/OptionsScene/setting02-hd_45_normal.PNG",
        "/OptionsScene/setting02-hd_45_normal.PNG", CC_CALLBACK_1(OptionsScene::goto_set, this));
    person_set_title->setPosition(Vec2(origin.x + visibleSize.width * 0.3,
        origin.y + visibleSize.height * 0.93));
    person_set_title->setScale(1.4);
    person_menu->addChild(person_set_title);
    //人员层下的statistics_title
    auto person_statistics_title = MenuItemImage::create("/OptionsScene/setting02-hd_43_normal.PNG",
        "/OptionsScene/setting02-hd_43_normal.PNG", CC_CALLBACK_1(OptionsScene::goto_statistics, this));
    person_statistics_title->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height * 0.935));
    person_statistics_title->setScale(1.4);
    person_menu->addChild(person_statistics_title);

    person_layer->addChild(person_menu);
    person_layer->setVisible(false);
    this->addChild(person_layer);

    /**************************************************************返回主菜单*****************************************************************************/
    auto menu_all = Menu::create();
    menu_all->setPosition(Vec2::ZERO);
    auto home = MenuItemImage::create("/OptionsScene/Btn_Return.PNG", "/OptionsScene/Btn_ReturnLight.PNG", CC_CALLBACK_1(OptionsScene::goto_menu, this));
    home->setPosition(Vec2(origin.x + visibleSize.width * 0.1,
        origin.y + visibleSize.height * 0.9));

    menu_all->addChild(home);
    this->addChild(menu_all);
    return true;
}

void OptionsScene::goto_menu(Ref* psender)
{
    auto menu_scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInB::create(0.3, menu_scene));

}

void OptionsScene::goto_set(Ref* psender)//设置仅选项层可见
{
    Node* set = this->getChildByName("SetLayer");
    Node* statistics = this->getChildByName("StatisticsLayer");
    Node* person = this->getChildByName("PersonLayer");

    set->setVisible(true);
    statistics->setVisible(false);
    person->setVisible(false);
}

void OptionsScene::goto_statistics(Ref* psender)//设置仅统计层可见
{
    Node* set = this->getChildByName("SetLayer");
    Node* statistics = this->getChildByName("StatisticsLayer");
    Node* person = this->getChildByName("PersonLayer");

    set->setVisible(false);
    statistics->setVisible(true);
    person->setVisible(false);
}

void OptionsScene::goto_person(Ref* psender)//设置仅人员层可见
{
    Node* set = this->getChildByName("SetLayer");
    Node* statistics = this->getChildByName("StatisticsLayer");
    Node* person = this->getChildByName("PersonLayer");

    set->setVisible(false);
    statistics->setVisible(false);
    person->setVisible(true);
}

void OptionsScene::close_sound(Ref* psender)
{
    //待实现
}

void OptionsScene::close_bgmusic(Ref* psender)
{
    //待实现
}

void OptionsScene::reset_game(Ref* psender)
{
    //待实现
}