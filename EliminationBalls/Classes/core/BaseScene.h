//
//  BaseScene.h
//  minGameTest
//
//  Created by 马 英臣 on 13-8-15.
// 场景基类
//

#ifndef minGameTest_BaseScene_h
#define minGameTest_BaseScene_h

#include "cocos2d.h"
#include "cocos-ext.h"
//#include "UIManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BaseScene: public cocos2d::Layer{
    
public:
    
    BaseScene();    
    virtual ~BaseScene();
    
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
    static cocos2d::Scene* scene();    

    CREATE_FUNC(BaseScene);    
    
    Node* getPopsNode(){return popsNode;};
    Node* getTipsNode(){return tipsNode;};
    
protected:
    //基础层
    Node*baseNode;
private:    
    //ui弹窗层
    Node* popsNode;
    //提示层
    Node* tipsNode;

};


#endif
