//
// Created by engineer on 2020/4/29.
//

#include "MyScenes.h"
#include "HelloWorldScene.h"
#include "MyTools.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

bool ActionScene::init() {

    if (!Scene::init()) {
        return false;
    }

    auto layerColor = LayerColor::create(Color4B(255, 255, 0, 255));
    layerColor->setVisible(true);
    this->addChild(layerColor);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto sprite = Sprite::create("bg.png");
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    initMenu();
    initActions();
    initAudio();



    return true;
}


void ActionScene::initMenu() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto helloWorldItem = MenuItemFont::create("ToHelloWorldScene",
                                               CC_CALLBACK_1(ActionScene::replaceScene, this));
    helloWorldItem->setColor(Color3B::BLACK);
    helloWorldItem->setAnchorPoint(Point(1, 0));


    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            [](Ref *sender) {
                Director::getInstance()->end();
            });
//    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 10;
//    float y = origin.y + closeItem->getContentSize().height / 2 + 10;
    closeItem->setAnchorPoint(Point(1, 0));
//    closeItem->setAnchorPoint(Point(1,1));
//    closeItem->setPosition(visibleSize.width-10,10);
    auto menu = Menu::create(helloWorldItem, closeItem, nullptr);
    menu->alignItemsVertically();
    menu->setAnchorPoint(Point(1, 0));
    menu->setPosition(visibleSize.width - 10, 100);
    this->addChild(menu);


}

cocos2d::Scene *ActionScene::createScene() {

    return ActionScene::create();
}

void ActionScene::replaceScene(cocos2d::Ref *pSender) {
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void ActionScene::initActions() {
    auto sprite = Sprite::create("plane/images/hero.png");
    sprite->setPosition(20, 20);
    sprite->setTag(1);
    this->addChild(sprite);
    auto jmpAct = JumpBy::create(5.0, Point(300, 100), 150, 5);
    sprite->runAction(jmpAct);

    auto sprite2 = Sprite::create("plane/images/enemy.png");
    sprite2->setPosition(50, 50);
    addChild(sprite2);

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch *touch, Event *event) -> bool {
        Point location = touch->getLocation();
        alert({"onTouchBegin: Location x=", std::to_string(location.x).c_str(), "y=",
               std::to_string(location.y).c_str()});
        auto spr = (Sprite *) this->getChildByTag(1);
        auto rect = spr->getBoundingBox();
        if (rect.containsPoint(location)) {
            spr->setScale(2);
        } else {
            spr->setScale(1);
        }
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

    auto listener2 = EventListenerTouchAllAtOnce::create();
    listener2->onTouchesBegan = [](const std::vector<Touch *> &touches, Event *event) {
        CCLOG("Multiple touch");
//        std::vector<Touch*>::const_iterator it = touches.begin();
//        Touch *touch;
//        Point location[2];
        for (auto &touch : touches) {

            auto location = touch->getLocation();
            CCLOG("location : %f , %f", location.x, location.y);

        }


    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener2, 1);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("good.plist");
    auto spr = Sprite::createWithSpriteFrameName("greenapple.jpg");
    spr->setPosition(100,100);
    this->addChild(spr);

    auto explosionAnimation = Animation::create();
    explosionAnimation->setDelayPerUnit(0.3);
    for(int i=1;i<20;i++){
        explosionAnimation->addSpriteFrameWithFile(StringUtils::format("plane/images/explosion%d.png",i));
    }
    auto explosionAnimate = Animate::create(explosionAnimation);

    spr->runAction(explosionAnimate);

    explosionAnimation = Animation::create();
    explosionAnimation->setDelayPerUnit(1.0/60);//indeed needed to animate
    for(int i=1;i<20;i++){
        explosionAnimation->addSpriteFrame(
                SpriteFrameCache::getInstance()->getSpriteFrameByName(
                        StringUtils::format("images/explosion%d.png",i)));
    }
    explosionAnimate = Animate::create(explosionAnimation);
    auto explosionForeverAction = RepeatForever::create(explosionAnimate);
    auto  explosion = Sprite::createWithSpriteFrameName("images/explosion1.png");
    explosion->setPosition(200,200);

    this->addChild(explosion);
    explosion->runAction(explosionForeverAction);

    this->schedule(schedule_selector(ActionScene::scheduleRun),1.0);
//    auto node = ParallaxNode::create();
//    this->addChild(node);
//    auto action_0 = MoveBy::create(10.0,Point(100,100));
//    auto action_1 = Place::create(Point::ZERO);
//    auto action_2 = Sequence::create(action_0,action_1);
//    auto action_3 = RepeatForever::create(action_2);
//
//    auto spr_0 = Sprite::createWithSpriteFrameName("lemon.jpg");
//    spr_0->setAnchorPoint(Point::ZERO);
//    node->addChild(spr_0,0,Point(1,1),Point::ZERO);
//
//    auto spr_1 = Sprite::createWithSpriteFrameName("lemon.jpg");
//    spr_1->setAnchorPoint(Point::ZERO);
//    node->addChild(spr_1,0,Point(1,1),Point(100,100));
//    node->runAction(action_3);
}

void ActionScene::scheduleRun(float delta) {
    CCLOG("scheduler running: %f",delta);
}

void ActionScene::initAudio() {
    CCLOG("init audio");
    SimpleAudioEngine::getInstance()->playBackgroundMusic("plane/audio/boom.mp3",true);
}