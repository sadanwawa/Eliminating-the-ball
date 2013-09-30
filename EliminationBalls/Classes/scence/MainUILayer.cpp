//
//  MainUILayer.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-8-20.
//
//

#include "MainUILayer.h"
#include "ChessLayer.h"
#include "GlobalUtil.h"

MainUILayer::MainUILayer()
:txt_hisScorces(NULL),
txt_scorces(NULL),
readyArea(NULL),
drawNode(NULL),
btn_restart(NULL),
btn_start(NULL)
{
    chessData=NULL;
    chess=NULL;
}
MainUILayer::~MainUILayer(){
    CCLOG("MainUILayer删除。");    
    CC_SAFE_RELEASE(txt_hisScorces);
    CC_SAFE_RELEASE(txt_scorces);
    CC_SAFE_RELEASE(readyArea);
    CC_SAFE_RELEASE(drawNode);
    CC_SAFE_RELEASE(btn_restart);
    CC_SAFE_RELEASE(btn_start);
    if(chessData){delete chessData;chessData=NULL;}
}
//执行顺序构造函数->init->onNodeLoaded->(addchild)->onEnter
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
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "readyArea", Node*,readyArea);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node", Node*,drawNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btn_restart", ControlButton*, btn_restart);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btn_start", ControlButton*, btn_start);    
    return false;
}
bool MainUILayer::onAssignCCBCustomProperty(Object* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue){
    
    return false;
}
void MainUILayer::onNodeLoaded(cocos2d::Node * node, cocos2d::extension::NodeLoader * nodeLoader){
    
}

void MainUILayer::onClickReStart(cocos2d::Object * sender, Control::EventType pControlEvent){
    
    
}
void MainUILayer::onClickStart(cocos2d::Object * sender, Control::EventType pControlEvent){
    //随机生成小球
    initReadyBalls();
    return;
    int len=chessData->getPosVoVec().size();
    for(int i=0;i<len;i++){
        Point point=chessData->getPosVoVec()[i]->point;        
        UIManager::Instance()->addPopLayer(CCBI::ui_ball_blue,chess,1,point.x,point.y);
    }
    UIManager::Instance()->openPopLayers(0.1);
}

void MainUILayer::initReadyBalls(){
    std::vector<int> readyballsVec=chessData->getReadyBallsVec();
    int len=readyballsVec.size();
    for(int i=0;i<len;i++){
        std::string ballPlist=GlobalUtil::Instance()->getPlistByBallType(readyballsVec[i]);
        Point point=Point(readyArea->getPositionX()+readyArea->getContentSize().width-i*38-38/2,readyArea->getPositionY()+38/2);
        UIManager::Instance()->addPopLayer(ballPlist,this,0,point.x,point.y);
    }
    //UIManager::Instance()->openPopLayers(0.1);
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

void MainUILayer::updataUI(){
    //棋
    chess=ChessLayer::create();
    chessData=new ChessDataVO(9,9,32);
    chess->initData(chessData);
    drawNode->addChild(chess);
    
    //初始化随机小球
    initReadyBalls();//初始化备选区小球
}

