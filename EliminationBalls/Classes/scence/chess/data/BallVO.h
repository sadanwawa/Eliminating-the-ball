//
//  BallVO.h
//  minGameTest
//
//  Created by 马 英臣 on 13-9-2.
//小球数据

#ifndef minGameTest_BallVO_h
#define minGameTest_BallVO_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BaseDataVO.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BallVO :public BaseDataVO{
public:
    BallVO(int type){
        _state=0;
        _type=type;
    };
    virtual ~BallVO(){
       
    };    
    
private:    
    int _type;//小球类型
    
    int _state;//小球当前状态；
          
};


#endif
