//
//  BallLayer.h
//  minGameTest
//
//  Created by 马 英臣 on 13-8-20.
//
//

#ifndef minGameTest_BallLayer_h
#define minGameTest_BallLayer_h


#include "cocos2d.h"
#include "cocos-ext.h"
#include "UIManager.h"
#include "ChessDataVO.h"
#include "ChessLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BallLayer:
public BaseLayer,
public cocos2d::extension::CCBSelectorResolver,
public cocos2d::extension::CCBMemberVariableAssigner,
public NodeLoaderListener

{   
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BallLayer, create);     
      
    BallLayer();    
    virtual ~BallLayer();        
    virtual void onEnter();
    virtual void onExit();    
    virtual bool init();
    void updataUI();
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object * pTarget, const char * pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Object * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(Object * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
    virtual bool onAssignCCBCustomProperty(Object* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
    virtual void onNodeLoaded(cocos2d::Node * node, NodeLoader * nodeLoader);
    
    virtual bool ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);   
        
private:    

        
    
    
    
};







#endif
