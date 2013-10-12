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
#include "TouchUtil.h"
#include "DataFormatUtil.h"
#include "StaticConstant.h"
#include "AStarModel.h"

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
    //this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//ALL_AT_ONCE
    this->setTouchEnabled(true);
    Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
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
    if(chessData->getCurrEmptyNum()<1)return;
    //消除准备区小球
    clearReadyBalls();
    //更新小球数据
    chessData->createNewBalls();
    //更新准备区小球
    initReadyBalls();   
    //放入棋盘小球
    initCreateBalls();
}

void MainUILayer::clearReadyBalls(){//清除备选区小球
    
    std::vector<int> readyVec=chessData->getReadyBallsVec();//新的准备区小球数据
    int len=readyVec.size();
    std::string tag="";
    for(int i=0;i<len;i++){
        std::string ballPlist=GlobalUtil::Instance()->getPlistByBallType(readyVec[i]);
        tag=POP_TAG::tag_readyball;
        UIManager::Instance()->removeLayerByType(ballPlist,tag);
    }

}

void MainUILayer::initReadyBalls(){
    std::vector<int> readyballsVec=chessData->getReadyBallsVec();
    int len=readyballsVec.size();
    std::string tag="";
    for(int i=0;i<len;i++){
        std::string ballPlist=GlobalUtil::Instance()->getPlistByBallType(readyballsVec[i]);
        Point point=Point(readyArea->getContentSize().width-i*38-38/2,38/2);        
        tag=POP_TAG::tag_readyball;        
        BallVO* ballVO=new BallVO(readyballsVec[i]);
        ballVO->setState(0);
        UIManager::Instance()->addPopLayer(ballPlist,readyArea,0,point.x,point.y,tag,ballVO);
    }
    UIManager::Instance()->openPopLayers(0.1);
}

void MainUILayer::initCreateBalls(){
    std::vector<int> creatVec=chessData->getCreateBallsVec();//新放入棋盘小球数据
    for(int j=0;j<creatVec.size();j++){
                
        std::string ballPlist=GlobalUtil::Instance()->getPlistByBallType(creatVec[j]);
        PosVO* posVO=chessData->getRandomEmptyPosVO();
        BallVO* ballVO=new BallVO(creatVec[j],posVO->mId,ballPlist);
        ballVO->setState(1);
        posVO->ballVO=ballVO;
        posVO->isBall=true;
        
        std::string tag=POP_TAG::tag_chessball+DataFormatUtil::toString(posVO->mId);
        UIManager::Instance()->addPopLayer(ballPlist,chess->getChessNode(),0,posVO->point.x,posVO->point.y,tag,posVO->ballVO);//添加datavo
        
        if(chessData->getCurrEmptyNum()<1){
            //游戏结束；
            break;
        }
        
    }
    UIManager::Instance()->openPopLayers(0.1);    
}

bool MainUILayer::ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){   
    //判断自定义触摸逻辑  如果找到目标并不再继续响应 return true;
    if(BaseLayer::ccTouchBegan(pTouch, pEvent)){
        //表示点击到当前对象
        if(TouchUtil::Instance()->touchNode(chess, pTouch)){
            return chess->ccTouchBegan(pTouch, pEvent);
        }        
    }
    //return true;
    
    //没有找到目标 调用BaseLayer::ccTouchBegan(pTouch, pEvent) 继续响应;
    return false;
}

void MainUILayer::updataUI(BaseDataVO* datavo){
    //棋
    chess=ChessLayer::create();
    chessData=new ChessDataVO(9,9,32);
    chess->initData(chessData);
    drawNode->addChild(chess);
    
    //初始化随机小球
    initReadyBalls();//初始化备选区小球
    
    AStarModel::Instance()->initAStar(9,9);//初始化A*节点数据
    
}

