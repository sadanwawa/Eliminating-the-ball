//
//  ChessBoardLayer.h
//  minGameTest
//
//  Created by 马 英臣 on 13-8-20.
//
//

#ifndef minGameTest_ChessBoardLayer_h
#define minGameTest_ChessBoardLayer_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BaseLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ChessBoardLayer:
public BaseLayer
{   
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ChessBoardLayer, create);     
      
    ChessBoardLayer();    
    virtual ~ChessBoardLayer();        
    virtual void onEnter();
    virtual void onExit();    
    virtual bool init();      
    virtual void draw();
    
    void initData(int lin,int row,float gra);//行 列 间隔
    
    
    
private:   
    int _lin;//行
    int _row;//列
    float _gra;//间隔
    
};







#endif
