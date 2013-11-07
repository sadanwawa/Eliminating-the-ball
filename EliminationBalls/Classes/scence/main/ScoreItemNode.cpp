//
//  ScoreItemNode.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-11-06.
//
//

#include "ScoreItemNode.h"
#include "DataFormatUtil.h"

ScoreItemNode::ScoreItemNode():
txt_name(NULL),
txt_num(NULL),
txt_scores(NULL)
{
    dataVO=NULL;
}
ScoreItemNode::~ScoreItemNode(){
    CCLOG("ScoreItemNode删除。");
    CC_SAFE_RELEASE(txt_num);
    CC_SAFE_RELEASE(txt_name);
    CC_SAFE_RELEASE(txt_scores);
}

void ScoreItemNode::onEnter(){
    BaseNode::onEnter();
}
void ScoreItemNode::onExit(){
    BaseNode::onExit();
}

bool ScoreItemNode::init(){
    if(!BaseNode::init()){
        return false;
    }
    return true;
}

void ScoreItemNode::onNodeLoaded(cocos2d::Node * node, cocos2d::extension::NodeLoader * nodeLoader){
    
    
}

void ScoreItemNode::updataUI(BaseDataVO* datavo){
    if(datavo==NULL||!datavo)return;
    dataVO=(ScorceVO*)(datavo);
    txt_num->setString(DataFormatUtil::toString(dataVO->mid).c_str());
    txt_name->setString(dataVO->name.c_str());
    txt_scores->setString(DataFormatUtil::toString(dataVO->scorces).c_str());
}

bool ScoreItemNode::onAssignCCBMemberVariable(cocos2d::Object * pTarget, const char * pMemberVariableName, cocos2d::Node * pNode){
    //显示对象 LabelTTF* txt_num;
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txt_num", LabelTTF*,txt_num);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txt_name", LabelTTF*,txt_name);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txt_scores", LabelTTF*,txt_scores);
    
    return false;
}

SEL_MenuHandler ScoreItemNode::onResolveCCBCCMenuItemSelector(Object * pTarget, const char * pSelectorName){
    
    return NULL;
}
Control::Handler ScoreItemNode::onResolveCCBCCControlSelector(Object * pTarget, const char * pSelectorName){
    
    return NULL;
}

bool ScoreItemNode::onAssignCCBCustomProperty(Object* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue){
    
    return true;
}

