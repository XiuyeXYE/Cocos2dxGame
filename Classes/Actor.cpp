//
// Created by engineer on 2020/5/7.
//

#include "Actor.h"

USING_NS_CC;

//    auto explosionAnimation = Animation::create();
//    explosionAnimation->setDelayPerUnit(1.0/60);//indeed needed to animate
//    for(int i=1;i<20;i++){
//        explosionAnimation->addSpriteFrame(
//                SpriteFrameCache::getInstance()->getSpriteFrameByName(
//                        StringUtils::format("images/explosion%d.png",i)));
//    }
//    return Animate::create(explosionAnimation);
void GlobalEnv::load() {
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("good.plist");
}

//Actor::Actor(){
//    this->init();
//}

void Actor::collide(cocos2d::Rect &rect) {
    sprite->getBoundingBox().intersectsRect(rect);
}

Sprite *Actor::actor() {
    return sprite;
}

void Actor::setPosition(float x, float y) {
    sprite->setPosition(x, y);
}

void Actor::release() {
//    sprite->release();
    sprite->removeFromParent();
}

void Hero::init() {
    sprite = Sprite::createWithSpriteFrameName("images/hero.png");
}

void Hero::move(float time, int x, int y) {
    sprite->runAction(MoveBy::create(time, Point(x, y)));
}

void Enemy::init() {
    sprite = Sprite::createWithSpriteFrameName("images/enemy.png");
}

void Enemy::move(float time, int x, int y) {
    sprite->runAction(MoveBy::create(time, Point(x, y)));
}


