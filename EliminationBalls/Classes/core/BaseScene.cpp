//
//  BaseScene.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-8-15.
//
//

#include "BaseScene.h"
//#include "../common/StaticConstant.h"
#include "../manager/UIManager.h"

BaseScene::BaseScene(){   
    baseNode=Node::create();
    baseNode->retain();
    popsNode=Node::create();
    popsNode->retain();
    tipsNode=Node::create();
    tipsNode->retain();    
    this->addChild(baseNode);
    this->addChild(popsNode);
    this->addChild(tipsNode);
   
}

BaseScene::~BaseScene(){
    CC_SAFE_RELEASE(popsNode);
    CC_SAFE_RELEASE(tipsNode);
}

void BaseScene::onEnter(){
    Layer::onEnter();
     UIManager::Instance()->setCurrScene(this);    
}
void BaseScene::onExit(){
    Layer::onExit();
    
}

 bool BaseScene::init(){
     if(!Layer::init()){
         return false;
     }
     
     return true;
 }

cocos2d::Scene* BaseScene::scene(){    
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();    
    // 'layer' is an autorelease object
    BaseScene *layer = BaseScene::create();    
    // add layer as a child to scene
    scene->addChild(layer);    
    // return the scene
    return scene;
}
