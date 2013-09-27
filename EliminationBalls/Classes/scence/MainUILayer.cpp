//
//  MainUILayer.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-8-20.
//
//

#include "MainUILayer.h"
#include "ChessLayer.h"

MainUILayer::MainUILayer()
:txt_hisScorces(NULL),
txt_scorces(NULL),
drawNode(NULL),
btn_restart(NULL),
btn_start(NULL)
{
    chessData=NULL;
}
MainUILayer::~MainUILayer(){
    CCLOG("MainUILayer删除。");    
    CC_SAFE_RELEASE(txt_hisScorces);
    CC_SAFE_RELEASE(txt_scorces);
    CC_SAFE_RELEASE(drawNode);
    CC_SAFE_RELEASE(btn_restart);
    CC_SAFE_RELEASE(btn_start);
    if(chessData){delete chessData;chessData=NULL;}
}

bool MainUILayer::init(){
    if(!BaseLayer::init()){
        return false;
    }    
    return true;
}

void MainUILayer::onEnter(){
    BaseLayer::onEnter();    
//    this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);//ALL_AT_ONCE    
//    Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this,100,true);
}
void MainUILayer::onExit(){
    BaseLayer::onExit();    
   
}

SEL_MenuHandler MainUILayer::onResolveCCBCCMenuItemSelector(cocos2d::Object * pTarget, const char * pSelectorName){
    //菜单事件    
    return NULL;
}
Control::Handler MainUILayer::onResolveCCBCCControlSelector(cocos2d::Object * pTarget, const char * pSelectorName){
    //按钮事件
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickReStart", MainUILayer::onClickReStart);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickStart", MainUILayer::onClickStart);   
    return NULL;
}
bool MainUILayer::onAssignCCBMemberVariable(cocos2d::Object * pTarget, const char * pMemberVariableName, cocos2d::Node * pNode){
    //显示对象    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txt_hisScorces", LabelTTF*, txt_hisScorces);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txt_scorces", LabelTTF*, txt_scorces);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node", Node*,drawNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btn_restart", ControlButton*, btn_restart);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btn_start", ControlButton*, btn_start);    
    return false;
}
bool MainUILayer::onAssignCCBCustomProperty(Object* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue){
    
    return false;
}
void MainUILayer::onNodeLoaded(cocos2d::Node * node, cocos2d::extension::NodeLoader * nodeLoader){

    //棋盘
    ChessLayer* chess=ChessLayer::create();
    chessData=new ChessDataVO(9,9,30);
    chess->initData(chessData);    
    drawNode->addChild(chess);

}

void MainUILayer::onClickReStart(cocos2d::Object * sender, Control::EventType pControlEvent){
    
    
}
void MainUILayer::onClickStart(cocos2d::Object * sender, Control::EventType pControlEvent){
    
    //随机生成小球
    
}

bool MainUILayer::ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){   
    //判断自定义触摸逻辑  如果找到目标并不再继续响应 return true;
    if(BaseLayer::ccTouchBegan(pTouch, pEvent)){
        //表示点击到当前对象
        return true;
    }
    //return true;
    
    //没有找到目标 调用BaseLayer::ccTouchBegan(pTouch, pEvent) 继续响应;
    return false;
}
