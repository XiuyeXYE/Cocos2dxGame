//
// Created by engineer on 2020/4/29.
//

#include "MyScenes.h"
#include "HelloWorldScene.h"

USING_NS_CC;

bool ActionScene::init() {

    if(!Scene::init()){
        return false;
    }

    auto layerColor = LayerColor::create(Color4B(255,255,0,255));
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


    return true;
}



void ActionScene::initMenu() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto helloWorldItem = MenuItemFont::create("ToHelloWorldScene",
                                               CC_CALLBACK_1(ActionScene::replaceScene,this));
    helloWorldItem->setColor(Color3B::BLACK);
    helloWorldItem->setAnchorPoint(Point(1,0));


    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            [](Ref *sender){
                Director::getInstance()->end();
            });
//    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 10;
//    float y = origin.y + closeItem->getContentSize().height / 2 + 10;
    closeItem->setAnchorPoint(Point(1,0));
//    closeItem->setAnchorPoint(Point(1,1));
//    closeItem->setPosition(visibleSize.width-10,10);
    auto menu = Menu::create(helloWorldItem,closeItem,nullptr);
    menu->alignItemsVertically();
    menu->setAnchorPoint(Point(1,0));
    menu->setPosition(visibleSize.width-10,100);
    this->addChild(menu);



}

cocos2d::Scene* ActionScene::createScene() {

    return ActionScene::create();
}
void ActionScene::replaceScene(cocos2d::Ref *pSender) {
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void ActionScene::initActions() {
    auto sprite = Sprite::create("plane/images/hero.png");
    sprite->setPosition(20,20);
    this->addChild(sprite);
    auto jmpAct = JumpBy::create(5.0,Point(300,100),150,5);
    sprite->runAction(jmpAct);

    auto sprite2 = Sprite::create("plane/images/enemy.png");
    sprite2->setPosition(50,50);
    addChild(sprite2);

}
