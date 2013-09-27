//
//  ChessLayer.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-8-20.
//
//

#include "ChessLayer.h"

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
    
    //初始化棋盘节点数据
    
    
}

void ChessLayer::onExit(){
    BaseLayer::onExit();    
   
}

bool ChessLayer::ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){   
    //判断自定义触摸逻辑  如果找到目标并不再继续响应 return true;
    if(BaseLayer::ccTouchBegan(pTouch, pEvent)){
        //表示点击到当前对象
        return true;
    }
    //return true;
    
    //没有找到目标 调用BaseLayer::ccTouchBegan(pTouch, pEvent) 继续响应;
    return false;
}
