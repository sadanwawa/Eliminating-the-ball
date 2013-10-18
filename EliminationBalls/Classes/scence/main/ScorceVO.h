//
//  ScorceVO.h
//  minGameTest
//
//  Created by 马 英臣 on 13-10-18.
//得分记录

#ifndef minGameTest_ScorceVO_h
#define minGameTest_ScorceVO_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BaseDataVO.h"


USING_NS_CC;
USING_NS_CC_EXT;

class ScorceVO :public BaseDataVO{
public:
    
    //舞台左下角开始，行列
    ScorceVO(){//pt从1开始
        mid=0;
        scorces=0;
        name="";
    };
    virtual ~ScorceVO(){
       
    };    
    
    int mid;//记录编号／当前名次
    std::string name;//玩家名字
    int scorces;//当前得分
    
    
    
    
private:    
    
    
};


#endif
