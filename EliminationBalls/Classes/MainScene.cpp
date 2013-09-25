//
//  MainScene.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-8-15.
//
//

#include "MainScene.h"


MainScene::MainScene(){
    
}
MainScene::~MainScene(){
    
}

 bool MainScene::init(){
     if(!BaseScene::init()){
         return false;
     }
          
     Size visibleSize = Director::getInstance()->getVisibleSize();
     Point origin = Director::getInstance()->getVisibleOrigin();
     //背景图
     Sprite* sprite = Sprite::create("HelloWorld.png");
     sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));     
     baseNode->addChild(sprite, 0);

     //标题
     LabelTTF* label = LabelTTF::create("MainScene", "Arial", 24);     
     label->setPosition(Point(origin.x + visibleSize.width/2,
                              origin.y + visibleSize.height - label->getContentSize().height));     
     
     baseNode->addChild(label, 1);            
     
     return true;
 }

cocos2d::Scene* MainScene::scene(){
    
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();    
    // 'layer' is an autorelease object
    MainScene *layer = MainScene::create();    
    // add layer as a child to scene
    scene->addChild(layer);    
    // return the scene
    return scene;
}
