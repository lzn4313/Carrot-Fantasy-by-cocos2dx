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
/*******************************  ������  ************************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}
/*******************************  ���ߺ���  **************************************/
//ͬHelperScene.cpp�е��÷�
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
/*��ʼ��*/
bool GameSelectionScene::init()
{
    /*��ʼ������*/
    if (!Scene::init())
    {
        return false;
    }
    //��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /**************************  ����  *******************************/
    auto background_image = Sprite::create("/GameSelectionScene/stages_bg-hd_0.PNG");
    background_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(background_image);
    /**************************  ����  ******************************/
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    //ȥ��������
    auto help_btn = MenuItemImage::create("/GameSelectionScene/stages_bg-hd_42.PNG", "/GameSelectionScene/stages_bg-hd_33.PNG");
    help_btn->setCallback([](Ref* psender) {//��ť�ص�����
        button_sound_effect();//������Ч
        auto helper_scene = HelperScene::createScene();//������������
        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.2, helper_scene));//����ʧ��ʽ�л�
        });
    help_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.8,
        origin.y + visibleSize.height * 0.95));
    menu->addChild(help_btn);

    this->addChild(menu);
    /*************************  biglevel  ****************************/
    auto biglevel = BigLevelLayer::createLayer();//����ѡ��ص�Layer
    this->addChild(biglevel);//�����Ⱦ


    return true;
}
/*******************************  BigLevelLayer  ******************************/
cocos2d::Layer* BigLevelLayer::createLayer()
{
	return BigLevelLayer::create();
}
//��ʼ��
bool BigLevelLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
    //��ȡ��Ļ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /*****************************************  ҳ��  ***********************************/
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
    /***************************  ������  *********************************/
    create_slide_layer();//����������
    /***************************  �˵���  *********************************/
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0);
    //�������˵�
    auto home_btn = MenuItemImage::create("/GameSelectionScene/themescene1-hd_8.PNG", "/GameSelectionScene/themescene1-hd_17.PNG");
    home_btn->setCallback([this](Ref* psender) {//�ص�����
        button_sound_effect();//������Ч
        auto menu_scene = MenuScene::createScene();//�������˵���ӦScene
        Director::getInstance()->replaceScene(TransitionFlipAngular::create(0.2, menu_scene));//�ԶԽǷ�ת��ʽ�л�
        });
    home_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.2,
        origin.y + visibleSize.height * 0.95));
    menu->addChild(home_btn);
    //����ҳ��ť
    auto left_btn = MenuItemImage::create("/GameSelectionScene/themescene1-hd_32.PNG", "/GameSelectionScene/themescene1-hd_31.PNG",
        CC_CALLBACK_1(BigLevelLayer::page_left, this));
    left_btn->setPosition(Vec2(origin.x + visibleSize.width *0.1,
        origin.y + visibleSize.height / 2));
    menu->addChild(left_btn);
    //���ҷ�ҳ��ť
    auto right_btn = MenuItemImage::create("/GameSelectionScene/themescene1-hd_26.PNG", "/GameSelectionScene/themescene1-hd_25.PNG",
        CC_CALLBACK_1(BigLevelLayer::page_right, this));
    right_btn->setPosition(Vec2(origin.x + visibleSize.width *0.9,
        origin.y + visibleSize.height / 2));
    menu->addChild(right_btn);

    return true;
}
//����������
void BigLevelLayer::create_slide_layer()
{
    auto slide_layer = Layer::create();
    slide_layer->setName("SlideLayer");
    this->addChild(slide_layer,1);
    //��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /*******************************  ������  ************************************/
    //evaluate
    auto evaluate = Sprite::create("/GameSelectionScene/themescene1-hd.png");
    evaluate->setName("Evaluate");
    evaluate->setPosition(Vec2(origin.x + visibleSize.width * (-0.5),
        origin.y + visibleSize.height / 2));
    slide_layer->addChild(evaluate);
    //���
    auto skyline = Sprite::create("/GameSelectionScene/themescene2-hd.pvr_2.PNG");
    skyline->setName("Skyline");
    skyline->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height * 0.45));
    slide_layer->addChild(skyline);
    //��ʹؿ�ͳ��
    auto level_1_statistics_image = Sprite::create("/GameSelectionScene/Items03-hd.pvr_0.PNG");
    level_1_statistics_image->setPosition(Vec2(origin.x + visibleSize.width * 0.66,
        origin.y + visibleSize.height * 0.11));
    slide_layer->addChild(level_1_statistics_image);

    auto level_1_statistics_txt = Label::createWithTTF(to_string(UserDefault::getInstance()->getIntegerForKey("level_1")) + "/9",
        "/fonts/Marker Felt.ttf", 20);
    level_1_statistics_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.66,
        origin.y + visibleSize.height * 0.12));
    slide_layer->addChild(level_1_statistics_txt);
    //����
    auto jungle = Sprite::create("/GameSelectionScene/themescene2-hd.pvr_0.PNG");
    jungle->setName("Jungle");
    jungle->setPosition(Vec2(origin.x + visibleSize.width *1.5,
        origin.y + visibleSize.height * 0.45));
    slide_layer->addChild(jungle);
    //���ֹؿ�ͳ��
    if (UserDefault::getInstance()->getIntegerForKey("level_2") == 0) {
        auto level_2_lock = Sprite::create("/GameSelectionScene/themescene1-hd_10.PNG");
        level_2_lock->setPosition(Vec2(origin.x + visibleSize.width * 1.78,
            origin.y + visibleSize.height * 0.2));
        slide_layer->addChild(level_2_lock);
    }
    else {
        //������
    }
    //ɳĮ
    auto desert = Sprite::create("/GameSelectionScene/themescene2-hd.pvr_1.PNG");
    desert->setName("Desert");
    desert->setPosition(Vec2(origin.x + visibleSize.width * 2.5,
        origin.y + visibleSize.height * 0.45));
    slide_layer->addChild(desert);
    //ɳĮ�ؿ�ͳ��
    if (UserDefault::getInstance()->getIntegerForKey("level_3") == 0) {
        auto level_3_lock = Sprite::create("/GameSelectionScene/themescene1-hd_10.PNG");
        level_3_lock->setPosition(Vec2(origin.x + visibleSize.width * 2.78,
            origin.y + visibleSize.height * 0.2));
        slide_layer->addChild(level_3_lock);
    }
    else {
        //������
    }

    /***********************************  ����ʵ��  ***********************************************/
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);//�����¼���û
    listener->onTouchBegan = [slide_layer,evaluate, skyline, jungle, desert](Touch* touch, Event* event) {
        Vec2 pos = slide_layer->convertTouchToNodeSpace(touch);
        //��������ʼ����ÿһ��ͼ�ε�ѡ��Χ�����¼���û
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
    listener->onTouchMoved = [slide_layer](Touch* touch, Event* event) {//ʵ����Ļ�津���ƶ�
        float distance = touch->getLocation().x - touch->getPreviousLocation().x;
        slide_layer->setPositionX(slide_layer->getPositionX() + distance);
    };
    listener->onTouchEnded = [this, slide_layer, visibleSize, evaluate, skyline, jungle, desert](Touch* touch, Event* event) {
        float distance = touch->getLocation().x - touch->getStartLocation().x;//��¼���δ����ĺ������
        float page[4] = { visibleSize.width,0,-visibleSize.width,-2 * visibleSize.width };
        int n = find(page, 4, slide_layer->getPosition().x);
        if (distance > visibleSize.width / 6) {//����������֮һ��Ļ���룬���ӷ�ҳ�ɹ�������һҳ
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
        else if (distance < -visibleSize.width / 6) {//��Ϊ�����ƶ�һҳ
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
        else {//��С������֮һ��Ļ���ӱ��δ���Ϊȡ����ҳ����
            if (distance > 0) {
                slide_layer->runAction(MoveTo::create(0.1, Vec2(page[n + 1], 0)));
            }
            else if (distance < 0) {
                slide_layer->runAction(MoveTo::create(0.1, Vec2(page[n], 0)));
            }
            else {//��û���ƶ�����Ϊ��������ݵ��λ��ȷ��������һ��ѡ��
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
    //���¼������������¼��ַ�����
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, slide_layer);

}
//ȥ���۽�
void BigLevelLayer::goto_evaluate(Ref* psender)
{
    button_sound_effect();//������Ч
    //��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /************************  ��ɫ��  *****************************/
    auto evaluate_layer = LayerColor::create(Color4B::BLACK);
    evaluate_layer->setPosition(Vec2::ZERO);
    evaluate_layer->setOpacity(85);
    this->addChild(evaluate_layer, 1);
    /************************  �¼�������  *****************************/
    auto listener2 = EventListenerTouchOneByOne::create();
    listener2->setSwallowTouches(true);//������û����ȷ�����밴��ť���ܷ�����һҳ
    listener2->onTouchBegan = [evaluate_layer](Touch* touch, Event* event) {
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, evaluate_layer);

    /******************  ����  ***************************/
    auto evaluate_image = Sprite::create("/GameSelectionScene/evaluate.png");
    evaluate_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    evaluate_layer->addChild(evaluate_image);
    /*******************  �˵�  **************************/
    auto evaluate_menu = Menu::create();
    evaluate_menu->setPosition(Vec2::ZERO);
    evaluate_layer->addChild(evaluate_menu);
    //ȷ�ϰ�ť
    auto ok_btn = MenuItemImage::create("/GameSelectionScene/close_evaluate_normal.png", "/GameSelectionScene/close_evaluate_selected.png");
    ok_btn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.25));
    ok_btn->setScale(1.4);
    ok_btn->setCallback([this, evaluate_layer](Ref* psender) {//��ť�ص��¼���������һ��
        button_sound_effect();
        this->removeChild(evaluate_layer);
        });
    evaluate_menu->addChild(ok_btn);

}
//����һҳ
void BigLevelLayer::page_left(Ref* psender)
{
    //��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //��¼ÿһҳ��Ӧ����
    float page[4] = { visibleSize.width,0,-visibleSize.width,-2 * visibleSize.width };
    Node* slide_layer = this->getChildByName("SlideLayer");
    int n = find(page, 4, slide_layer->getPositionX());
    //�����ƶ�һҳ
    if (slide_layer->getPosition().x < page[0]) {
        slide_layer->runAction(MoveBy::create(0.1, Vec2(visibleSize.width, 0)));
        page_sound_effect();
        Node* num_1 = this->getChildByTag(n);
        static_cast<Sprite*>(num_1)->setTexture("/GameSelectionScene/page_yes.png");
        Node* num_2 = this->getChildByTag(n + 1);
        static_cast<Sprite*>(num_2)->setTexture("/GameSelectionScene/page_no.png");
    }

}
//����һҳ
void BigLevelLayer::page_right(Ref* psender)
{
    //��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //��¼ÿһҳ����
    float page[4] = { visibleSize.width,0,-visibleSize.width,-2 * visibleSize.width };
    Node* slide_layer = this->getChildByName("SlideLayer");
    int n = find(page, 4, slide_layer->getPositionX());
    //�����ƶ�һҳ
    if (slide_layer->getPosition().x > page[3]) {
        slide_layer->runAction(MoveBy::create(0.1, Vec2(-visibleSize.width, 0)));
            page_sound_effect();
                Node* num_1 = this->getChildByTag(n + 2);
                static_cast<Sprite*>(num_1)->setTexture("/GameSelectionScene/page_yes.png");
                Node* num_2 = this->getChildByTag(n + 1);
                static_cast<Sprite*>(num_2)->setTexture("/GameSelectionScene/page_no.png");
    }

}
//ȥ���
void BigLevelLayer::goto_level_1(Ref* psender)
{
    button_sound_effect();//������Ч
    auto level_1_layer = Level_1_Layer::createLayer();//�����㣬������
    this->getParent()->addChild(level_1_layer, 1);
    this->removeFromParent();
}
//ȥ����
void BigLevelLayer::goto_level_2(Ref* psender)
{
    button_sound_effect();//������Ч

    if (UserDefault::getInstance()->getIntegerForKey("level_2") == 0) {//����ǰ����δ��������������ʾ

        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        /*****************************  ��ɫ��  ******************************************/
        auto black_layer = LayerColor::create(Color4B::BLACK);
        black_layer->setOpacity(85);

        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
            return true;
        };
        listener->setSwallowTouches(true);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
        /********************************  ����  *****************************************/
        auto level_2_lock = Sprite::create("/GameSelectionScene/level_2_lock.png");
        level_2_lock->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));
        level_2_lock->setScale(1.4);
        black_layer->addChild(level_2_lock);
        /********************************  ��ť  ****************************************/
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
        ;//boss_pattern������
    }
}
//ȥɳĮ
void BigLevelLayer::goto_level_3(Ref* psender)
{
    button_sound_effect();//������Ч

    if (UserDefault::getInstance()->getIntegerForKey("level_2") == 0) {//����ǰɳĮδ��������������ʾ

        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        /*****************************  ��ɫ��  ******************************************/
        auto black_layer = LayerColor::create(Color4B::BLACK);
        black_layer->setOpacity(85);

        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
            return true;
        };
        listener->setSwallowTouches(true);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
        /********************************  ����  *****************************************/
        auto level_3_lock = Sprite::create("/GameSelectionScene/level_3_lock.png");
        level_3_lock->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2));
        level_3_lock->setScale(1.4);
        black_layer->addChild(level_3_lock);
        /********************************  ��ť  ****************************************/
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
        ;//boss_pattern������
    }
}
/********************************  Level_1_Layer  *********************************/
cocos2d::Layer* Level_1_Layer::createLayer()
{
    return Level_1_Layer::create();
}
//��ʼ��
bool Level_1_Layer::init()
{
    if (!Layer::init()) {
        return false;
    }
    //��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /***********************  �˵�  *************************/
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    //����ѡ���
    auto return_btn = MenuItemImage::create("/GameSelectionScene/stages_bg-hd_41.PNG", "/GameSelectionScene/stages_bg-hd_40.PNG",
        CC_CALLBACK_1(Level_1_Layer::return_to_biglevel, this));
    return_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.2,
        origin.y + visibleSize.height * 0.95));
    menu->addChild(return_btn);
    /**********************  ����  **************************/
    auto bg_1 = Sprite::create("/GameSelectionScene/BG_Left.PNG");
    bg_1->setPosition(Vec2(origin.x + bg_1->getContentSize().width / 2,
        origin.y + bg_1->getContentSize().height / 2));
    this->addChild(bg_1);

    auto bg_2 = Sprite::create("/GameSelectionScene/BG_Right.PNG");
    bg_2->setPosition(Vec2(origin.x + +visibleSize.width - bg_2->getContentSize().width / 2,
        origin.y + bg_2->getContentSize().height / 2));
    this->addChild(bg_2);

    /***********************  ������  ***********************/
    create_slide_layer();

    return true;
}
//����������
void Level_1_Layer::create_slide_layer()
{
    //��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /**********************  ���������  ***********************/
    //����һ��������
    auto slide_layer = Layer::create();
    slide_layer->setName("SlideLayer");
    this->addChild(slide_layer);

    //�ɶ���  �津�������ƶ�
    auto move_layer = Layer::create();
    move_layer->setName("MoveLayer");
    slide_layer->addChild(move_layer, 1);
    //���ɶ���  �ڴ���ȷ����ҳ��ֱ���ƶ�
    auto static_layer = Layer::create();
    static_layer->setName("StaticLayer");
    slide_layer->addChild(static_layer, 2);
    /*************************  �ؿ�level_1_1  **************************************/
    //ͼ  ����ͼ�軬��������ɶ���
    auto level_1_1_image = Sprite::create("/GameSelectionScene/Level_1.PNG");
    level_1_1_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height *0.54));
    move_layer->addChild(level_1_1_image);
    //������  ���軬�������벻�ɶ���
    auto waves_1 = Sprite::create("/GameSelectionScene/total_waves.png");
    waves_1->setPosition(Vec2(origin.x + visibleSize.width * 0.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_1);
    auto waves_1_txt = Label::createWithTTF("15", "/fonts/Marker Felt.ttf", 24);
    waves_1_txt->setTextColor(Color4B::YELLOW);
    waves_1_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_1_txt);
    //��̨����  ���軬�������벻�ɶ���
    //ƿ��
    auto tower_1 = Sprite::create("/GameSelectionScene/Tower_1.PNG");
    tower_1->setPosition(Vec2(origin.x + visibleSize.width / 2 - tower_1->getContentSize().width / 2,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_1);
    //���
    auto tower_2 = Sprite::create("/GameSelectionScene/Tower_2.PNG");
    tower_2->setPosition(Vec2(origin.x + visibleSize.width / 2 + tower_2->getContentSize().width / 2,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_2);
    //��ʼ  �����ƶ������벻�ɶ���
    auto level_1_btn = Button::create("/GameSelectionScene/stages_bg-hd_30.PNG", "/GameSelectionScene/stages_bg-hd_28.PNG",
        "/GameSelectionScene/stages_bg-hd_39.PNG");
    level_1_btn->addTouchEventListener(CC_CALLBACK_2(Level_1_Layer::level_1_1, this));
    level_1_btn->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height * 0.1));
    static_layer->addChild(level_1_btn);

    /*************************  �ؿ�level_1_2  **************************************/
    //ͼ �ɶ���
    auto level_1_2_image = Sprite::create("/GameSelectionScene/Level_2.PNG");
    level_1_2_image->setPosition(Vec2(origin.x + visibleSize.width * 1.5,
        origin.y + visibleSize.height * 0.54));
    move_layer->addChild(level_1_2_image);
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 2) {//��δ����������Ⱦ��������ʾ
        auto level_1_2_lock = Sprite::create("/GameSelectionScene/stages_bg-hd_31.PNG");
        level_1_2_lock->setPosition(Vec2(origin.x + visibleSize.width * 1.64,
            origin.y + visibleSize.height * 0.4));
        move_layer->addChild(level_1_2_lock);
    }
    //������ ���ɶ���
    auto waves_2 = Sprite::create("/GameSelectionScene/total_waves.png");
    waves_2->setPosition(Vec2(origin.x + visibleSize.width * 1.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_2);
    auto waves_2_txt = Label::createWithTTF("15", "/fonts/Marker Felt.ttf", 24);
    waves_2_txt->setTextColor(Color4B::YELLOW);
    waves_2_txt->setPosition(Vec2(origin.x + visibleSize.width * 1.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_2_txt);
    //��̨���� ���ɶ���
    //ƿ��
    auto tower_2_1 = Sprite::create("/GameSelectionScene/Tower_1.PNG");
    tower_2_1->setPosition(Vec2(origin.x + visibleSize.width * 1.5 - tower_2_1->getContentSize().width,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_2_1);
    //���
    auto tower_2_2 = Sprite::create("/GameSelectionScene/Tower_2.PNG");
    tower_2_2->setPosition(Vec2(origin.x + visibleSize.width *1.5,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_2_2);
    //����
    auto tower_2_3 = Sprite::create("/GameSelectionScene/Tower_4.PNG");
    tower_2_3->setPosition(Vec2(origin.x + visibleSize.width * 1.5 + tower_2_3->getContentSize().width,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_2_3);
    //��ʼ  ���ɶ���
    auto level_2_btn = Button::create("/GameSelectionScene/stages_bg-hd_30.PNG", "/GameSelectionScene/stages_bg-hd_28.PNG",
        "/GameSelectionScene/stages_bg-hd_39.PNG");
    level_2_btn->addTouchEventListener(CC_CALLBACK_2(Level_1_Layer::level_1_2, this));
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 2) {//��δ�����������ð�ťΪ������
        level_2_btn->setEnabled(false);
    }
    level_2_btn->setPosition(Vec2(origin.x + visibleSize.width * 1.5,
        origin.y + visibleSize.height * 0.1));
    static_layer->addChild(level_2_btn);

    /*************************  �ؿ�level_1_3  **************************************/
     //ͼ �ɶ���
    auto level_1_3_image = Sprite::create("/GameSelectionScene/Level_3.PNG");
    level_1_3_image->setPosition(Vec2(origin.x + visibleSize.width * 2.5,
        origin.y + visibleSize.height * 0.54));
    move_layer->addChild(level_1_3_image);
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 3) {//��δ����������Ⱦ��������ʾ
        auto level_1_3_lock = Sprite::create("/GameSelectionScene/stages_bg-hd_31.PNG");
        level_1_3_lock->setPosition(Vec2(origin.x + visibleSize.width * 2.64,
            origin.y + visibleSize.height * 0.4));
        move_layer->addChild(level_1_3_lock);
    }
    //������  ���ɶ���
    auto waves_3 = Sprite::create("/GameSelectionScene/total_waves.png");
    waves_3->setPosition(Vec2(origin.x + visibleSize.width * 2.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_3);
    auto waves_3_txt = Label::createWithTTF("20", "/fonts/Marker Felt.ttf", 24);
    waves_3_txt->setTextColor(Color4B::YELLOW);
    waves_3_txt->setPosition(Vec2(origin.x + visibleSize.width * 2.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_3_txt);
    //��̨����  ���ɶ���
    //ƿ��
    auto tower_3_1 = Sprite::create("/GameSelectionScene/Tower_1.PNG");
    tower_3_1->setPosition(Vec2(origin.x + visibleSize.width * 2.5 - tower_3_1->getContentSize().width,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_3_1);
    //���
    auto tower_3_2 = Sprite::create("/GameSelectionScene/Tower_2.PNG");
    tower_3_2->setPosition(Vec2(origin.x + visibleSize.width * 2.5,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_3_2);
    //����
    auto tower_3_3 = Sprite::create("/GameSelectionScene/Tower_3.PNG");
    tower_3_3->setPosition(Vec2(origin.x + visibleSize.width * 2.5 + tower_3_3->getContentSize().width,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_3_3);
    //��ʼ ���ɶ���
    auto level_3_btn = Button::create("/GameSelectionScene/stages_bg-hd_30.PNG", "/GameSelectionScene/stages_bg-hd_28.PNG",
        "/GameSelectionScene/stages_bg-hd_39.PNG");
    level_3_btn->addTouchEventListener(CC_CALLBACK_2(Level_1_Layer::level_1_3, this));
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 3) {//��δ�����������ð�ťΪ������
        level_3_btn->setEnabled(false);
    }
    level_3_btn->setPosition(Vec2(origin.x + visibleSize.width * 2.5,
        origin.y + visibleSize.height * 0.1));
    static_layer->addChild(level_3_btn);


    /*************************  �ؿ�level_1_4  **************************************/
    //ͼ
    auto level_1_4_image = Sprite::create("/GameSelectionScene/Level_4.PNG");
    level_1_4_image->setPosition(Vec2(origin.x + visibleSize.width * 3.5,
        origin.y + visibleSize.height * 0.54));
    move_layer->addChild(level_1_4_image);
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 4) {//��δ����������Ⱦ��������ʾ
        auto level_1_4_lock = Sprite::create("/GameSelectionScene/stages_bg-hd_31.PNG");
        level_1_4_lock->setPosition(Vec2(origin.x + visibleSize.width * 3.64,
            origin.y + visibleSize.height * 0.4));
        move_layer->addChild(level_1_4_lock);
    }
    //������
    auto waves_4 = Sprite::create("/GameSelectionScene/total_waves.png");
    waves_4->setPosition(Vec2(origin.x + visibleSize.width * 3.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_4);
    auto waves_4_txt = Label::createWithTTF("20", "/fonts/Marker Felt.ttf", 24);
    waves_4_txt->setTextColor(Color4B::YELLOW);
    waves_4_txt->setPosition(Vec2(origin.x + visibleSize.width * 3.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_4_txt);
    //��̨����
    //���
    auto tower_4_1 = Sprite::create("/GameSelectionScene/Tower_2.PNG");
    tower_4_1->setPosition(Vec2(origin.x + visibleSize.width * 3.5 - tower_4_1->getContentSize().width/2,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_4_1);
    //ˮ����
    auto tower_4_2 = Sprite::create("/GameSelectionScene/Tower_5.PNG");
    tower_4_2->setPosition(Vec2(origin.x + visibleSize.width * 3.5 + tower_4_2->getContentSize().width / 2,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_4_2);
    //��ʼ
    auto level_4_btn = Button::create("/GameSelectionScene/stages_bg-hd_30.PNG", "/GameSelectionScene/stages_bg-hd_28.PNG",
        "/GameSelectionScene/stages_bg-hd_39.PNG");
    level_4_btn->addTouchEventListener(CC_CALLBACK_2(Level_1_Layer::level_1_4, this));
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 4) {
        level_4_btn->setEnabled(false);
    }
    level_4_btn->setPosition(Vec2(origin.x + visibleSize.width * 3.5,
        origin.y + visibleSize.height * 0.1));
    static_layer->addChild(level_4_btn);

    /*************************  �ؿ�level_1_5  **************************************/
    //ͼ
    auto level_1_5_image = Sprite::create("/GameSelectionScene/Level_5.PNG");
    level_1_5_image->setPosition(Vec2(origin.x + visibleSize.width * 4.5,
        origin.y + visibleSize.height * 0.54));
    move_layer->addChild(level_1_5_image);
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 5) {//��δ����������Ⱦ��������ʾ
        auto level_1_5_lock = Sprite::create("/GameSelectionScene/stages_bg-hd_31.PNG");
        level_1_5_lock->setPosition(Vec2(origin.x + visibleSize.width * 4.64,
            origin.y + visibleSize.height * 0.4));
        move_layer->addChild(level_1_5_lock);
    }
    //������
    auto waves_5 = Sprite::create("/GameSelectionScene/total_waves.png");
    waves_5->setPosition(Vec2(origin.x + visibleSize.width * 4.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_5);
    auto waves_5_txt = Label::createWithTTF("20", "/fonts/Marker Felt.ttf", 24);
    waves_5_txt->setTextColor(Color4B::YELLOW);
    waves_5_txt->setPosition(Vec2(origin.x + visibleSize.width * 4.6,
        origin.y + visibleSize.height * 0.83));
    static_layer->addChild(waves_5_txt);
    //��̨����
    //���
    auto tower_5_1 = Sprite::create("/GameSelectionScene/Tower_2.PNG");
    tower_5_1->setPosition(Vec2(origin.x + visibleSize.width * 4.5 - tower_5_1->getContentSize().width / 2,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_5_1);
    //����
    auto tower_5_2 = Sprite::create("/GameSelectionScene/Tower_4.PNG");
    tower_5_2->setPosition(Vec2(origin.x + visibleSize.width * 4.5 + tower_5_2->getContentSize().width / 2,
        origin.y + visibleSize.height * 0.23));
    static_layer->addChild(tower_5_2);
    //��ʼ
    auto level_5_btn = Button::create("/GameSelectionScene/stages_bg-hd_30.PNG", "/GameSelectionScene/stages_bg-hd_28.PNG",
        "/GameSelectionScene/stages_bg-hd_39.PNG");
    level_5_btn->addTouchEventListener(CC_CALLBACK_2(Level_1_Layer::level_1_5, this));
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 5) {//��δ�����������ð�ťΪ������
        level_5_btn->setEnabled(false);
    }
    level_5_btn->setPosition(Vec2(origin.x + visibleSize.width * 4.5,
        origin.y + visibleSize.height * 0.1));
    static_layer->addChild(level_5_btn);



    /***********************  ����ʵ��  *****************************/
    auto listener4 = EventListenerTouchOneByOne::create();
    listener4->onTouchBegan = [move_layer](Touch* touch, Event* event) {
        return true;
    };
    listener4->onTouchMoved = [move_layer](Touch* touch, Event* event) {//ʵ�ִ�������
        float distance = touch->getLocation().x - touch->getPreviousLocation().x;
        move_layer->setPositionX(move_layer->getPositionX() + distance);
    };
    listener4->onTouchEnded = [=](Touch* touch, Event* event) {
        //��ȡ�����ƶ��������
        float distance = touch->getLocation().x - touch->getStartLocation().x;
        //��¼ÿһҳ����
        float page[5] = { 0,-visibleSize.width,-2 * visibleSize.width ,-3 * visibleSize.width ,-4 * visibleSize.width };
        int n = find(page, 5, move_layer->getPosition().x);

        if (distance > visibleSize.width / 6) {//��������������֮һ��Ļ������Ϊ������ҳ
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
        else {//��С������֮һ��Ļ������Ϊȡ����ҳ����
            if (distance > 0) {//��ȡ����ҳ����ص�����ǰ��ҳ��
                move_layer->runAction(MoveTo::create(0.1, Vec2(page[n + 1], 0)));
                static_layer->setPosition(Vec2(page[n + 1], static_layer->getPositionY()));
            }
            else if (distance < 0) {
                move_layer->runAction(MoveTo::create(0.1, Vec2(page[n], 0)));
                static_layer->setPosition(Vec2(page[n], static_layer->getPositionY()));
            }
            else {//���������������λ�ã����йؿ�ѡ��
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
    //���¼������������¼��ַ���
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener4, move_layer);
}
//�ص�ѡ��ؽ���
void Level_1_Layer::return_to_biglevel(Ref* psender)
{
    button_sound_effect();//������Ч
    auto big_level_layer = BigLevelLayer::createLayer();//�������Layer
    this->getParent()->addChild(big_level_layer);//��Ⱦ
    this->removeFromParent();//�Ƴ���ǰLayer
}
//��ʵ�1��
void Level_1_Layer::level_1_1(Ref* psender, Widget::TouchEventType type)
{
    //��ť�ص�����
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::CANCELED:
            break;
        case Widget::TouchEventType::ENDED://���ҽ���̧��ʱ����
            button_sound_effect();//������Ч
            level_selection = 1;
            auto game_scene = GameScene::createScene();
            Director::getInstance()->replaceScene(game_scene);
            break;
    }
}
//��ʵ�2��
void Level_1_Layer::level_1_2(Ref* psender, Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::CANCELED:
            break;
        case Widget::TouchEventType::ENDED://���ҽ���̧��ʱ����
            button_sound_effect();//������Ч

            if (UserDefault::getInstance()->getIntegerForKey("level_1") < 2) {//����ǰ��δ������������ʾ

                auto visibleSize = Director::getInstance()->getVisibleSize();
                Vec2 origin = Director::getInstance()->getVisibleOrigin();
                /*****************************  ��ɫ��  ******************************************/
                auto black_layer = LayerColor::create(Color4B::BLACK);
                black_layer->setOpacity(85);

                auto listener = EventListenerTouchOneByOne::create();
                listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
                    return true;
                };
                listener->setSwallowTouches(true);
                Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
                /********************************  ����  *****************************************/
                auto lock = Sprite::create("/GameSelectionScene/lock_image.png");
                lock->setPosition(Vec2(origin.x + visibleSize.width / 2,
                    origin.y + visibleSize.height / 2));
                lock->setScale(1.4);
                black_layer->addChild(lock);
                /********************************  ��ť  ****************************************/
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
//��ʵ�3��
void Level_1_Layer::level_1_3(Ref* psender, Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::CANCELED:
            break;
        case Widget::TouchEventType::ENDED://���ҽ���̧��ʱ����
            button_sound_effect();//������Ч

            if (UserDefault::getInstance()->getIntegerForKey("level_1") < 3) {//��δ������������ʾ

                auto visibleSize = Director::getInstance()->getVisibleSize();
                Vec2 origin = Director::getInstance()->getVisibleOrigin();
                /*****************************  ��ɫ��  ******************************************/
                auto black_layer = LayerColor::create(Color4B::BLACK);
                black_layer->setOpacity(85);

                auto listener = EventListenerTouchOneByOne::create();
                listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
                    return true;
                };
                listener->setSwallowTouches(true);
                Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
                /********************************  ����  *****************************************/
                auto lock = Sprite::create("/GameSelectionScene/lock_image.png");
                lock->setPosition(Vec2(origin.x + visibleSize.width / 2,
                    origin.y + visibleSize.height / 2));
                lock->setScale(1.4);
                black_layer->addChild(lock);
                /********************************  ��ť  ****************************************/
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
                ;//level_1_3������
            }
            break;
    }
}
//��ʵ�4��
void Level_1_Layer::level_1_4(Ref* psender, Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::CANCELED:
            break;
        case Widget::TouchEventType::ENDED://���ҽ���̧��ʱ����
            button_sound_effect();//������Ч

            if (UserDefault::getInstance()->getIntegerForKey("level_1") < 4) {//��δ������������ʾ

                auto visibleSize = Director::getInstance()->getVisibleSize();
                Vec2 origin = Director::getInstance()->getVisibleOrigin();
                /*****************************  ��ɫ��  ******************************************/
                auto black_layer = LayerColor::create(Color4B::BLACK);
                black_layer->setOpacity(85);

                auto listener = EventListenerTouchOneByOne::create();
                listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
                    return true;
                };
                listener->setSwallowTouches(true);
                Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
                /********************************  ����  *****************************************/
                auto lock = Sprite::create("/GameSelectionScene/lock_image.png");
                lock->setPosition(Vec2(origin.x + visibleSize.width / 2,
                    origin.y + visibleSize.height / 2));
                lock->setScale(1.4);
                black_layer->addChild(lock);
                /********************************  ��ť  ****************************************/
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
                ;//level_1_4������
            }
            break;
    }
}
//��ʵ�5��
void Level_1_Layer::level_1_5(Ref* psender, Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::CANCELED:
            break;
        case Widget::TouchEventType::ENDED://���ҽ���̧��ʱ����
            button_sound_effect();//������Ч

            if (UserDefault::getInstance()->getIntegerForKey("level_1") < 5) {//��δ������������ʾ

                auto visibleSize = Director::getInstance()->getVisibleSize();
                Vec2 origin = Director::getInstance()->getVisibleOrigin();
                /*****************************  ��ɫ��  ******************************************/
                auto black_layer = LayerColor::create(Color4B::BLACK);
                black_layer->setOpacity(85);

                auto listener = EventListenerTouchOneByOne::create();
                listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
                    return true;
                };
                listener->setSwallowTouches(true);
                Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
                /********************************  ����  *****************************************/
                auto lock = Sprite::create("/GameSelectionScene/lock_image.png");
                lock->setPosition(Vec2(origin.x + visibleSize.width / 2,
                    origin.y + visibleSize.height / 2));
                lock->setScale(1.4);
                black_layer->addChild(lock);
                /********************************  ��ť  ****************************************/
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
                ;//level_1_5������
            }
            break;
    }
}
