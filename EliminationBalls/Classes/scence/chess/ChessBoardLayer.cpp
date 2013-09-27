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
    _lin=0;//行
    _row=0;//列
    _gra=0;//间隔
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

void ChessBoardLayer::initData(int lin,int row,float gra){
    _lin=lin;
    _row=row;
    _gra=gra;
}

void ChessBoardLayer::draw(){
    Layer::draw();    
    glLineWidth(3.0f);//线宽
    DrawPrimitives::setDrawColor4B(155,0,0,155);//颜色
    for(int i=0;i<=this->_lin;i++){
       DrawPrimitives::drawLine(Point(0,_gra*i), Point(_row*_gra,_gra*i));
    }   
    for(int j=0;j<=this->_lin;j++){
        DrawPrimitives::drawLine(Point(_gra*j,0), Point(_gra*j,_gra*_lin));
    }
}
