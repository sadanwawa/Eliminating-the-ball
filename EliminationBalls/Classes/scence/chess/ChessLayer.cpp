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

ChessLayer::ChessLayer()
{    
    chessBoard=NULL;
    chessBalls=NULL;
    chessEffect=NULL;
    
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



