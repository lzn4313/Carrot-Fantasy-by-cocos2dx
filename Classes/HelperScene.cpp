#include "MenuScene.h"
#include "HelperScene.h"
#include "MenuScene.h"
#include "ui/CocosGUI.h"
#include"sound&music.h"
USING_NS_CC;
using namespace cocos2d::ui;
/*错误处理*/
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
}
/*工具函数*/
//为了根据滑动层的坐标判断当前在第几页，以及控制滑动翻页是否进行，调用该函数会返回：比松手时界面位置小的最大页数
static int find(float page[], int N, float x) {
	for (int i = 0; i < N; i++) {
		if (x >= page[i]) {
			return i - 1;
		}
	}
	return N - 1;
}
/*****************************  HelperScene类  ***********************************************************/
cocos2d::Scene* HelperScene::createScene()
{
	return HelperScene::create();
}
//初始化
bool HelperScene::init()
{
	if (!Scene::init()) {
		return false;
	}
	//获取屏幕位置
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/************************************************  背景创建  *******************************************************/
	auto background_image = Sprite::create("/HelperScene/help_3-hd_bg.png");
	if (background_image == nullptr) {
		problemLoading("help_3-hd_bg.png");
	}
	background_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(background_image,0);
	/********************************  help_layer  *******************************/
	auto help_layer = HelpLayer::createLayer();
	help_layer->setName("HelpLayer");
	this->addChild(help_layer,0);
	/**************************************************  菜单  *****************************************************/
	auto menu_all = Menu::create();
	menu_all->setPosition(Vec2::ZERO);
	//返回主菜单的按钮（以MenuItemImage形式实现）
	auto home = MenuItemImage::create("/HelperScene/help_1-hd_67.PNG", "/HelperScene/help_1-hd_38.PNG", CC_CALLBACK_1(HelperScene::goto_home, this));
	home->setPosition(Vec2(origin.x + visibleSize.width * 0.1,
		origin.y + visibleSize.height * 0.92));
	menu_all->addChild(home);
	this->addChild(menu_all,10);
	/***********************************************选项卡****************************************************/
	//help按钮
	auto help_btn = ui::Button::create("/HelperScene/help_1-hd-33_normal.PNG", "/HelperScene/help_1-hd-33_normal.PNG", "/HelperScene/help_1-hd_33.PNG");
	if (help_btn == nullptr) {
		problemLoading("help_1-hd-33_normal.PNG||help_1-hd-33.PNG");
	}
	help_btn->setName("HelpBtn");
	help_btn->setPosition(Vec2(origin.x + visibleSize.width*0.31,
		origin.y + visibleSize.height*0.925));
	help_btn->addTouchEventListener(CC_CALLBACK_2(HelperScene::goto_help, this));
	help_btn->setEnabled(false);
	this->addChild(help_btn,10);
	//monster按钮
	auto monster_btn = ui::Button::create("/HelperScene/help_1-hd_71_normal.PNG", "/HelperScene/help_1-hd_71_normal.PNG", "/HelperScene/help_1-hd_71.png");
	if (monster_btn == nullptr) {
		problemLoading("help_1-hd-71_normal.PNG||help_1-hd-71.PNG");
	}
	monster_btn->setName("MonsterBtn");
	monster_btn->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height*0.922));
	monster_btn->setScale(1.4);
	monster_btn->addTouchEventListener(CC_CALLBACK_2(HelperScene::goto_monster, this));
	this->addChild(monster_btn,10);
	//tower按钮
	auto tower_btn = ui::Button::create("/HelperScene/help_1-hd_66_normal.PNG", "/HelperScene/help_1-hd_66_normal.PNG", "/HelperScene/help_1-hd_66.PNG");
	if (tower_btn == nullptr) {
		problemLoading("help_1-hd-66_normal.PNG||help_1-hd-66.PNG");
	}
	tower_btn->setName("TowerBtn");
	tower_btn->setPosition(Vec2(origin.x + visibleSize.width*0.69,
		origin.y + visibleSize.height*0.923));
	tower_btn->setScale(1.4);
	tower_btn->addTouchEventListener(CC_CALLBACK_2(HelperScene::goto_tower, this));
	this->addChild(tower_btn,10);

	return true;
}
//返回主菜单
void HelperScene::goto_home(Ref* psender)
{
	button_sound_effect();//播放音效
	Scene* menu_scene = MenuScene::createScene();//创建菜单场景
	Director::getInstance()->replaceScene(TransitionSlideInT::create(0.3, menu_scene));//以从上向下滑动方式切换
}
//去帮助选项页
void HelperScene::goto_help(Ref* psender, Widget::TouchEventType type)
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
			//将切换前对应的Layer移除
			if (this->getChildByName("MonsterLayer") != nullptr) {
				this->removeChildByName("MonsterLayer");
			}
			if (this->getChildByName("TowerLayer") != nullptr) {
				this->removeChildByName("TowerLayer");
			}
			//创建帮助选项卡并渲染
			auto help_layer = HelpLayer::createLayer();
			help_layer->setName("HelpLayer");
			this->addChild(help_layer, 0);

			//设置帮助按钮不可用
			Node* help_btn = this->getChildByName("HelpBtn");
			help_btn->setScale(1);
			static_cast<ui::Button*>(help_btn)->setEnabled(false);
			//设置monster按钮可用
			Node* monster_btn = this->getChildByName("MonsterBtn");
			monster_btn->setScale(1.4);
			static_cast<ui::Button*>(monster_btn)->setEnabled(true);
			//设置tower按钮可用
			Node* tower_btn = this->getChildByName("TowerBtn");
			tower_btn->setScale(1.4);
			static_cast<ui::Button*>(tower_btn)->setEnabled(true);

			break;
	}
}
//去monster选项页
void HelperScene::goto_monster(Ref* psender, Widget::TouchEventType type)
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

			//将切换前的Layer移除
			if (this->getChildByName("HelpLayer") != nullptr) {
				this->removeChildByName("HelpLayer");
			}
			if (this->getChildByName("TowerLayer") != nullptr) {
				this->removeChildByName("TowerLayer");
			}
			//创建monster选项卡并渲染
			auto monster_layer = MonsterLayer::createLayer();
			monster_layer->setName("MonsterLayer");
			this->addChild(monster_layer, 0);

			//设置help按钮可用
			Node* help_btn = this->getChildByName("HelpBtn");
			help_btn->setScale(1.4);
			static_cast<ui::Button*>(help_btn)->setEnabled(true);
			//设置monster按钮不可用
			Node* monster_btn = this->getChildByName("MonsterBtn");
			monster_btn->setScale(1);
			static_cast<ui::Button*>(monster_btn)->setEnabled(false);
			//设置tower按钮可用
			Node* tower_btn = this->getChildByName("TowerBtn");
			tower_btn->setScale(1.4);
			static_cast<ui::Button*>(tower_btn)->setEnabled(true);

			break;
	}
}
//去tower选项页
void HelperScene::goto_tower(Ref* psender, Widget::TouchEventType type)
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

			//将切换前的选项页移除
			if (this->getChildByName("HelpLayer") != nullptr) {
				this->removeChildByName("HelpLayer");
			}
			if (this->getChildByName("MonsterLayer") != nullptr) {
				this->removeChildByName("MonsterLayer");
			}
			//创建tower选项页并渲染
			auto tower_layer = TowerLayer::createLayer();
			tower_layer->setName("TowerLayer");
			this->addChild(tower_layer, 0);

			//设置help按钮为可用
			Node* help_btn = this->getChildByName("HelpBtn");
			help_btn->setScale(1.4);
			static_cast<ui::Button*>(help_btn)->setEnabled(true);
			//设置monster按钮为可用
			Node* monster_btn = this->getChildByName("MonsterBtn");
			monster_btn->setScale(1.4);
			static_cast<ui::Button*>(monster_btn)->setEnabled(true);
			//设置tower按钮为不可用
			Node* tower_btn = this->getChildByName("TowerBtn");
			tower_btn->setScale(1);
			static_cast<ui::Button*>(tower_btn)->setEnabled(false);

			break;
	}
}
/*************************************** HelpLayer类  ******************************************/
cocos2d::Layer* HelpLayer::createLayer()
{
	return HelpLayer::create();
}
//初始化
bool HelpLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	//获取屏幕大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/**************************  滑动层  ********************************/
	//实现原理，将对应的几页内容全部按顺序横向渲染，通过移动当前层的位置来实现翻页效果
	auto toplayer = Layer::create();
	toplayer->setName("toplayer");
	/**************************  第一页  ******************************/
	auto help_1_image = Sprite::create("/HelperScene/help_3-hd_1.png");
	help_1_image->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height *0.55));
	toplayer->addChild(help_1_image);
	auto help_1_txt = Sprite::create("/HelperScene/help_1-hd_73.PNG");
	help_1_txt->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.22));
	toplayer->addChild(help_1_txt);
	/**************************  第二页  ******************************/
	auto help_2_image = Sprite::create("/HelperScene/help_3-hd_2.png");
	help_2_image->setPosition(Vec2(origin.x + visibleSize.width * 1.5, origin.y + visibleSize.height *0.55));
	toplayer->addChild(help_2_image);
	auto help_2_txt = Sprite::create("/HelperScene/help_1-hd_4.PNG");
	help_2_txt->setPosition(Vec2(origin.x + visibleSize.width *1.5, origin.y + visibleSize.height *0.22));
	toplayer->addChild(help_2_txt);
	/**************************  第三页  ******************************/
	auto help_3_image = Sprite::create("/HelperScene/help_3-hd_3.png");
	help_3_image->setPosition(Vec2(origin.x + visibleSize.width * 2.5, origin.y + visibleSize.height *0.55));
	toplayer->addChild(help_3_image);
	auto help_3_txt = Sprite::create("/HelperScene/help_1-hd_50.PNG");
	help_3_txt->setPosition(Vec2(origin.x + visibleSize.width * 2.5, origin.y + visibleSize.height *0.22));
	toplayer->addChild(help_3_txt);
	/**************************  第四页  ******************************/
	auto help_4_image = Sprite::create("/HelperScene/help_3-hd_4.png");
	help_4_image->setPosition(Vec2(origin.x + visibleSize.width * 3.5, origin.y + visibleSize.height *0.55));
	toplayer->addChild(help_4_image);
	auto help_4_txt = Sprite::create("/HelperScene/help_1-hd_65.PNG");
	help_4_txt->setPosition(Vec2(origin.x + visibleSize.width * 3.5, origin.y + visibleSize.height *0.22));
	toplayer->addChild(help_4_txt);
	this->addChild(toplayer);

	/***************************  页码  ******************************/
	auto page_num_image = Sprite::create("/HelperScene/help_1-hd_0.PNG");
	page_num_image->setPosition(Vec2(origin.x + visibleSize.width *0.51, origin.y + visibleSize.height * 0.06));
	this->addChild(page_num_image);
	auto num_divide = Sprite::create("/HelperScene/num_-1.png");
	num_divide->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.062));
	this->addChild(num_divide);
	num_divide->setScale(1.4);
	auto num_4 = Sprite::create("/HelperScene/num_4.png");
	num_4->setPosition(Vec2(origin.x + visibleSize.width / 2 + num_4->getContentSize().width * 2, origin.y + visibleSize.height * 0.062));
	this->addChild(num_4);
	num_4->setScale(1.4);
	auto page_num = Sprite::create("/HelperScene/num_1.png");
	page_num->setName("page_num1");
	page_num->setScale(1.4);
	page_num->setPosition(Vec2(origin.x + visibleSize.width / 2 - page_num->getContentSize().width * 3, origin.y + visibleSize.height * 0.062));
	this->addChild(page_num);
	/****************************  滑动实现  *****************************/
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
	};
	listener->onTouchMoved = [toplayer](Touch* touch, Event* event) {//实现屏幕跟着滑动的效果
		float distance = touch->getLocation().x - touch->getPreviousLocation().x;
		toplayer->setPositionX(toplayer->getPositionX() + distance);
	};
	listener->onTouchEnded = [this,toplayer,visibleSize](Touch* touch, Event* event) {
		float distance = touch->getLocation().x - touch->getStartLocation().x;//获取本次触摸移动的横向距离
		float page[4] = { 0,-visibleSize.width,-2 * visibleSize.width,-3 * visibleSize.width };//记录每一页对应的坐标
		if (distance > visibleSize.width / 6) {//如果滑动距离大于六分之一屏幕（向右滑），则选择切换到左一页
			if (toplayer->getPosition().x > 0) {//如果已经是最左页，则不滑动，利用动画返回最左页
				toplayer->runAction(MoveTo::create(0.1, Vec2(page[0], 0)));
			}
			else {//若不是最左页，进行左翻页操作
				page_sound_effect();//播放翻页音效
				if (toplayer->getPosition().x < 0 && toplayer->getPosition().x >page[1]) {//如果当前是第1页，则到第0页
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[0], 0)));
					Node* num =this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_1.png");
				}
				else if (toplayer->getPosition().x < page[1] && toplayer->getPosition().x >page[2]) {//若当前是第2页，则翻到第1页
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[1], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_2.png");
				}
				else if (toplayer->getPosition().x < page[2] && toplayer->getPosition().x >page[3]) {//若当前是第3页，则翻到第2页
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[2], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_3.png");
				}
			}
		}
		else if (distance < -visibleSize.width / 6) {//若滑动距离小于-六分之一个屏幕（左滑），则选择切换到右一页
			if (toplayer->getPosition().x < page[3]) {//若已经是最右页，则取消滑动，利用动画回到最右页
				toplayer->runAction(MoveTo::create(0.1, Vec2(page[3], 0)));
			}
			else {//若不是最右页，则利用动画切换到右一页
				page_sound_effect();//播放音效
				if (toplayer->getPosition().x < 0 && toplayer->getPosition().x >page[1]) {//若当前是第0页，切换到第1页
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[1], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_2.png");
				}
				else if (toplayer->getPosition().x < page[1] && toplayer->getPosition().x >page[2]) {//若当前是第1页，切换到第2页
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[2], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_3.png");
				}
				else if (toplayer->getPosition().x < page[2] && toplayer->getPosition().x >page[3]) {//若当前是第2页，切换到第3页
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[3], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_4.png");
				}
			}
		}
		else {//若滑动距离小于六分之一屏幕，则视本次滑动为取消滑动，利用动画回到滑动之前的页码
			if (distance > 0) {
				if (toplayer->getPosition().x > 0 && toplayer->getPosition().x > page[1]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[0], 0)));
				}
				else if (toplayer->getPosition().x < 0 && toplayer->getPosition().x >page[1]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[1], 0)));
				}
				else if (toplayer->getPosition().x < page[1] && toplayer->getPosition().x >page[2]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[2], 0)));
				}
				else if (toplayer->getPosition().x < page[2] && toplayer->getPosition().x >page[3]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[3], 0)));
				}
			}
			else if(distance<0) {
				if (toplayer->getPosition().x < 0 && toplayer->getPosition().x >page[1]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[0], 0)));
				}
				else if (toplayer->getPosition().x < page[1] && toplayer->getPosition().x >page[2]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[1], 0)));
				}
				else if (toplayer->getPosition().x < page[2] && toplayer->getPosition().x >page[3]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[2], 0)));
				}
				else if (toplayer->getPosition().x < page[3]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[3], 0)));
				}
			}
		}
	};
	//添加触摸监听器到事件分发器内
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}
/**************************************  MonsterLayer类  ************************************/
cocos2d::Layer* MonsterLayer::createLayer()
{
	return MonsterLayer::create();
}
//初始化
bool MonsterLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	//获取屏幕大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景
	auto bg_image = Sprite::create("/HelperScene/help_3-hd_monster.png");
	if (bg_image == nullptr) {
		problemLoading("help_3-hd_monster.png");
	}
	bg_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height*0.45));
	this->addChild(bg_image);

	//文字
	auto little_monster_txt = Sprite::create("/HelperScene/help_1-hd_14.PNG");
	if (little_monster_txt == nullptr) {
		problemLoading("help_1-hd_14.PNG");
	}
	little_monster_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.2,
		origin.y + visibleSize.height *0.45));
	this->addChild(little_monster_txt);

	auto fly_monster_txt = Sprite::create("/HelperScene/help_1-hd_1.PNG");
	if (fly_monster_txt == nullptr) {
		problemLoading("help_1-hd_1.PNG");
	}
	fly_monster_txt->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height *0.45));
	this->addChild(fly_monster_txt);

	auto boss_monster_txt = Sprite::create("/HelperScene/help_1-hd_2.PNG");
	if (boss_monster_txt == nullptr) {
		problemLoading("help_1-hd_2.PNG");
	}
	boss_monster_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.8,
		origin.y + visibleSize.height *0.45));
	this->addChild(boss_monster_txt);

	auto blood_1 = Sprite::create("/HelperScene/help_1-hd_3.PNG");
	if (blood_1 == nullptr) {
		problemLoading("help_1-hd_3.PNG");
	}
	blood_1->setPosition(Vec2(origin.x + visibleSize.width *0.336,
		origin.y + visibleSize.height * 0.285));
	this->addChild(blood_1);
	auto blood_2= Sprite::create("/HelperScene/help_1-hd_3.PNG");
	if (blood_2 == nullptr) {
		problemLoading("help_1-hd_3.PNG");
	}
	blood_2->setPosition(Vec2(origin.x + visibleSize.width *0.645,
		origin.y + visibleSize.height * 0.285));
	this->addChild(blood_2);

	auto speed_1= Sprite::create("/HelperScene/help_1-hd_29.PNG");
	if (speed_1 == nullptr) {
		problemLoading("help_1-hd_29.PNG");
	}
	speed_1->setPosition(Vec2(origin.x + visibleSize.width *0.336,
		origin.y + visibleSize.height * 0.355));
	this->addChild(speed_1);
	auto speed_2 = Sprite::create("/HelperScene/help_1-hd_29.PNG");
	if (speed_2 == nullptr) {
		problemLoading("help_1-hd_29.PNG");
	}
	speed_2->setPosition(Vec2(origin.x + visibleSize.width *0.645,
		origin.y + visibleSize.height * 0.355));
	this->addChild(speed_2);

	auto txt = Sprite::create("/HelperScene/help_1-hd_39.PNG");
	if (txt == nullptr) {
		problemLoading("help_1-hd_39.PNG");
	}
	txt->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height * 0.2)); 
	this->addChild(txt);

	return true;
}
/*************************************  TowerLayer类  ***********************************/
cocos2d::Layer* TowerLayer::createLayer()
{
	return TowerLayer::create();
}
//初始化
bool TowerLayer::init()
{
	if (!Layer::create()) {
		return false;
	}
	//获取屏幕大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/**************************  滑动层  ********************************/
	//实现原理，将对应的几页内容全部按顺序横向渲染，通过移动当前层的位置来实现翻页效果
	auto toplayer = Layer::create();
	toplayer->setName("toplayer2");
	/**************************  第1页  ******************************/
	auto tower_1 = Sprite::create("/HelperScene/tower_1.png");
	tower_1->setPosition(Vec2(origin.x + visibleSize.width / 2, 
		origin.y + visibleSize.height * 0.5));
	toplayer->addChild(tower_1);
	/**************************  第2页  ******************************/
	auto tower_2 = Sprite::create("/HelperScene/tower_2.png");
	tower_2->setPosition(Vec2(origin.x + visibleSize.width * 1.5, 
		origin.y + visibleSize.height * 0.5));
	toplayer->addChild(tower_2);	
	/**************************  第3页  ******************************/
	auto tower_3 = Sprite::create("/HelperScene/tower_3.png");
	tower_3->setPosition(Vec2(origin.x + visibleSize.width * 2.5, 
		origin.y + visibleSize.height * 0.5));
	toplayer->addChild(tower_3);	
	/**************************  第4页  ******************************/
	auto tower_4 = Sprite::create("/HelperScene/tower_4.png");
	tower_4->setPosition(Vec2(origin.x + visibleSize.width * 3.5, 
		origin.y + visibleSize.height * 0.5));
	toplayer->addChild(tower_4);	
	/**************************  第5页  ******************************/
	auto tower_5 = Sprite::create("/HelperScene/tower_5.png");
	tower_5->setPosition(Vec2(origin.x + visibleSize.width * 4.5, 
		origin.y + visibleSize.height * 0.5));
	toplayer->addChild(tower_5);	
	/**************************  第6页  ******************************/
	auto tower_6 = Sprite::create("/HelperScene/tower_6.png");
	tower_6->setPosition(Vec2(origin.x + visibleSize.width * 5.5,
		origin.y + visibleSize.height * 0.5));
	toplayer->addChild(tower_6);	
	/**************************  第7页  ******************************/
	auto tower_7 = Sprite::create("/HelperScene/tower_7.png");
	tower_7->setPosition(Vec2(origin.x + visibleSize.width * 6.5, 
		origin.y + visibleSize.height * 0.5));
	toplayer->addChild(tower_7);	
	/**************************  第8页  ******************************/
	auto tower_8 = Sprite::create("/HelperScene/tower_8.png");
	tower_8->setPosition(Vec2(origin.x + visibleSize.width * 7.5, 
		origin.y + visibleSize.height * 0.5));
	toplayer->addChild(tower_8);	
	/**************************  第9页  ******************************/
	auto tower_9 = Sprite::create("/HelperScene/tower_9.png");
	tower_9->setPosition(Vec2(origin.x + visibleSize.width * 8.5, 
		origin.y + visibleSize.height * 0.5));
	toplayer->addChild(tower_9);	
	/**************************  第10页  ******************************/
	auto tower_10 = Sprite::create("/HelperScene/tower_10.png");
	tower_10->setPosition(Vec2(origin.x + visibleSize.width * 9.5,
		origin.y + visibleSize.height * 0.5));
	toplayer->addChild(tower_10);
	this->addChild(toplayer);
	/***************************  页码  ******************************/
	auto page_num_image = Sprite::create("/HelperScene/help_1-hd_0.PNG");
	page_num_image->setPosition(Vec2(origin.x + visibleSize.width * 0.51, origin.y + visibleSize.height * 0.06));
	this->addChild(page_num_image);
	auto num_divide = Sprite::create("/HelperScene/num_-1.png");
	num_divide->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.062));
	this->addChild(num_divide);
	num_divide->setScale(1.4);
	auto num_10 = Sprite::create("/HelperScene/num_10.png");
	num_10->setPosition(Vec2(origin.x + visibleSize.width / 2 + num_10->getContentSize().width, 
		origin.y + visibleSize.height * 0.062));
	this->addChild(num_10);
	num_10->setScale(1.4);
	auto page_num = Sprite::create("/HelperScene/num_1.png");
	page_num->setName("page_num2");
	page_num->setScale(1.4);
	page_num->setPosition(Vec2(origin.x + visibleSize.width / 2 - page_num->getContentSize().width * 3,
		origin.y + visibleSize.height * 0.062));
	this->addChild(page_num);
	/****************************  滑动实现  *****************************/
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
	};
	listener->onTouchMoved = [toplayer](Touch* touch, Event* event) {//实现屏幕随触摸移动
		float distance = touch->getLocation().x - touch->getPreviousLocation().x;
		toplayer->setPositionX(toplayer->getPositionX() + distance);
	};
	listener->onTouchEnded = [this, toplayer, visibleSize](Touch* touch, Event* event) {
		float distance = touch->getLocation().x - touch->getStartLocation().x;//获取本次触摸移动的水平距离
		//记录每一页对应页码
		float page[10] = { 0,-visibleSize.width,-2 * visibleSize.width,-3 * visibleSize.width,-4 * visibleSize.width,
			-5 * visibleSize.width,-6 * visibleSize.width,-7 * visibleSize.width,-8 * visibleSize.width,-9 * visibleSize.width };
		int n = find(page, 10, toplayer->getPosition().x);
		if (distance > visibleSize.width / 6) {//若滑动超过六分之一屏幕，视本次滑动为有效，向左一页
			if (toplayer->getPosition().x > 0) {
				toplayer->runAction(MoveTo::create(0.1, Vec2(page[0], 0)));
			}
			else {
				toplayer->runAction(MoveTo::create(0.1, Vec2(page[n], 0)));
				page_sound_effect();
				Node* num = this->getChildByName("page_num2");
				switch (n) {
					case 0:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_1.png");
						break;
					case 1:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_2.png");
						break;
					case 2:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_3.png");
						break;
					case 3:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_4.png");
						break;
					case 4:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_5.png");
						break;
					case 5:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_6.png");
						break;
					case 6:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_7.png");
						break;
					case 7:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_8.png");
						break;
					case 8:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_9.png");
						break;
					default:
						break;
				}
			}
		}
		else if (distance < -visibleSize.width / 6) {//视本次滑动有效，向右翻一页
			if (toplayer->getPosition().x < page[9]) {
				toplayer->runAction(MoveTo::create(0.1, Vec2(page[9], 0)));
			}
			else {
				toplayer->runAction(MoveTo::create(0.1, Vec2(page[n + 1], 0)));
				page_sound_effect();
				Node* num = this->getChildByName("page_num2");
				switch (n) {
					case 0:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_2.png");
						break;
					case 1:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_3.png");
						break;
					case 2:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_4.png");
						break;
					case 3:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_5.png");
						break;
					case 4:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_6.png");
						break;
					case 5:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_7.png");
						break;
					case 6:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_8.png");
						break;
					case 7:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_9.png");
						break;
					case 8:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_10.png");
						break;
					default:
						break;
				}
			}
		}
		else {//若滑动小于六分之一屏幕，视本次滑动无效，返回滑动前的页码对应坐标
			if (distance > 0) {
				toplayer->runAction(MoveTo::create(0.1, Vec2(page[n + 1], 0)));
			}
			else if (distance < 0) {
				toplayer->runAction(MoveTo::create(0.1, Vec2(page[n], 0)));
			}
		}
	};
	//将事件监听器添加到事件分发器内
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}
