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
    _lin=9;//行
    _row=9;//列
    _gra=30;
    _width=300;//宽
    _height=300;//高
    chessBoard=NULL;
    chessBalls=NULL;
    chessEffect=NULL;
    this->setContentSize(Size(_row*_gra,_lin*_gra));
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

void ChessLayer::onEnter(){
    BaseLayer::onEnter();
    //棋盘
    if(!chessBoard){
        chessBoard=ChessBoardLayer::create();
        chessBoard->initData(9, 9, 30);
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
