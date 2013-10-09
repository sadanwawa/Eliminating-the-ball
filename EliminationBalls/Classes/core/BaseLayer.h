//
//  BaseLayer.h
//  minGameTest
//
//  Created by 马 英臣 on 13-9-2.
//layer 弹窗基类
//

#ifndef minGameTest_BaseLayer_h
#define minGameTest_BaseLayer_h

#include "BaseDataVO.h"
#include "BaseNode.h"
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BaseLayer :public Layer{
public:

    BaseLayer();
    virtual ~BaseLayer();
    
    virtual const char* description();
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool init();
    
    virtual void onNodeLoaded(cocos2d::Node * node, NodeLoader * nodeLoader);
    virtual void updataUI(BaseDataVO* data=NULL);
    virtual bool ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    
    virtual BaseDataVO* getDataVO(){return _dataVo;};
    
    
private:        
    BaseDataVO* _dataVo;
};





#endif
