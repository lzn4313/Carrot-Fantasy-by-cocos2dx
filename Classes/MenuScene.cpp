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
    //大云
    auto cloud1 = Sprite::create("/MenuScene/Cloud.PNG");
    if (cloud1 == nullptr)
    {
        problemLoading("'Cloud.PNG'");
    }
    else
    {
        cloud1->setPosition(Vec2(origin.x + visibleSize.width / 4,
            origin.y + visibleSize.height * 0.85));
        Color3B c = cloud1->getColor();
        c.r *= -0.7;
        c.g *= -0.7;
        c.b *= -0.7;
        cloud1->setColor(c);
        cloud->addChild(cloud1);
    }
    //小云
    auto cloud2 = Sprite::create("/MenuScene/Cloud.PNG");
    if (cloud2 == nullptr)
    {
        problemLoading("'Cloud.PNG'");
    }
    else
    {
        cloud2->setScale(0.5);
        cloud2->setPosition(Vec2(origin.x + visibleSize.width * 0.85,
            origin.y + visibleSize.height * 0.8));
        cloud->addChild(cloud2);
    }

    this->addChild(cloud);
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
    return true;
}

