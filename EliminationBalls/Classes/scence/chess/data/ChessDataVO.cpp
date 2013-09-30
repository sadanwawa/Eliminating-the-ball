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
    //小球池子
    _BallsTypeVec={1,2,3,4,5,6,7,8,9};
    //备选区小球个数
    _readyNum=3;    
    _readyBallsVec.clear();    
    initPosVOs();//初始化节点数据
    
    //初始化被选区小球数据
    initReadyBalls();
    
};
ChessDataVO::~ChessDataVO(){
    
};

void ChessDataVO::initReadyBalls(){    
    for(int i=0;i<_readyNum;i++){
        int randomColor=getColorByRandom();
        _readyBallsVec.push_back(randomColor);
    }    
}

void ChessDataVO::initPosVOs(){
    clearPosVOs();
    int len=_lin*_row;
    for(int i=0;i<len;i++){        
        addPosVO(i);
    }
    _currEmptyNum=len;
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

//随机一种小球
int ChessDataVO::getColorByRandom(){
    int len=_BallsTypeVec.size();
    int index=(CCRANDOM_0_1()*len);    
    return _BallsTypeVec[index];
}

//随机一个位置
int ChessDataVO::getPosByRandom(){    
    int targetIndex=(CCRANDOM_0_1()*_currEmptyNum);//目标索引
    int index=0;
    int len=_PosVOVec.size();    
    for(int i=0;i<len;i++){
        if(!_PosVOVec[i]->ballVO){
            index++;
            if(index==targetIndex){
                _currEmptyNum++;
                return _PosVOVec[i]->mId;
            }
        }
    }        
    return 0;
}

void ChessDataVO::checkAllEmptyPos(){//选出所有空节点
    int len=_PosVOVec.size();
    _emptyPosVec.clear();
    for(int i=0;i<len;i++){
        if(!_PosVOVec[i]->ballVO){
            _emptyPosVec.push_back(_PosVOVec[i]->mId);
        }        
    }    
}



