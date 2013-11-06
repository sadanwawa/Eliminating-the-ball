//
//  ScorcesListLayer.h
//  minGameTest
//
//  Created by 马 英臣 on 13-11-05.
//
//

#ifndef minGameTest_ScorcesListLayer_h
#define minGameTest_ScorcesListLayer_h


#include "cocos2d.h"
#include "cocos-ext.h"
#include "UIManager.h"
#include "ScorceVO.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ScorcesListLayer:
public BaseLayer,
public cocos2d::extension::CCBSelectorResolver,
public cocos2d::extension::CCBMemberVariableAssigner,
public NodeLoaderListener
{   
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ScorcesListLayer, create);
      
    ScorcesListLayer();    
    virtual ~ScorcesListLayer();        
    virtual void onEnter();
    virtual void onExit();    
    virtual bool init();
    void updataUI(BaseDataVO* datavo=NULL);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object * pTarget, const char * pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Object * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(Object * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
    virtual bool onAssignCCBCustomProperty(Object* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
    
    void onClickClose(cocos2d::Object * sender, Control::EventType pControlEvent);
    virtual void onNodeLoaded(cocos2d::Node * node, NodeLoader * nodeLoader);
    
    virtual bool ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);   
    
    ScorceVO* getDataVO(){return dynamic_cast<ScorceVO*>(_datavo);};
            
private:    

    BaseDataVO* _datavo;
    
    Node* listArea;
    
    ControlButton* btn_close;
        
};







#endif
