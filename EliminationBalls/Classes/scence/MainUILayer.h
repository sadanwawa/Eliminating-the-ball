//
//  MainUILayer.h
//  minGameTest
//
//  Created by 马 英臣 on 13-8-20.
//
//

#ifndef minGameTest_MainUILayer_h
#define minGameTest_MainUILayer_h


#include "cocos2d.h"
#include "cocos-ext.h"
#include "UIManager.h"
#include "chess/data/ChessDataVO.h"
#include "ChessLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MainUILayer:
public BaseLayer,
public cocos2d::extension::CCBSelectorResolver,
public cocos2d::extension::CCBMemberVariableAssigner,
public NodeLoaderListener

{   
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainUILayer, create);     
      
    MainUILayer();    
    virtual ~MainUILayer();        
    virtual void onEnter();
    virtual void onExit();    
    virtual bool init();
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object * pTarget, const char * pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Object * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(Object * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
    virtual bool onAssignCCBCustomProperty(Object* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
    virtual void onNodeLoaded(cocos2d::Node * node, NodeLoader * nodeLoader);
                   
    void onClickReStart(cocos2d::Object * sender, Control::EventType pControlEvent);
    void onClickStart(cocos2d::Object * sender, Control::EventType pControlEvent);
    
    virtual bool ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);   
        
private:    
    
    LabelTTF* txt_hisScorces;
    LabelTTF* txt_scorces;
    Node* drawNode;
    ControlButton* btn_restart;
    ControlButton* btn_start;
    
    ChessLayer* chess;//棋局对象
    ChessDataVO* chessData;//当前棋局数据
    
};







#endif
