#include "MenuScene.h"

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
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
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

    /*背景图*/
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
    /*云*/
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
        cloud1->setTag(1);
        cloud->addChild(cloud1);
    }
    ////大云运动
    //小云
    auto cloud2 = Sprite::create("/MenuScene/Cloud.PNG");
    if (cloud2 == nullptr)
    {
        problemLoading("'Cloud.PNG'");
    }
    else
    {
        cloud2->setScale(0.5);
        cloud2->setPosition(Vec2(origin.x + visibleSize.width + cloud2->getContentSize().width,
            origin.y + visibleSize.height * 0.8));
        cloud2->setTag(2);
        cloud->addChild(cloud2);
    }

    this->addChild(cloud);
    /*添加怪物图形*/
    auto monster = Sprite::create("/MenuScene/FlyMonster.PNG");
    if (monster == nullptr) {
        problemLoading("'FlyMonster.PNG'");
    }
    else {
        monster->setPosition(Vec2(origin.x + visibleSize.width / 4,
            origin.y + visibleSize.height * 0.8));
        monster->setName("Monster");
        this->addChild(monster);
    }
    /*添加萝卜图形*/
    auto carrot = Sprite::create();
    //1,添加萝卜叶子
    auto carrot_leaf1 = Sprite::create("/MenuScene/Leaf1.PNG");
    if (carrot_leaf1 == nullptr)
    {
        problemLoading("'Leaf1.PNG'");
    }
    else
    {
        carrot_leaf1->setPosition(Vec2(origin.x + visibleSize.width / 2 - carrot_leaf1->getContentSize().width / 2,
            origin.y + visibleSize.height / 2 + carrot_leaf1->getContentSize().height * 1.2));
        carrot->addChild(carrot_leaf1);
    }

    auto carrot_leaf2 = Sprite::create("/MenuScene/Leaf2.PNG");
    if (carrot_leaf2 == nullptr)
    {
        problemLoading("'Leaf2.PNG'");
    }
    else
    {
        carrot_leaf2->setPosition(Vec2(origin.x + visibleSize.width / 2 + carrot_leaf2->getContentSize().width / 2,
            origin.y + visibleSize.height / 2 + carrot_leaf2->getContentSize().height * 1.3));

        carrot->addChild(carrot_leaf2);
    }

    auto carrot_leaf3 = Sprite::create("/MenuScene/Leaf3.PNG");
    if (carrot_leaf3 == nullptr)
    {
        problemLoading("'Leaf3.PNG'");
    }
    else
    {
        carrot_leaf3->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2 + carrot_leaf3->getContentSize().height * 1.1));

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
        carrot_body->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2 + carrot_body->getContentSize().height / 4));

        carrot->addChild(carrot_body);
    }

    this->addChild(carrot);
    /*添加保卫萝卜标题*/
    auto title = Sprite::create("/MenuScene/MainTitle.PNG");
    if (title == nullptr) {
        problemLoading("'MainTitle.PNG'");
    }
    else {
        title->setPosition(Vec2(origin.x + visibleSize.width / 2 + title->getContentSize().width / 20,
            origin.y + visibleSize.height / 2 - title->getContentSize().height / 7));
        this->addChild(title);
    }

    /*开启调度器*/
    this->scheduleUpdate();


    return true;
}

void MenuScene::update(float dt) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /*动物的上下运动*/
    Node* Monster = this->getChildByName("Monster");
    static bool direction = 1;//向下运动
    static float dx = 0;
    if (direction == 1) {
        Monster->setPosition(Vec2(Monster->getPosition().x, Monster->getPosition().y - 50 * dt));
        dx += 50 * dt;
        if (dx >= Monster->getContentSize().height / 2) {
            direction = 0;
            dx = 0;
        }
    }
    else {
        Monster->setPosition(Vec2(Monster->getPosition().x, Monster->getPosition().y + 50 * dt));
        dx += 50 * dt;
        if (dx >= Monster->getContentSize().height / 2) {
            direction = 1;
            dx = 0;
        }
    }

    /*云的运动*/
    Node* Cloud = this->getChildByName("Cloud");
    Node* Cloud1 = Cloud->getChildByTag(1);
    Node* Cloud2 = Cloud->getChildByTag(2);

    Cloud1->setPosition(Vec2(Cloud1->getPosition().x + 30 * dt, Cloud1->getPosition().y));
    Cloud2->setPosition(Vec2(Cloud2->getPosition().x - 50 * dt, Cloud2->getPosition().y));
    if (Cloud1->getPosition().x >= visibleSize.width + Cloud1->getContentSize().width&& Cloud2->getPosition().x <= 0 - Cloud2->getContentSize().width) {
        Cloud1->setPosition(Vec2(0 - Cloud1->getContentSize().width, Cloud1->getPosition().y));
        Cloud2->setPosition(Vec2(visibleSize.width + Cloud2->getContentSize().width, Cloud2->getPosition().y));
    }
}

