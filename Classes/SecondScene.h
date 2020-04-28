//
// Created by engineer on 2020/4/28.
//

#ifndef PROJ_ANDROID_SECONDSCENE_H
#define PROJ_ANDROID_SECONDSCENE_H

#include "cocos2d.h"

class SecondScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void replaceScene(cocos2d::Ref* pSender);

    void menuClose(cocos2d::Ref* pSender);

    CREATE_FUNC(SecondScene);
};

#endif //PROJ_ANDROID_SECONDSCENE_H
