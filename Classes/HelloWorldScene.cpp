/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SecondScene.h"
#include "MyTools.h"
USING_NS_CC;



Scene *HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
//    this->updateDisplayedColor(Color3B(0,0,255));

// set background color OK!
    auto layerColor = LayerColor::create(Color4B(255,0,0,255));
    layerColor->setVisible(true);
    this->addChild(layerColor);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 10;
        float y = origin.y + closeItem->getContentSize().height / 2 + 10;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    auto strawberry  = Sprite::create("fruit/strawberry.jpg");
    strawberry->setPosition(Point(100,100));
    strawberry->setAnchorPoint(Point(0.5,0.5));
    this->addChild(strawberry);

    auto size = Director::getInstance()->getWinSize();
    auto grape = Sprite::create("fruit/grape.jpg");
    grape->setAnchorPoint(Point(0.5,0.5));
    grape->setPosition(Point(size.width/2,size.height/2));
    grape->setFlippedY(true);
    this->addChild(grape);

    auto helloLabel = Label::createWithSystemFont("Hello World","Thonburi",34);
    helloLabel->setPosition(Point(240,160));
    helloLabel->enableShadow(Color4B::BLUE,Size(2,-2));
    this->addChild(helloLabel);

    auto item_1 = MenuItemImage::create(
            "CloseNormal.png","CloseSelected.png",
            CC_CALLBACK_1(HelloWorld::menuCallback1,this)
            );
    auto item_2 = MenuItemImage::create(
            "CloseNormal.png","CloseSelected.png",
            CC_CALLBACK_1(HelloWorld::menuCallback2,this)
            );
    auto item_3 = MenuItemImage::create(
            "CloseNormal.png","CloseSelected.png",
            CC_CALLBACK_1(HelloWorld::menuCallback3,this)
            );
    auto menu2 = Menu::create(item_1,item_2,item_3, nullptr);
    menu2->alignItemsVertically();
    this->addChild(menu2);
    auto item_5 = MenuItemFont::create(
            "Play",
            CC_CALLBACK_1(HelloWorld::menuCallback1,this)
            );
    auto item_6 = MenuItemFont::create(
            "High Scores",
            CC_CALLBACK_1(HelloWorld::menuCallback2,this)
            );
    auto item_7 = MenuItemFont::create(
            "About",
            CC_CALLBACK_1(HelloWorld::menuCallback3,this)
            );
    auto menu3 = Menu::create(item_5,item_6,item_7, nullptr);
    menu3->alignItemsVertically();
    menu3->setPosition(100,100);
    this->addChild(menu3);

    alert({"HelloWorld Scene Opened!"});


    auto replaceSceneItem = MenuItemFont::create("切换场景",CC_CALLBACK_1(HelloWorld::replaceScene,this));

    auto menu5 = Menu::create(replaceSceneItem, nullptr);
    menu5->alignItemsVertically();
    menu5->setPosition(100,200);
    this->addChild(menu5);





    return true;
}

void HelloWorld::replaceScene(cocos2d::Ref *pSender) {
    Director::getInstance()->replaceScene(SecondScene::createScene());
    alert({"replace Scene"});
}

void HelloWorld::menuCallback1(Ref *pSender){
    alert({"item1","called!","哈哈..."});
    CCLOG("item1");
}
void HelloWorld::menuCallback2(Ref *pSender){
    alert({"item2","called!","哈哈..."});
    CCLOG("item2");
}
void HelloWorld::menuCallback3(Ref *pSender){
    alert({"item3","called!","哈哈..."});
    CCLOG("item3");
}

void HelloWorld::menuCloseCallback(Ref *pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
