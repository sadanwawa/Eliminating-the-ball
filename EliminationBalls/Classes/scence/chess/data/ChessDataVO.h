//
//  ChessDataVO.h
//  minGameTest
//
//  Created by 马 英臣 on 13-9-2.
//chess对象数据管理

#ifndef minGameTest_ChessDataVO_h
#define minGameTest_ChessDataVO_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BallVO.h"

USING_NS_CC;
USING_NS_CC_EXT;

//棋盘节点信息
struct PosVO{
    int mId=0;//编号
    int lin=0;//行
    int row=0;//列
    Point point=Point(0,0);
    bool isBall=false;//是否有球    
    BallVO* ballVO=NULL;    
};

class ChessDataVO :public BaseDataVO{
public:
    ChessDataVO(int lin,int row,float gra);
    virtual ~ChessDataVO();
    inline int getLin(){return _lin;};
    inline int getRow(){return _row;};
    inline float getGra(){return _gra;};    
    inline float getWidth(){return _lin*_gra;};
    inline float getHeight(){return _row*_gra;};    
    inline float getLineWidth(){return _lineWidth;};
    
    Color4B getBorderColor(){return _borderColor;};
        
    std::vector<PosVO*> getPosVoVec(){return _PosVOVec;};
    
    
    PosVO* getRandomEmptyPosVO();//随机取得空的位置数据
    PosVO* getPosVOByIndex(int index);//根据编号取得位置数据
    
    std::vector<int> getReadyBallsVec(){return _readyBallsVec;};
    
    void createNewBalls();
    
    std::vector<int> getCreateBallsVec(){return _createBallsVec;};
    
    void updataPosVO(PosVO*vo,int ballType);//更新位置数据
    
    inline int getCurrEmptyNum(){return _currEmptyNum;};//当前空节点数
        
private:
    
    PosVO* getEmptyPosVOByIndex(int index);//取得第几个空位置；0,1,2...
    
    
    void initPosVOs();//初始化节点数据
    void clearPosVOs();//清除节点数据
    //添加节点
    void addPosVO(int mid);
    
    int _lin;//行
    int _row;//列
    float _gra;//间隔
    
    float _lineWidth;
    
    Color4B _borderColor;
        
    std::vector<PosVO*> _PosVOVec;//所有节点数据
    
    
    //随机一种小球
    int getColorByRandom();
    //随机一个位置
    int getPosByRandom();
            
    std::vector<int> _readyBallsVec;//预备小球数组
    
    std::vector<int> _createBallsVec;//放入棋盘小球数组
        
    std::vector<int> _BallsTypeVec;//小球池子

    std::vector<int> _emptyPosVec;//空节点数组
    
    void checkAllEmptyPos();//选出所有空节点    

    int _currEmptyNum;//当前空节点数
    
    int _readyNum;//备选区小球个数
    int _createNum;//每次生成小球个数
    
    void initReadyBalls();//初始化备选区小球类型

};


#endif
