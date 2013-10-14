//
//  ChessLayer.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-8-20.
//
//

#include "ChessLayer.h"
#include "StaticConstant.h"
#include "DataFormatUtil.h"
#include "AStarModel.h"
#include "ParticaleEffect.h"

ChessLayer::ChessLayer()
{    
    chessBoard=NULL;
    chessBalls=NULL;
    chessEffect=NULL;
    
    _startPosVO=NULL;
    _targetPosVO=NULL;
    _moveBall=NULL;
    _isMoving=false;
}
ChessLayer::~ChessLayer(){
    CCLOG("ChessLayer删除。");    
    CC_SAFE_RELEASE(chessBoard);
    CC_SAFE_RELEASE(chessBalls);
    CC_SAFE_RELEASE(chessEffect);
}

bool ChessLayer::init(){
    if(!BaseLayer::init()){
        return false;
    }    
    return true;
}

void ChessLayer::initData(ChessDataVO*vo){    
    _chessDataVO=vo;
    this->setContentSize(Size(_chessDataVO->getWidth(),_chessDataVO->getHeight()));
}

void ChessLayer::onEnter(){
    BaseLayer::onEnter();
    //棋盘
    if(!chessBoard){
        chessBoard=ChessBoardLayer::create();
        chessBoard->initData(_chessDataVO);
        this->addChild(chessBoard);
    }
    //棋子
    if(!chessBalls){
        chessBalls=Node::create();
        this->addChild(chessBalls);
    }
    //特效
    if(!chessEffect){
        chessEffect=Node::create();
        this->addChild(chessEffect);
    }
    this->setTouchEnabled(true);  
}

void ChessLayer::onExit(){
    BaseLayer::onExit();    
   
}

bool ChessLayer::ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){
    //判断自定义触摸逻辑  如果找到目标并不再继续响应 return true;
    if(BaseLayer::ccTouchBegan(pTouch, pEvent)){
        if(_isMoving)return true;
        //表示点击到当前对象
        //根据pTouch取得当前位置数据；
        PosVO* posvo=_chessDataVO->getPosVOByTouch(chessBalls, pTouch);
        if(posvo->isBall){//有球
               //更新小球
            std::string tag=POP_TAG::tag_chessball+DataFormatUtil::toString(posvo->mId);
            BallLayer* ball=dynamic_cast<BallLayer*>(UIManager::Instance()->getLayerByType(posvo->ballVO->getPlist(),tag));
            return ball->ccTouchBegan(pTouch, pEvent);
        }else{//当前点击位置为空            
            //有选中小球
            if(_chessDataVO->getCurrSelectId()!=-1){
                
                
                //搜索最短路径
                //起始点
                PosVO* currPosVO =_chessDataVO->getPosVOByIndex(_chessDataVO->getCurrSelectId());
                Point pointA=currPosVO->point;                
                //目标点
                Point pointB=posvo->point;
                CCLOG("起始点:(%f,%f),目标点:(%f,%f)",pointA.x,pointA.y,pointB.x,pointB.y);
                
                //1.取得A＊所有节点数据并更新=======
                Array* allsteps=AStarModel::Instance()->getAllStepVOs();
                CCLOG("leng %d",allsteps->count());
                
                std::vector<PosVO*> posVoVec=_chessDataVO->getPosVoVec();
                int len=posVoVec.size();
                
                for(int i=0;i<len;i++){
                    PosVO* pos=posVoVec[i];
                    StepVO* step=dynamic_cast<StepVO*>(allsteps->objectAtIndex(i));
                    step->isWalkAble=!pos->isBall;
                    step->parent=NULL;
                }
                //==========1end
                
                //2.根据初始位置、目标位置搜索最短路径
                GPoint* gptA=new GPoint();
                GPoint* gptB=new GPoint();
                gptA->lin=currPosVO->lin+1;
                gptA->row=currPosVO->row+1;
                gptB->lin=posvo->lin+1;
                gptB->row=posvo->row+1;                
                bool getPath=AStarModel::Instance()->searchPathByPoint(gptA,gptB);
                delete gptA;
                delete gptB;
                //=========2end
                
                if(!getPath){return true;};
                
                //3.取得最短路径 并转换为地图坐标                
                std::vector<Point> pointsVec;
                pointsVec.clear();
                Array* paths=AStarModel::Instance()->getMovePath();                    
                //路径转换为坐标
                int plen=paths->count();
                for(int i=0;i<plen;i++){                        
                    StepVO*vo=dynamic_cast<StepVO*>(paths->objectAtIndex(i));
                    //取得地图位置编号0,1,2...                        
                    int mId=_chessDataVO->getMIdByLinAndRow(vo->point->lin-1,vo->point->row-1);                        
                    PosVO* pvo=_chessDataVO->getPosVOByIndex(mId);                        
                    pointsVec.push_back(pvo->point);                                              
                }                              
                //=========3end
                
                //4.根据路径数组移动小球
                std::string tag=POP_TAG::tag_chessball+DataFormatUtil::toString(currPosVO->mId);
                BallLayer* ball=dynamic_cast<BallLayer*>(UIManager::Instance()->getLayerByType(currPosVO->ballVO->getPlist(),tag));
                
                
                //整理数据
                _startPosVO=currPosVO;
                _targetPosVO=posvo;//记录目标位置
                _moveBall=ball;//记录当前小球                
                tag=POP_TAG::tag_selectball;
                _moveFire=dynamic_cast<ParticaleEffect*>(UIManager::Instance()->getLayerByType(CCBI::eff_selectball,tag));
                
                moveBallToTarget(ball,pointsVec);
                
            }           
        }
        
        return true;
    }
    //return true;
    
    //没有找到目标 调用BaseLayer::ccTouchBegan(pTouch, pEvent) 继续响应;
    return false;
}

