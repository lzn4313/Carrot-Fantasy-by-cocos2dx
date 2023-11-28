#include "MenuScene.h"
#include "HelperScene.h"
#include "MenuScene.h"

USING_NS_CC;

cocos2d::Scene* HelperScene::createScene()
{
	return HelperScene::create();
}

/*错误处理*/
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
}

bool HelperScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/******************************************************************背景创建*******************************************************/
	auto background_image = Sprite::create("/HelperScene/help_3-hd_bg.png");
	background_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));

	this->addChild(background_image);

	/**********************************************monster_layer实现*******************************************************************/
	auto monster_layer = Layer::create();


	/***************************************************************菜单***************************************************************/
	auto menu_all = Menu::create();
	menu_all->setPosition(Vec2::ZERO);

	auto home = MenuItemImage::create("/HelperScene/help_1-hd_67.PNG", "/HelperScene/help_1-hd_67.PNG", CC_CALLBACK_1(HelperScene::goto_home, this));
	home->setPosition(Vec2(origin.x + visibleSize.width * 0.1,
		origin.y + visibleSize.height * 0.9));
	menu_all->addChild(home);
	this->addChild(menu_all);
	return true;
}

void HelperScene::goto_home(Ref* psender)
{
	Scene* menu_scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionSlideInT::create(0.3, menu_scene));
}


