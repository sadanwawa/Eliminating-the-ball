//
//  ChessDataVO.h
//  minGameTest
//
//  Created by 马 英臣 on 13-9-2.
//

#include "ChessDataVO.h"

ChessDataVO::ChessDataVO(int lin,int row,float gra){
    _lin=lin;//行
    _row=row;//列
    _gra=gra;
    
    //棋盘线宽
    _lineWidth=3.0f;
    //棋盘颜色
    _borderColor=Color4B(125,0,0,125);
    
    initPosVOs();//初始化节点数据
    
};
ChessDataVO::~ChessDataVO(){
    
};

void ChessDataVO::initPosVOs(){
    clearPosVOs();
    int len=_lin*_row;
    for(int i=0;i<len;i++){        
        addPosVO(i);
    }    
}

void ChessDataVO::clearPosVOs(){
    int len=_PosVOVec.size();
    for(int i=0;i<len;i++){
        delete _PosVOVec[i];
    }
    _PosVOVec.clear();
}

void ChessDataVO::addPosVO(int i){
    PosVO* posvo=new PosVO();
    posvo->mId=i;
    int lin=i/_row;//行
    int row=i%_row;//列
    posvo->lin=lin;
    posvo->row=row;
    posvo->point=Point(row*_gra+_gra/2,lin*_gra+_gra/2);
    _PosVOVec.push_back(posvo);
};