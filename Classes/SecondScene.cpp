//
// Created by engineer on 2020/4/28.
//

#include "SecondScene.h"
#include "HelloWorldScene.h"
#include "MyTools.h"
USING_NS_CC;

Scene * SecondScene::createScene(){
    return SecondScene::create();
}

bool SecondScene::init() {
    if (!Scene::init())
    {
        return false;
    }

    auto layerColor = LayerColor::create(Color4B(0,0,255,255));
    layerColor->setVisible(true);
    this->addChild(layerColor);
//    alert({"Second Scene Opened!"});
    auto item = MenuItemFont::create("HelloWorldScene",CC_CALLBACK_1(SecondScene::replaceScene,this));
    auto menu = Menu::create(item, nullptr);
    menu->alignItemsVertically();
    this->addChild(menu);
    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(SecondScene::menuClose, this));
    auto menu2 = Menu::create(closeItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu);
}

void SecondScene::replaceScene(cocos2d::Ref *pSender) {
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void SecondScene::menuClose(cocos2d::Ref *pSender) {
    Director::getInstance()->end();
}