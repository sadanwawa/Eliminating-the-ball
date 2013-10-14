//
//  ChessDataVO.h
//  minGameTest
//
//  Created by 马 英臣 on 13-9-2.
//

#include "ChessDataVO.h"
#include <time.h>
#include "DataFormatUtil.h"

ChessDataVO::ChessDataVO(int lin,int row,float gra){
    _lin=lin;//行
    _row=row;//列
    _gra=gra;
    _selectId=-1;
    
    //棋盘线宽
    _lineWidth=3.0f;
    //棋盘颜色
    _borderColor=Color4B(125,0,0,125);    
    //小球池子
    _BallsTypeVec={1,2,3,4,5,6,7,8,9};
    //备选区小球个数
    _readyNum=5;
    //每次生成小球个数
    _createNum=3;
    _readyBallsVec.clear();
    _createBallsVec.clear();
    
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
    int index=DataFormatUtil::getRandom(len);
    return _BallsTypeVec[index];
}

//随机一个位置
int ChessDataVO::getPosByRandom(){        
    int targetIndex=DataFormatUtil::getRandom(_currEmptyNum);             
    PosVO* targetPos=getEmptyPosVOByIndex(targetIndex);    
    return targetPos->mId;
}

PosVO* ChessDataVO::getEmptyPosVOByIndex(int targetIndex){
    
    int len=_PosVOVec.size();
    int index=0;
    for(int i=0;i<len;i++){
        if(!_PosVOVec[i]->ballVO){
            if(index==targetIndex){
                _currEmptyNum--;
                return _PosVOVec[i];
            }
            index++;
        }
    }    
    return NULL;
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

//创建新小球
void ChessDataVO::createNewBalls(){
    //_createNum取出等待区小球
    _createBallsVec.clear();
       
    int len=_readyBallsVec.size();
    for(int i=0;i<_createNum;i++){ //缓存数据
        _createBallsVec.push_back(_readyBallsVec[i]);                
    }
    for(int i=_createNum;i<len;i++){//平移数据
        _readyBallsVec[i-_createNum]=_readyBallsVec[i];       
    }
    //随机 种子 设置
    for(int i=_createNum-1;i<len;i++){//生成新数据
        _readyBallsVec[i]=getColorByRandom();
        std::cout<<"新入："<<_readyBallsVec[i]<<std::endl;
        
    }
}

PosVO* ChessDataVO::getRandomEmptyPosVO(){//随机取得空的位置数据    
    if(_currEmptyNum<=1){
        return getEmptyPosVOByIndex(0);
    }
    int pos=getPosByRandom();
    return getPosVOByIndex(pos);          
}

PosVO* ChessDataVO::getPosVOByIndex(int index){
    int len=_PosVOVec.size();
    PosVO* targetVO=NULL;    
    for(int i=0;i<len;i++){
        if(_PosVOVec[i]->mId==index){
            targetVO=_PosVOVec[i];
            return targetVO;
        }
    }
    return targetVO;
}

//根据touch取得当前位置数据
PosVO* ChessDataVO::getPosVOByTouch(Node* node,cocos2d::Touch *pTouch){
    int len=_PosVOVec.size();
    Point point =node->convertTouchToNodeSpace(pTouch);//当前触摸点相对node的位置
    for(int i=0;i<len;i++){        
        PosVO* posvo=_PosVOVec[i];
        if(posvo->point.x+_gra/2>=point.x&&posvo->point.x-_gra/2<=point.x&&posvo->point.y-_gra/2<=point.y&&posvo->point.y+_gra/2>=point.y){
            return _PosVOVec[i];            
        }        
    }    
    return NULL;
}

//根据行列号 取得位置编号
int ChessDataVO::getMIdByLinAndRow(int lin,int row){    
    return  lin*_row+row;
}




void ChessDataVO::updataPosVO(PosVO*vo,int ballType){//更新位置数据


}


