//
//  StepVO.h
//  minGameTest
//
//  Created by 马 英臣 on 13-10-11.
//小球数据

#ifndef minGameTest_StepVO_h
#define minGameTest_StepVO_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BaseDataVO.h"

//编号位置
struct GPoint{
    int lin=0;
    int row=0;
};

USING_NS_CC;
USING_NS_CC_EXT;

class StepVO :public BaseDataVO{
public:
    
    //舞台左下角开始，行列
    StepVO(GPoint* pt){//pt从1开始
        point=pt;
        valueH=0.0f;
        valueG=0.0f;        
        parent=NULL;
        
        isWalkAble=true;
        
        linValue=10;//横行通行值
        rowValue=10;//纵向通行值
        skewValue=14;//斜向通行值
    };
    virtual ~StepVO(){
        //delete point;
    };    
    
    //行列位置
    GPoint* point;
    //用int主要是为了提高效率；默认每步为10
    int valueH;//估算值
    int valueG;//当前走过步长值
    int getValueF(){return valueH+valueG;}
    
    bool isWalkAble;//是否可通行
    
    int linValue;//横行通行值
    int rowValue;//纵向通行值
    int skewValue;//斜向通行值
    
    StepVO* parent;
    
    
    
        
private:    
    
    
};


#endif
