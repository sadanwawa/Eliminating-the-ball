//
//  ScorcesModel.h
//  minGameTest
//
//  Created by 马 英臣 on 13-10-18.
//  积分管理：本地积分列表   服务器积分列表
//

#ifndef minGameTest_ScorcesModel_h
#define minGameTest_ScorcesModel_h


#include "cocos2d.h"
#include "Singleton.h"
#include "cocos-ext.h"
#include "ScorceVO.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ScorcesModel : public Singleton<ScorcesModel>, public Object
{
public:
    ScorcesModel(){
        totalNum=20;//默认保存20条记录
        
        initTopScores=100;//默认最高分100
        currTopScores=0;
        _allScoreVOs=NULL;
    };
    ~ScorcesModel(){
        
    };
    
    virtual bool initialize();
    
    //更新数据
    void initData();
    
    void initGlobleData();
    
    Array* getScoreVOs(){
        return _allScoreVOs;
    }
    
    int getTotalNum(){
        return totalNum;
    }
    
    //插入数据记录
    void insertRecord(std::string name,int scorce);
    
    ScorceVO* getScorceVOByIndex(int index);
    
    int getCurrTopScores(){return currTopScores;};
    
    void clearData();
   
private:
    
    //积分列表
    Array* _allScoreVOs;
    //积分榜存储记录条数
    int totalNum;
    
    int currTopScores;
    
    int initTopScores;
    
};

#endif
