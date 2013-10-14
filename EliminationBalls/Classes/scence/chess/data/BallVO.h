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
#include "GlobalUtil.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BallVO :public BaseDataVO{
public:
    BallVO(int type,int mid=0,std::string plist=""){
        _state=0;
        _select=false;
        _type=type;
        _mid=mid;
        _plist=plist;//GlobalUtil::Instance()->getPlistByBallType(type);
        
    };
    virtual ~BallVO(){
       
    };    
    
    void setState(int state){_state=state;};
    void setSelect(bool boo){_select=boo;};
    
    int getState(){
        return _state;
    }
    
    bool getSelect(){
        return _select;
    }
    
    std::string getPlist(){
        return _plist;
    }
    
    void setId(int mid){
        _mid=mid;
    }
    
    int getId(){
        return _mid;
    }
   
    
private:    
    int _type;//小球类型
    
    int _mid;//小球编号
    
    int _state;//小球当前状态；0在准备区  1在棋盘区
    
    bool _select;//是否选中
    
    std::string _plist;//小球plist
    
};


#endif
