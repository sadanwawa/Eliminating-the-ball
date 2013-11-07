//
//  ScorcesListLayer.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-11-05.
//
//

#include "ScorcesListLayer.h"
#include "ChessLayer.h"
#include "GlobalUtil.h"
#include "ParticaleEffect.h"
#include "StaticConstant.h"
#include "TableViewLayer.h"

ScorcesListLayer::ScorcesListLayer():
listArea(NULL),
btn_close(NULL)
{
    
}
ScorcesListLayer::~ScorcesListLayer(){
    CCLOG("ScorcesListLayer删除。");
    CC_SAFE_RELEASE(listArea);
    CC_SAFE_RELEASE(btn_close);
    UIManager::Instance()->removeLayersByType(CCBI::ui_scoreitem);
}
//执行顺序构造函数->init->onNodeLoaded->(addchild)->onEnter
bool ScorcesListLayer::init(){
    if(!BaseLayer::init()){
        return false;
    }    
    return true;
}

void ScorcesListLayer::onEnter(){
    BaseLayer::onEnter();
    this->setTouchEnabled(true);
    Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this,-128,true);
    btn_close->setTouchPriority(-130);
        
    //Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(,-1,true);
    //Director::getInstance()->getTouchDispatcher()->addAndResetTouchDelegate(btn_ok,-1);
}
void ScorcesListLayer::onExit(){
    BaseLayer::onExit();
    Director::getInstance()->getTouchDispatcher()->removeDelegate(this);
    Director::getInstance()->getTouchDispatcher()->removeDelegate(btn_close);
}

SEL_MenuHandler ScorcesListLayer::onResolveCCBCCMenuItemSelector(cocos2d::Object * pTarget, const char * pSelectorName){
    //菜单事件    
    return NULL;
}
Control::Handler ScorcesListLayer::onResolveCCBCCControlSelector(cocos2d::Object * pTarget, const char * pSelectorName){
    //按钮事件
     CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickClose", ScorcesListLayer::onClickClose);   
    return NULL;
}
bool ScorcesListLayer::onAssignCCBMemberVariable(cocos2d::Object * pTarget, const char * pMemberVariableName, cocos2d::Node * pNode){
    //显示对象    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "listArea", Node*,listArea);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btn_close", ControlButton*,btn_close);
    return false;
}
bool ScorcesListLayer::onAssignCCBCustomProperty(Object* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue){
    return false;
}
void ScorcesListLayer::onNodeLoaded(cocos2d::Node * node, cocos2d::extension::NodeLoader * nodeLoader){
    
}

bool ScorcesListLayer::ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){   
    //判断自定义触摸逻辑  如果找到目标并不再继续响应 return true;
    if(BaseLayer::ccTouchBegan(pTouch, pEvent)){
               
        return true;
    }
    //return true;
    
    //没有找到目标 调用BaseLayer::ccTouchBegan(pTouch, pEvent) 继续响应;
    return false;
}

void ScorcesListLayer::updataUI(BaseDataVO* datavo){
    _datavo=datavo;

    Size winSize = Director::getInstance()->getWinSize();
    //TableViewLayer* layer=TableViewLayer::create();
    TableViewLayer* layer=new TableViewLayer();
    listArea->addChild(layer);
    layer->release();
}

void ScorcesListLayer::onClickClose(cocos2d::Object * sender, Control::EventType pControlEvent){
    UIManager::Instance()->removeSingleLayerByNode(this);
    
    //当前积分列表
    
    
    
    
}
