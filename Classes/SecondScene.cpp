//
// Created by engineer on 2020/4/28.
//

#include "SecondScene.h"
#include "HelloWorldScene.h"
#include "MyTools.h"
#include "MyScenes.h"

USING_NS_CC;

Scene * SecondScene::createScene(){
    return SecondScene::create();
}

bool SecondScene::init() {
    if (!Scene::init())
    {
        return false;
    }

    auto layerColor = LayerColor::create(Color4B(0,255,255,255));
    layerColor->setVisible(true);
    this->addChild(layerColor);

    initMenu();

    return true;
}

void SecondScene::replaceScene(cocos2d::Ref *pSender) {
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void SecondScene::initMenu() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    alert({"Second Scene Opened!"});
    auto item = MenuItemFont::create("HelloWorldScene",CC_CALLBACK_1(SecondScene::replaceScene,this));

    MenuItemFont * actionItemTo;
    actionItemTo = MenuItemFont::create("Cocos2dx基本动作Action", [](Ref *sender) {
        Director::getInstance()->replaceScene(ActionScene::createScene());
//        Director::getInstance()->replaceScene(TransitionPageTurn::create(3,ActionScene::createScene(),true));
    });



    auto menu = Menu::create(item,actionItemTo, nullptr);
    menu->alignItemsVertically();
    this->addChild(menu);




    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(SecondScene::menuClose, this));
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 10;
    float y = origin.y + closeItem->getContentSize().height / 2 + 10;
    closeItem->setPosition(Vec2(x, y));
    auto menu2 = Menu::create(closeItem, NULL);
    menu2->alignItemsVertically();
    menu2->setPosition(Vec2(x, y));
    //添加过的菜单再次添加将不会生效
    this->addChild(menu2);
}

void SecondScene::menuClose(cocos2d::Ref *pSender) {
    Director::getInstance()->end();
}