void ChessLayer::createNewBalls(){
    
}

void ChessLayer::moveBallToTarget(BallLayer*ball, std::vector<Point> paths){
    
    int len=paths.size();
    float delayt=0;
    float stept=0.4;
    for(int i=0;i<len;i++){
        FiniteTimeAction*  action=NULL;        
        if(i==len-1){
            action = Sequence::create(
                                      DelayTime::create(delayt),
                                      MoveTo::create(stept,paths[i]),
                                      //此处可随时更新初始搜索位置
                                      CallFunc::create( CC_CALLBACK_0(ChessLayer::updataBallToTarget,this)),
                                      NULL);
        }else{
            action = Sequence::create(
                                                         DelayTime::create(delayt),
                                                         MoveTo::create(stept,paths[i]),                                                         
                                                         NULL);
        }            
        ball->runAction(action);
        delayt+=stept;         
    }
    
    //控制整体速度
//    Director::sharedDirector()->getScheduler()->setTimeScale(0.5);
//    
//    //单独控制速度
//    CCScheduler* sched1 = new CCScheduler();
//    defaultScheduler->scheduleUpdateForTarget(sched1, 0, false);
//    
//    //Create a new ActionManager, and link it to the new scheudler
//    actionManager1 = new CCActionManager();
//    sched1->scheduleUpdateForTarget(actionManager1, 0, false);
//    sched1->setTimeScale(0.5);
    
    //🔥跟随小球
    _isMoving=true;
    this->schedule(schedule_selector(ChessLayer::onTimeMoveWithBall),((float)1.0/60));//渲染
}

void ChessLayer::updataBallToTarget(){
            
    //起始位置
    PosVO* currPosVO =_chessDataVO->getPosVOByIndex(_chessDataVO->getCurrSelectId());
    
    //目标位置
    _targetPosVO->isBall=true;
    _targetPosVO->ballVO=currPosVO->ballVO;    
    
    //改旗易帜  tag 编号    
    std::string tag=POP_TAG::tag_chessball+DataFormatUtil::toString(currPosVO->mId);
    std::string tagTo=POP_TAG::tag_chessball+DataFormatUtil::toString(_targetPosVO->mId);
    UIManager::Instance()->replaceLayerTag(currPosVO->ballVO->getPlist(), tag, tagTo);        
    _moveBall->updataMid(_targetPosVO->mId);
        
    currPosVO->isBall=false;
    currPosVO->ballVO=NULL;
    
    //更新起始位置
    _chessDataVO->setCurrSelectId(_targetPosVO->mId);
    
    //移除事件
    this->unschedule(schedule_selector(ChessLayer::onTimeMoveWithBall));
    _moveBall->stopAllActions();
    _isMoving=false;
}

void ChessLayer::onTimeMoveWithBall(float time){    
    //this 是注册schedule的对象（注意this所指  不同的回调方法中，this所指向对象不一定相同）
    _moveFire->setPosition(_moveBall->getPosition());
   
}
