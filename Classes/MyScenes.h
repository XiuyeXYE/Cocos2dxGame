//
// Created by engineer on 2020/4/29.
//

#ifndef PROJ_ANDROID_MYSCENES_H
#define PROJ_ANDROID_MYSCENES_H

#include "cocos2d.h"
#include "Actor.h"


class ActionScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void initMenu();
    void initActions();
    void initAudio();

    virtual void update(float delta);

    void replaceScene(cocos2d::Ref* pSender);
    void scheduleRun(float delta);

    CREATE_FUNC(ActionScene);

    void onEnter();

    void onEnterTransitionDidFinish();

    void onExit();

    void onExitTransitionDidStart();

    void cleanup();
};

class WarScene : public cocos2d::Scene {
public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    void initBG();

    void initMenu();

    void initSprite();

    void update();

    CREATE_FUNC(WarScene);
private:
    Hero *hero;
    Enemy *enemy;
public:
    ~WarScene();
};

#endif //PROJ_ANDROID_MYSCENES_H
