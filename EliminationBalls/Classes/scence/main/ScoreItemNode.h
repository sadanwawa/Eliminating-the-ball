//
//  ScoreItemNode.h
//  minGameTest
//
//  Created by 马 英臣 on 13-11-06.
//  得分记录 item
//

#ifndef minGameTest_ScoreItemNode_h
#define minGameTest_ScoreItemNode_h


#include "cocos2d.h"
#include "cocos-ext.h"
#include "BaseNode.h"
#include "ScorceVO.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ScoreItemNode:
public BaseNode,
public cocos2d::extension::CCBSelectorResolver,
public cocos2d::extension::CCBMemberVariableAssigner,
public NodeLoaderListener

{   
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ScoreItemNode, create);     
      
    ScoreItemNode();    
    virtual ~ScoreItemNode();
    virtual void onEnter();
    virtual void onExit();
    virtual bool init();
    
    void updataUI(BaseDataVO* datavo=NULL);  
    virtual void onNodeLoaded(cocos2d::Node * node, NodeLoader * nodeLoader);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object * pTarget, const char * pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Object * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(Object * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
    virtual bool onAssignCCBCustomProperty(Object* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
    
    //virtual bool onAssignCCBMemberVariable(cocos2d::Object * pTarget, const char * pMemberVariableName, cocos2d::Node * pNode);
    
    ScorceVO* getDataVO(){return dataVO;};
    
    
    
    
    
private:
    
    LabelTTF* txt_num;
    
    LabelTTF* txt_name;
    
    LabelTTF* txt_scores;
    
    ScorceVO* dataVO;
    
};







#endif
