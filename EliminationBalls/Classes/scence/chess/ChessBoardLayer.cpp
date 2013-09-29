//
//  ChessBoardLayer.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-8-20.
//
//

#include "ChessBoardLayer.h"

ChessBoardLayer::ChessBoardLayer()
{
    _chessDataVO=NULL;
}
ChessBoardLayer::~ChessBoardLayer(){
    
}

bool ChessBoardLayer::init(){
    if(!BaseLayer::init()){
        return false;
    }    
    return true;
}

void ChessBoardLayer::onEnter(){
    BaseLayer::onEnter();    
}
void ChessBoardLayer::onExit(){
    BaseLayer::onExit();    
   
}

void ChessBoardLayer::initData(ChessDataVO* vo){
    _chessDataVO=vo;
}

void ChessBoardLayer::draw(){
    Layer::draw();    
    glLineWidth(_chessDataVO->getLineWidth());//线宽    
    Color4B d=_chessDataVO->getBorderColor();
    DrawPrimitives::setDrawColor4B(d.r,d.g,d.b,d.a);//颜色
    for(int i=0;i<=this->_chessDataVO->getLin();i++){
       DrawPrimitives::drawLine(Point(0,_chessDataVO->getGra()*i), Point(_chessDataVO->getRow()*_chessDataVO->getGra(),_chessDataVO->getGra()*i));
    }   
    for(int j=0;j<=this->_chessDataVO->getRow();j++){
        DrawPrimitives::drawLine(Point(_chessDataVO->getGra()*j,0), Point(_chessDataVO->getGra()*j,_chessDataVO->getGra()*_chessDataVO->getLin()));
    }
}
