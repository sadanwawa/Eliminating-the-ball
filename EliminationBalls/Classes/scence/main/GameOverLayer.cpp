//
//  GameOverLayer.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-10-18.
//
//

#include "GameOverLayer.h"
#include "ChessLayer.h"
#include "GlobalUtil.h"
#include "ParticaleEffect.h"
#include "StaticConstant.h"
#include "EditBoxLayer.h"

GameOverLayer::GameOverLayer():
inputArea(NULL),
btn_ok(NULL)
{
    
}
GameOverLayer::~GameOverLayer(){
    CCLOG("GameOverLayer删除。");
    CC_SAFE_RELEASE(inputArea);
    CC_SAFE_RELEASE(btn_ok);
}
//执行顺序构造函数->init->onNodeLoaded->(addchild)->onEnter
bool GameOverLayer::init(){
    if(!BaseLayer::init()){
        return false;
    }    
    return true;
}

void GameOverLayer::onEnter(){
    BaseLayer::onEnter();
    this->setTouchEnabled(true);
    Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this,-128,true);
    btn_ok->setTouchPriority(-129);
        
    //Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(,-1,true);
    //Director::getInstance()->getTouchDispatcher()->addAndResetTouchDelegate(btn_ok,-1);
}
void GameOverLayer::onExit(){
    BaseLayer::onExit();
    Director::getInstance()->getTouchDispatcher()->removeDelegate(this);
    Director::getInstance()->getTouchDispatcher()->removeDelegate(btn_ok);
}

SEL_MenuHandler GameOverLayer::onResolveCCBCCMenuItemSelector(cocos2d::Object * pTarget, const char * pSelectorName){
    //菜单事件    
    return NULL;
}
Control::Handler GameOverLayer::onResolveCCBCCControlSelector(cocos2d::Object * pTarget, const char * pSelectorName){
    //按钮事件
     CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickOk", GameOverLayer::onClickOk);   
    return NULL;
}
bool GameOverLayer::onAssignCCBMemberVariable(cocos2d::Object * pTarget, const char * pMemberVariableName, cocos2d::Node * pNode){
    //显示对象    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "inputArea", Node*,inputArea);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btn_ok", ControlButton*,btn_ok);
    return false;
}
bool GameOverLayer::onAssignCCBCustomProperty(Object* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue){
    return false;
}
void GameOverLayer::onNodeLoaded(cocos2d::Node * node, cocos2d::extension::NodeLoader * nodeLoader){
    
}

bool GameOverLayer::ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){   
    //判断自定义触摸逻辑  如果找到目标并不再继续响应 return true;
    if(BaseLayer::ccTouchBegan(pTouch, pEvent)){
               
        return true;
    }
    //return true;
    
    //没有找到目标 调用BaseLayer::ccTouchBegan(pTouch, pEvent) 继续响应;
    return false;
}

void GameOverLayer::updataUI(BaseDataVO* datavo){
    _datavo=datavo;
    EditBoxLayer* layer=new EditBoxLayer();
    inputArea->addChild(layer);
    layer->release();
}

void GameOverLayer::onClickOk(cocos2d::Object * sender, Control::EventType pControlEvent){   
    UIManager::Instance()->removeSingleLayerByNode(this);
    //写入本地数据
    
    //当前积分列表
    UIManager::Instance()->addPopLayer(CCBI::ui_scorceslist);
    UIManager::Instance()->openSinglePopLayer();
    
}
