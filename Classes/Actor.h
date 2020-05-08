//
// Created by engineer on 2020/5/7.
//

#ifndef PROJ_ANDROID_ACTOR_H
#define PROJ_ANDROID_ACTOR_H

#include "cocos2d.h"

USING_NS_CC;

class GlobalEnv {
public:
    static void load();
};

class Actor {
public:
//    Actor();
    virtual void init() = 0;

    virtual void collide(cocos2d::Rect &rect);

    virtual cocos2d::Sprite *actor();

    virtual void setPosition(float x, float y);

    virtual void release();

    virtual cocos2d::Sprite *operator->();

    virtual operator Sprite *();

    virtual operator Sprite &();

protected:
    cocos2d::Sprite *sprite;
};

//2D move
class Hero : public Actor {
public:
    void init();

    void move(float time, int x, int y);

private:

};

class Enemy : public Actor {
public:
    void init();

    void move(float time, int x, int y);


private:

};


#endif //PROJ_ANDROID_ACTOR_H
