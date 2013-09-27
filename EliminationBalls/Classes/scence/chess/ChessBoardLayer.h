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
#include "data/ChessDataVO.h"

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
    
    void initData(ChessDataVO* vo);    
    
private:   
    ChessDataVO* _chessDataVO;//当前数据
    
};







#endif
