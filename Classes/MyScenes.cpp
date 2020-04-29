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

    initMenu();



    return true;
}



void ActionScene::initMenu() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto helloWorldItem = MenuItemFont::create("ToHelloWorldScene",
                                               CC_CALLBACK_1(ActionScene::replaceScene,this));
    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            [](Ref *sender){
                Director::getInstance()->end();
            });
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 10;
    float y = origin.y + closeItem->getContentSize().height / 2 + 10;
    closeItem->setPosition(Vec2(x, y));
    auto menu = Menu::create(helloWorldItem,closeItem,nullptr);
    menu->alignItemsVertically();
    menu->setPosition(x,y);
    this->addChild(menu);
}

cocos2d::Scene* ActionScene::createScene() {

    return ActionScene::create();
}
void ActionScene::replaceScene(cocos2d::Ref *pSender) {
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}