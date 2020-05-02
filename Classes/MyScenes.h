//
// Created by engineer on 2020/4/29.
//

#ifndef PROJ_ANDROID_MYSCENES_H
#define PROJ_ANDROID_MYSCENES_H

#include "cocos2d.h"

class ActionScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void initMenu();
    void initActions();

    void replaceScene(cocos2d::Ref* pSender);
    void scheduleRun(float delta);

    CREATE_FUNC(ActionScene);
};

#endif //PROJ_ANDROID_MYSCENES_H
